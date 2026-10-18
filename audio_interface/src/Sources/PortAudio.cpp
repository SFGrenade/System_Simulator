// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/Sources/PortAudio.h"

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/Types/Constants.h"

// C++ Includes
#include <algorithm>
#include <cmath>
#include <vector>

namespace SFG::SystemSimulator::AudioInterface::Sources {

void PortAudio::init( std::map< std::string, std::any > const& config ) {
  sourceName_ = std::any_cast< std::string >( config.at( "sourceName" ) );
  apiName_ = std::any_cast< std::string >( config.at( "apiName" ) );
  channels_ = std::any_cast< size_t >( config.at( "channels" ) );
  sampleRate_ = std::any_cast< double >( config.at( "sampleRate" ) );
  framesPerBuffer_ = std::any_cast< size_t >( config.at( "framesPerBuffer" ) );
  logger_->trace( fmt::runtime( "init( {:?}, {:?}, {:d}, {:f}, {:d} )" ), sourceName_, apiName_, channels_, sampleRate_, framesPerBuffer_ );

  PaDeviceIndex inputDeviceIndex = PA::GetDevice( sourceName_, apiName_ );

  {
    PaDeviceInfo const* deviceInfo = Pa_GetDeviceInfo( inputDeviceIndex );
    parameters_.device = inputDeviceIndex;
    parameters_.channelCount = channels_;
    parameters_.sampleFormat = PA::float32;
    parameters_.suggestedLatency = deviceInfo->defaultLowInputLatency;
    parameters_.hostApiSpecificStreamInfo = nullptr;
    sampleRate_ = ( sampleRate_ <= 0.0 ) ? deviceInfo->defaultSampleRate : sampleRate_;
    framesPerBuffer_ = ( framesPerBuffer_ <= 0 ) ? size_t( std::ceil( sampleRate_ * 0.02 ) ) : framesPerBuffer_;

    logger_->info( fmt::runtime( "Settings:" ) );
    logger_->info( fmt::runtime( "- device: {:d}" ), parameters_.device );
    logger_->info( fmt::runtime( "- channelCount: {:d}" ), channels_ );
    logger_->info( fmt::runtime( "- sampleFormat: {:d}" ), parameters_.sampleFormat );
    logger_->info( fmt::runtime( "- suggestedLatency: {:f}" ), parameters_.suggestedLatency );
    logger_->info( fmt::runtime( "- hostApiSpecificStreamInfo: {:p}" ), parameters_.hostApiSpecificStreamInfo );
    logger_->info( fmt::runtime( "- sampleRate: {:f}" ), sampleRate_ );
    logger_->info( fmt::runtime( "- framesPerBuffer: {:d}" ), framesPerBuffer_ );
  }
  {
    PaStream* tmpStream = nullptr;
    if( PaError error = Pa_OpenStream( &tmpStream, &parameters_, nullptr, sampleRate_, framesPerBuffer_, PA::noFlag, nullptr, nullptr ); error != PaErrorCode::paNoError ) {
      logger_->error( fmt::runtime( "PortAudio Pa_OpenStream error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
      return deinit();
    }
    stream_.reset( tmpStream );
  }

  {
    soxr_error_t soxError;
    resampler_.reset( soxr_create( sampleRate_, Types::INTERNAL_SAMPLERATE, channels_, &soxError, nullptr, nullptr, nullptr ) );
    if( soxError ) {
      logger_->error( fmt::runtime( "soxr soxr_create error: {:s}" ), soxError );
      return deinit();
    }
  }
  outPorts = { { "main", {} } };
  outPorts["main"].resize( channels_ );

  if( PaError error = Pa_StartStream( stream_.get() ); error != PaErrorCode::paNoError ) {
    logger_->error( fmt::runtime( "PortAudio Pa_StartStream error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
    return deinit();
  }

  internalFrames_ = std::ceil( double( framesPerBuffer_ ) * Types::INTERNAL_SAMPLERATE / sampleRate_ );
  internalFrames_ = std::min< size_t >( internalFrames_, Types::AUDIO_MESSAGE_CAPACITY );
  rawFrames_ = std::ceil( double( internalFrames_ ) * sampleRate_ / Types::INTERNAL_SAMPLERATE );
  rawBuffer_.resize( channels_ * rawFrames_, 0.0f );
  internalBuffer_.resize( channels_ * internalFrames_, 0.0f );
  logger_->debug( fmt::runtime( "using {:d} internal and {:d} raw frames" ), internalFrames_, rawFrames_ );
}

void PortAudio::updateConfig( std::string const& option, std::any const& newValue ) {
  logger_->trace( fmt::runtime( "updateConfig( option={:?}, newValue={} )" ), option, newValue.type().name() );
}

void PortAudio::update() {
  if( !stream_ ) {
    return;
  }

  if( PaError error = Pa_ReadStream( stream_.get(), rawBuffer_.data(), rawFrames_ ); error != PaErrorCode::paNoError ) {
    logger_->warn( fmt::runtime( "PortAudio Pa_ReadStream: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
  }

  size_t rawFramesUsed = 0;
  size_t internalFramesUsed = 0;
  while( rawFramesUsed < rawFrames_ ) {
    size_t rawFramesProcessed = 0;
    size_t internalFramesProcessed = 0;
    soxr_error_t soxError = soxr_process( resampler_.get(), rawBuffer_.data() + ( rawFramesUsed * channels_ ), rawFrames_ - rawFramesUsed, &rawFramesProcessed, internalBuffer_.data() + ( internalFramesUsed * channels_ ), internalFrames_ - internalFramesUsed, &internalFramesProcessed );
    if( soxError ) {
      logger_->error( fmt::runtime( "soxr soxr_process error: {:s}" ), soxError );
      break;
    }
    if( rawFramesProcessed == 0 && internalFramesProcessed == 0 ) {
      logger_->debug( fmt::runtime( "soxr made no progress; input backlogged" ) );
      break;
    }
    rawFramesUsed += rawFramesProcessed;
    internalFramesUsed += internalFramesProcessed;
  }
  logger_->trace( fmt::runtime( "soxr: {:d} (act={:d}) => {:d} (act={:d})" ), rawFrames_, rawFramesUsed, internalFrames_, internalFramesUsed );

  auto& outPort = outPorts["main"];
  for( size_t channel = 0; channel < channels_; channel++ ) {
    auto& outPortChannel = outPort[channel];
    for( size_t frame = 0; frame < ( internalFramesUsed ); frame++ ) {
      outPortChannel->push( internalBuffer_[( frame * channels_ ) + channel] );
    }
  }
}

void PortAudio::deinit() {
  logger_->trace( fmt::runtime( "deinit()" ) );

  if( stream_ ) {
    if( PaError error = Pa_StopStream( stream_.get() ); error != PaErrorCode::paNoError ) {
      logger_->error( fmt::runtime( "PortAudio Pa_StopStream error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
    }
  }

  stream_.reset();

  resampler_.reset();
  outPorts["main"] = {};
}

}  // namespace SFG::SystemSimulator::AudioInterface::Sources
