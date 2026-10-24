// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/Sources/Mp3File.h"

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/Types/Constants.h"

// C++ Includes
#include <algorithm>
#include <cmath>
#include <vector>

namespace SFG::SystemSimulator::AudioInterface::Sources {

void Mp3File::init( std::map< std::string, std::any > const& config ) {
  fileName_ = std::any_cast< std::string >( config.at( "fileName" ) );
  framesPerBuffer_ = std::any_cast< int64_t >( config.at( "framesPerBuffer" ) );
  logger_->trace( fmt::runtime( "init( {:?}, {:d} )" ), fileName_, framesPerBuffer_ );

  if( drmp3_bool32 err = drmp3_init_file( &mp3_, fileName_.c_str(), nullptr ); err != DRMP3_SUCCESS ) {
    logger_->error( fmt::runtime( "drmp3_init_file error {:d}" ), err );
  }

  framesPerBuffer_ = ( framesPerBuffer_ <= 0 ) ? int64_t( mp3_.sampleRate * 0.02 ) : framesPerBuffer_;

  {
    soxr_error_t soxError;
    resampler_.reset( soxr_create( mp3_.sampleRate, Types::INTERNAL_SAMPLERATE, mp3_.channels, &soxError, nullptr, nullptr, nullptr ) );
    if( soxError ) {
      logger_->error( fmt::runtime( "soxr soxr_create error: {:s}" ), soxError );
      return deinit();
    }
  }
  outPorts = { { "main", {} } };
  outPorts["main"].resize( mp3_.channels );

  internalFrames_ = std::ceil( double( framesPerBuffer_ ) * Types::INTERNAL_SAMPLERATE / mp3_.sampleRate );
  internalFrames_ = std::min< size_t >( internalFrames_, Types::AUDIO_MESSAGE_CAPACITY );
  rawFrames_ = std::ceil( double( internalFrames_ ) * mp3_.sampleRate / Types::INTERNAL_SAMPLERATE );
  rawBuffer_.resize( mp3_.channels * rawFrames_, 0.0f );
  internalBuffer_.resize( mp3_.channels * internalFrames_, 0.0f );
}

void Mp3File::updateConfig( std::string const& option, std::any const& newValue ) {
  logger_->trace( fmt::runtime( "updateConfig( option={:?}, newValue={} )" ), option, newValue.type().name() );
}

void Mp3File::update() {
  // todo: fixme: looping? oneshot? more config options to re-/start|stop the sound at will?
  size_t rawFramesRead = drmp3_read_pcm_frames_f32( &mp3_, rawFrames_, rawBuffer_.data() );

  size_t rawFramesUsed = 0;
  size_t internalFramesUsed = 0;
  while( rawFramesUsed < rawFramesRead ) {
    size_t rawFramesProcessed = 0;
    size_t internalFramesProcessed = 0;
    soxr_error_t soxError = soxr_process( resampler_.get(), rawBuffer_.data() + ( rawFramesUsed * mp3_.channels ), rawFramesRead - rawFramesUsed, &rawFramesProcessed, internalBuffer_.data() + ( internalFramesUsed * mp3_.channels ), internalFrames_ - internalFramesUsed, &internalFramesProcessed );
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
  for( size_t channel = 0; channel < mp3_.channels; channel++ ) {
    auto& outPortChannel = outPort[channel];
    for( size_t frame = 0; frame < ( internalFramesUsed ); frame++ ) {
      outPortChannel->push( internalBuffer_[( frame * mp3_.channels ) + channel] );
    }
  }
}

void Mp3File::deinit() {
  logger_->trace( fmt::runtime( "deinit()" ) );

  drmp3_uninit( &mp3_ );

  resampler_.reset();
  outPorts["main"] = {};
}

}  // namespace SFG::SystemSimulator::AudioInterface::Sources
