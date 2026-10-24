// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/Sinks/WavFile.h"

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/Types/Constants.h"

// C++ Includes
#include <algorithm>
#include <cmath>
#include <vector>

namespace SFG::SystemSimulator::AudioInterface::Sinks {

void WavFile::init( std::map< std::string, std::any > const& config ) {
  fileName_ = std::any_cast< std::string >( config.at( "fileName" ) );
  channels_ = std::any_cast< int64_t >( config.at( "channels" ) );
  framesPerBuffer_ = std::any_cast< int64_t >( config.at( "framesPerBuffer" ) );
  logger_->trace( fmt::runtime( "init( {:?}, {:d} )" ), fileName_, channels_ );

  format_.container = drwav_container::drwav_container_riff;
  format_.format = DR_WAVE_FORMAT_IEEE_FLOAT;
  format_.channels = channels_;
  format_.sampleRate = Types::INTERNAL_SAMPLERATE;
  format_.bitsPerSample = 32;  // float bit depth
  logger_->info( fmt::runtime( "Settings:" ) );
  logger_->info( fmt::runtime( "- container: {:d}" ), static_cast< uint32_t >( format_.container ) );
  logger_->info( fmt::runtime( "- format: {:d}" ), format_.format );
  logger_->info( fmt::runtime( "- channels: {:d}" ), format_.channels );
  logger_->info( fmt::runtime( "- sampleRate: {:d}" ), format_.sampleRate );
  logger_->info( fmt::runtime( "- bitsPerSample: {:d}" ), format_.bitsPerSample );

  if( drwav_bool32 err = drwav_init_file_write( &wav_, fileName_.c_str(), &format_, nullptr ); err != DRWAV_SUCCESS ) {
    logger_->error( fmt::runtime( "drwav_init_file_write error {:d}" ), err );
  }

  inPorts = { { "main", {} } };
  inPorts["main"].resize( channels_ );

  internalFrames_ = ( framesPerBuffer_ <= 0 ) ? size_t( Types::INTERNAL_SAMPLERATE * 0.02 ) : framesPerBuffer_;
  internalBuffer_.resize( channels_ * internalFrames_, 0.0f );
}

void WavFile::updateConfig( std::string const& option, std::any const& newValue ) {
  logger_->trace( fmt::runtime( "updateConfig( option={:?}, newValue={} )" ), option, newValue.type().name() );
}

void WavFile::update() {
  auto& inPort = inPorts["main"];
  for( size_t channel = 0; channel < channels_; channel++ ) {
    auto& inPortChannel = inPort[channel];
    if( !inPortChannel ) {
      for( size_t frame = 0; frame < ( internalFrames_ ); frame++ ) {
        internalBuffer_[( frame * channels_ ) + channel] = 0.0f;
      }
    } else {
      for( size_t frame = 0; frame < ( internalFrames_ ); frame++ ) {
        float tmp = 0.0f;
        inPortChannel->pop( tmp );
        internalBuffer_[( frame * channels_ ) + channel] = tmp;
      }
    }
  }

  drwav_uint64 framesWritten = drwav_write_pcm_frames( &wav_, internalFrames_, internalBuffer_.data() );
  // todo: fixme: how to check for errors here?
}

void WavFile::deinit() {
  logger_->trace( fmt::runtime( "deinit()" ) );

  if( drwav_result err = drwav_uninit( &wav_ ); err != DRWAV_SUCCESS ) {
    logger_->error( fmt::runtime( "drwav_uninit error {:d}" ), err );
  }

  inPorts["main"] = {};
}

}  // namespace SFG::SystemSimulator::AudioInterface::Sinks
