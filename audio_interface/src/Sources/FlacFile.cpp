// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/Sources/FlacFile.h"

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/Types/Constants.h"

// C++ Includes
#include <algorithm>
#include <cmath>
#include <vector>

namespace SFG::SystemSimulator::AudioInterface::Sources {

void FlacFile::init( std::map< std::string, std::any > const& config ) {
  fileName_ = std::any_cast< std::string >( config.at( "fileName" ) );
  framesPerBuffer_ = std::any_cast< int64_t >( config.at( "framesPerBuffer" ) );
  logger_->trace( fmt::runtime( "init( {:?}, {:d} )" ), fileName_, framesPerBuffer_ );

  flac_.reset( drflac_open_file( fileName_.c_str(), nullptr ) );

  framesPerBuffer_ = ( framesPerBuffer_ <= 0 ) ? int64_t( flac_->sampleRate * 0.02 ) : framesPerBuffer_;

  {
    soxr_error_t soxError;
    resampler_.reset( soxr_create( flac_->sampleRate, Types::INTERNAL_SAMPLERATE, flac_->channels, &soxError, nullptr, nullptr, nullptr ) );
    if( soxError ) {
      logger_->error( fmt::runtime( "soxr soxr_create error: {:s}" ), soxError );
      return deinit();
    }
  }
  outPorts = { { "main", {} } };
  outPorts["main"].resize( flac_->channels );

  internalFrames_ = std::ceil( double( framesPerBuffer_ ) * Types::INTERNAL_SAMPLERATE / flac_->sampleRate );
  internalFrames_ = std::min< size_t >( internalFrames_, Types::AUDIO_MESSAGE_CAPACITY );
  rawFrames_ = std::ceil( double( internalFrames_ ) * flac_->sampleRate / Types::INTERNAL_SAMPLERATE );
  rawBuffer_.resize( flac_->channels * rawFrames_, 0.0f );
  internalBuffer_.resize( flac_->channels * internalFrames_, 0.0f );
}

void FlacFile::updateConfig( std::string const& option, std::any const& newValue ) {
  logger_->trace( fmt::runtime( "updateConfig( option={:?}, newValue={} )" ), option, newValue.type().name() );
}

void FlacFile::update() {
  // todo: fixme: looping? oneshot? more config options to re-/start|stop the sound at will?
  size_t rawFramesRead = drflac_read_pcm_frames_f32( flac_.get(), rawFrames_, rawBuffer_.data() );

  size_t rawFramesUsed = 0;
  size_t internalFramesUsed = 0;
  while( rawFramesUsed < rawFramesRead ) {
    size_t rawFramesProcessed = 0;
    size_t internalFramesProcessed = 0;
    soxr_error_t soxError = soxr_process( resampler_.get(), rawBuffer_.data() + ( rawFramesUsed * flac_->channels ), rawFramesRead - rawFramesUsed, &rawFramesProcessed, internalBuffer_.data() + ( internalFramesUsed * flac_->channels ), internalFrames_ - internalFramesUsed, &internalFramesProcessed );
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
  // logger_->trace( fmt::runtime( "soxr: {:d} (act={:d}) => {:d} (act={:d})" ), rawFramesRead, rawFramesUsed, internalFrames_, internalFramesUsed );

  auto& outPort = outPorts["main"];
  for( size_t channel = 0; channel < flac_->channels; channel++ ) {
    auto& outPortChannel = outPort[channel];
    for( size_t frame = 0; frame < ( internalFramesUsed ); frame++ ) {
      outPortChannel->push( internalBuffer_[( frame * flac_->channels ) + channel] );
    }
  }
}

void FlacFile::deinit() {
  logger_->trace( fmt::runtime( "deinit()" ) );

  flac_.reset();

  resampler_.reset();
  outPorts["main"] = {};
}

}  // namespace SFG::SystemSimulator::AudioInterface::Sources
