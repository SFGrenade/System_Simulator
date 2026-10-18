// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/Sinks/PortAudio.h"

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/Types/Constants.h"

// C++ Includes
#include <algorithm>
#include <cmath>
#include <vector>

namespace SFG::SystemSimulator::AudioInterface::Sinks {

void PortAudio::init( std::map< std::string, std::any > const& config ) {
  sourceName_ = std::any_cast< std::string >( config.at( "sourceName" ) );
  apiName_ = std::any_cast< std::string >( config.at( "apiName" ) );
  channels_ = std::any_cast< size_t >( config.at( "channels" ) );
  sampleRate_ = std::any_cast< double >( config.at( "sampleRate" ) );
  logger_->trace( fmt::runtime( "init( {:?}, {:?}, {:d}, {:f} )" ), sourceName_, apiName_, channels_, sampleRate_ );

  PaDeviceIndex outputDeviceIndex = PA::GetDevice( sourceName_, apiName_ );

  {
    PaDeviceInfo const* deviceInfo = Pa_GetDeviceInfo( outputDeviceIndex );
    parameters_.device = outputDeviceIndex;
    parameters_.channelCount = channels_;
    parameters_.sampleFormat = PA::float32;
    parameters_.suggestedLatency = 0;
    parameters_.hostApiSpecificStreamInfo = nullptr;
    sampleRate_ = ( sampleRate_ <= 0.0 ) ? deviceInfo->defaultSampleRate : sampleRate_;

    logger_->info( fmt::runtime( "Settings:" ) );
    logger_->info( fmt::runtime( "- device: {:d}" ), parameters_.device );
    logger_->info( fmt::runtime( "- channelCount: {:d}" ), channels_ );
    logger_->info( fmt::runtime( "- sampleFormat: {:d}" ), parameters_.sampleFormat );
    logger_->info( fmt::runtime( "- suggestedLatency: {:f}" ), parameters_.suggestedLatency );
    logger_->info( fmt::runtime( "- hostApiSpecificStreamInfo: {:p}" ), parameters_.hostApiSpecificStreamInfo );
    logger_->info( fmt::runtime( "- sampleRate: {:f}" ), sampleRate_ );
  }
  {
    PaStream* tmpStream = nullptr;
    if( PaError error = Pa_OpenStream( &tmpStream, nullptr, &parameters_, sampleRate_, PA::framesPerBufferUnspecified, PA::noFlag, nullptr, this ); error != PaErrorCode::paNoError ) {
      logger_->error( fmt::runtime( "PortAudio Pa_OpenStream error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
      return deinit();
    }
    stream_ = std::shared_ptr< PaStream >( tmpStream, []( PaStream* p ) { Pa_CloseStream( p ); } );
  }

  soxrIoSpec_ = soxr_io_spec( SOXR_FLOAT32_I, SOXR_FLOAT32_I );
  soxrIoSpec_.scale = 1.0;
  soxrIoSpec_.flags = 0;
  soxrIoSpec_.e = nullptr;
  soxrs_.clear();
  soxrs_.reserve( channels_ );
  for( size_t channel = 0; channel < channels_; channel++ ) {
    soxr_error_t soxError;
    std::shared_ptr< soxr > tmp = std::shared_ptr< soxr >( soxr_create( Types::INTERNAL_SAMPLERATE, sampleRate_, 1, &soxError, &soxrIoSpec_, nullptr, nullptr ), []( soxr_t p ) { soxr_delete( p ); } );
    if( soxError ) {
      logger_->error( fmt::runtime( "soxr soxr_create error: {:s}" ), soxError );
      return deinit();
    }
    soxrs_.push_back( tmp );
  }
  inPorts = { { "main", {} } };
  inPorts["main"].resize( channels_ );

  if( PaError error = Pa_StartStream( stream_.get() ); error != PaErrorCode::paNoError ) {
    logger_->error( fmt::runtime( "PortAudio Pa_StartStream error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
    return deinit();
  }
}

void PortAudio::updateConfig( std::string const& option, std::any const& newValue ) {
  logger_->trace( fmt::runtime( "deinit( option={:?}, newValue={} )" ), option, newValue.type().name() );
}

bool PortAudio::update() {
  size_t rawFrames = std::min< size_t >( Pa_GetStreamWriteAvailable( stream_.get() ), Types::AUDIO_MESSAGE_CAPACITY );
  size_t internalFrames = std::ceil( double( rawFrames ) * Types::INTERNAL_SAMPLERATE / sampleRate_ );

  if( rawFrames <= 0 ) {
    return false;
  }

  std::vector< float > rawBuffer( channels_ * rawFrames, 0.0f );

  for( size_t channel = 0; channel < channels_; channel++ ) {
    std::vector< float > internalBufferChannel( internalFrames, 0.0f );
    // for( size_t frame = 0; frame < internalFrames; frame++ ) {
    //   if( inPorts["main"][channel] ) {
    //     inPorts["main"][channel]->pop( internalBufferChannel[frame] );
    //   }
    // }
    if( inPorts["main"][channel] ) {
      inPorts["main"][channel]->pop( internalBufferChannel.data(), internalFrames );
    }

    std::vector< float > rawBufferChannel( rawFrames, 0.0f );

    size_t internalFramesUsed = 0;
    size_t rawFramesUsed = 0;
    soxr_error_t soxError = soxr_process( soxrs_[channel].get(), internalBufferChannel.data(), internalFrames, &internalFramesUsed, rawBufferChannel.data(), rawFrames, &rawFramesUsed );
    if( soxError ) {
      logger_->error( fmt::runtime( "soxr soxr_process error: {:s}" ), soxError );
    }
    logger_->trace( fmt::runtime( "called soxr_process with: {:d} (act: {:d}) => {:d} (act: {:d})" ), rawFrames, rawFramesUsed, internalFrames, internalFramesUsed );

    for( size_t frame = 0; frame < rawFramesUsed; frame++ ) {
      rawBuffer[( frame * channels_ ) + channel] = rawBufferChannel[frame];
    }
  }

  if( PaError error = Pa_WriteStream( stream_.get(), rawBuffer.data(), rawFrames ); error != PaErrorCode::paNoError ) {
    logger_->warn( fmt::runtime( "PortAudio Pa_WriteStream: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
  }

  return true;
}

void PortAudio::deinit() {
  logger_->trace( fmt::runtime( "deinit()" ) );

  if( PaError error = Pa_StopStream( stream_.get() ); error != PaErrorCode::paNoError ) {
    logger_->error( fmt::runtime( "PortAudio Pa_StopStream error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
  }

  stream_.reset();

  std::vector< std::shared_ptr< soxr > >( 0 ).swap( soxrs_ );
  std::vector< Types::InputPort< Types::AudioMessage > >( 0 ).swap( inPorts["main"] );
}

}  // namespace SFG::SystemSimulator::AudioInterface::Sinks
