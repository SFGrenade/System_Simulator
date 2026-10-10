// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/Sources/ALSA.h"

namespace SFG::SystemSimulator::AudioInterface::Sources {

void ALSA::init() {
  logger_->trace( fmt::runtime( "init()" ) );

  logger_->trace( fmt::runtime( "init - ALSA available: {}" ), alsa_.isAvailable() );

  soxrs_.reserve( parameters_.channelCount );
  for( size_t i = 0; i < parameters_.channelCount; i++ ) {
    soxr_error_t soxError;
    std::shared_ptr< soxr > tmp = std::shared_ptr< soxr >( soxr_create( samplerate_, INTERNAL_SAMPLERATE, 1, &soxError, nullptr, nullptr, nullptr ),
                                                           []( soxr_t p ) { soxr_delete( p ); } );
    if( soxError ) {
      logger_->error( fmt::runtime( "soxr soxr_create error: {:s}" ), soxError );
      return stop();
    }
    soxrs_.push_back( tmp );
  }
  audioQueues_.reserve( parameters_.channelCount );
  for( size_t i = 0; i < parameters_.channelCount; i++ ) {
    audioQueues_.push_back( makeAudioQueue() );
  }
  pushSignals_.resize( parameters_.channelCount );
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
    for( size_t channel = 0; channel < parameters_.channelCount; channel++ ) {
      if( audioQueues_[channel]->size() >= framesPerBuffer_ ) {
        AudioChunk samples( framesPerBuffer_, 0.0f );
        std::move( audioQueues_[channel]->begin(), audioQueues_[channel]->begin() + framesPerBuffer_, samples.data() );
        audioQueues_[channel]->erase_begin( framesPerBuffer_ );
        pushSignals_[channel]( samples );
      }
    }
  }
}

}  // namespace SFG::SystemSimulator::AudioInterface::Sources
