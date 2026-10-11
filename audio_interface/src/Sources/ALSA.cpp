// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/Sources/ALSA.h"

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/DynamicLibrary/ALSA.detail.h"

namespace DynAlsa = SFG::SystemSimulator::AudioInterface::DynamicLibrary::ALSA_detail;

namespace SFG::SystemSimulator::AudioInterface::Sources {

void ALSA::init( ALSAConfig const& config ) {
  config_ = config;
  logger_->trace( fmt::runtime( "init()" ) );

  logger_->trace( fmt::runtime( "init - ALSA available: {}" ), alsa_.isAvailable() );

  snd_pcm_hw_params_alloc( &alsaHwParams_, alsa_. );

  if( int err = alsa_.snd_pcm_open( &alsaPcm_, config_.sourceName.c_str(), DynAlsa::snd_pcm_stream_t::SND_PCM_STREAM_CAPTURE, config_.openMode ); err < 0 ) {
    logger_->error( fmt::runtime( "init - snd_pcm_open error: {:s}" ), alsa_.snd_strerror( err ) );
  }

  if( int err = alsa_.snd_pcm_hw_params_any( alsaPcm_, alsaHwParams_ ); err < 0 ) {
    logger_->error( fmt::runtime( "init - snd_pcm_hw_params_any error: {:s}" ), alsa_.snd_strerror( err ) );
  }

  if( int err = alsa_.snd_pcm_hw_params_set_rate_resample( alsaPcm_, alsaHwParams_, config_.hwResample ); err < 0 ) {
    logger_->error( fmt::runtime( "init - snd_pcm_hw_params_set_rate_resample error: {:s}" ), alsa_.snd_strerror( err ) );
  }
  if( int err = alsa_.snd_pcm_hw_params_set_access( alsaPcm_, alsaHwParams_, config_.access ); err < 0 ) {
    logger_->error( fmt::runtime( "init - snd_pcm_hw_params_set_access error: {:s}" ), alsa_.snd_strerror( err ) );
  }
  if( int err = alsa_.snd_pcm_hw_params_set_format( alsaPcm_, alsaHwParams_, config_.format ); err < 0 ) {
    logger_->error( fmt::runtime( "init - snd_pcm_hw_params_set_format error: {:s}" ), alsa_.snd_strerror( err ) );
  }
  if( int err = alsa_.snd_pcm_hw_params_set_channels( alsaPcm_, alsaHwParams_, config_.channels ); err < 0 ) {
    logger_->error( fmt::runtime( "init - snd_pcm_hw_params_set_channels error: {:s}" ), alsa_.snd_strerror( err ) );
  }
  if( int err = alsa_.snd_pcm_hw_params_set_rate_near( alsaPcm_, alsaHwParams_, &config_.sampleRate, nullptr ); err < 0 ) {
    logger_->error( fmt::runtime( "init - snd_pcm_hw_params_set_rate_near error: {:s}" ), alsa_.snd_strerror( err ) );
  }
  if( int err = alsa_.snd_pcm_hw_params_set_period_size_near( alsaPcm_, alsaHwParams_, &config_.framesPerBuffer, nullptr ); err < 0 ) {
    logger_->error( fmt::runtime( "init - snd_pcm_hw_params_set_period_size_near error: {:s}" ), alsa_.snd_strerror( err ) );
  }
  if( int err = alsa_.snd_pcm_hw_params_set_buffer_size_near( alsaPcm_, alsaHwParams_, &config_.alsaBufferSize ); err < 0 ) {
    logger_->error( fmt::runtime( "init - snd_pcm_hw_params_set_buffer_size_near error: {:s}" ), alsa_.snd_strerror( err ) );
  }

  if( int err = alsa_.snd_pcm_hw_params( alsaPcm_, alsaHwParams_ ); err < 0 ) {
    logger_->error( fmt::runtime( "init - snd_pcm_hw_params error: {:s}" ), alsa_.snd_strerror( err ) );
  }

  soxrs_.reserve( config_.channels );
  for( size_t i = 0; i < config_.channels; i++ ) {
    soxr_error_t soxError;
    std::shared_ptr< soxr > tmp = std::shared_ptr< soxr >( soxr_create( double( config_.sampleRate ), INTERNAL_SAMPLERATE, 1, &soxError, nullptr, nullptr, nullptr ), []( soxr_t p ) { soxr_delete( p ); } );
    if( soxError ) {
      logger_->error( fmt::runtime( "soxr soxr_create error: {:s}" ), soxError );
      return stop();
    }
    soxrs_.push_back( tmp );
  }
  audioQueues_.reserve( config_.channels );
  for( size_t i = 0; i < config_.channels; i++ ) {
    audioQueues_.push_back( makeAudioQueue() );
  }
  pushSignals_.resize( config_.channels );
}

void ALSA::start() {
  logger_->trace( fmt::runtime( "start()" ) );

  running_ = true;
  thread_ = std::thread( &ALSA::threadRun, this );
}

void ALSA::stop() {
  logger_->trace( fmt::runtime( "stop()" ) );

  running_ = false;

  if( thread_.joinable() ) {
    thread_.join();
  }

  decltype( soxrs_ )( 0 ).swap( soxrs_ );
  decltype( audioQueues_ )( 0 ).swap( audioQueues_ );
  decltype( pushSignals_ )( 0 ).swap( pushSignals_ );
}

std::vector< PushAudioSignal >& ALSA::pushSignals() {
  logger_->trace( fmt::runtime( "pushSignals()" ) );

  return pushSignals_;
}

AudioChunk ALSA::onPullAudio( size_t channel, size_t frames ) {
  return AudioChunk( 0 );
}

void ALSA::threadRun() {
  while( running_.load( std::memory_order_relaxed ) ) {
    for( size_t channel = 0; channel < config_.channels; channel++ ) {
      if( audioQueues_[channel]->size() >= config_.framesPerBuffer ) {
        AudioChunk samples( config_.framesPerBuffer, 0.0f );
        std::move( audioQueues_[channel]->begin(), audioQueues_[channel]->begin() + config_.framesPerBuffer, samples.data() );
        audioQueues_[channel]->erase_begin( config_.framesPerBuffer );
        pushSignals_[channel]( samples );
      }
    }
  }
}

}  // namespace SFG::SystemSimulator::AudioInterface::Sources
