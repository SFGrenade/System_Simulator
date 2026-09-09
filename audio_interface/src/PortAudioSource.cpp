// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/PortAudioSource.h"

namespace SFG::SystemSimulator::AudioInterface {

void PortAudioSource::init( std::string const& sourceName, std::string const& apiName, bool pulling, size_t framesPerBuffer ) {
  logger_->trace( fmt::runtime( "init( {:?}, {:?}, {}, {:d} )" ), sourceName, apiName, pulling, framesPerBuffer );

  PaDeviceIndex inputDeviceIndex = PA::GetDevice( sourceName, apiName );

  {
    PaDeviceInfo const* deviceInfo = Pa_GetDeviceInfo( inputDeviceIndex );
    parameters_.device = inputDeviceIndex;
    parameters_.channelCount = deviceInfo->maxInputChannels;
    parameters_.sampleFormat = PA::float32;
    parameters_.suggestedLatency = deviceInfo->defaultLowInputLatency;
    parameters_.hostApiSpecificStreamInfo = nullptr;
    samplerate_ = deviceInfo->defaultSampleRate;
    framesPerBuffer_ = ( framesPerBuffer == size_t( -1 ) ) ? size_t( std::ceil( parameters_.suggestedLatency * samplerate_ ) ) : framesPerBuffer;
    flags_ = PA::noFlag;
    pulling_ = pulling;

    logger_->info( fmt::runtime( "Settings:" ) );
    logger_->info( fmt::runtime( "- device: {:d}" ), parameters_.device );
    logger_->info( fmt::runtime( "- channelCount: {:d}" ), parameters_.channelCount );
    logger_->info( fmt::runtime( "- sampleFormat: {:d}" ), parameters_.sampleFormat );
    logger_->info( fmt::runtime( "- suggestedLatency: {:f}" ), parameters_.suggestedLatency );
    logger_->info( fmt::runtime( "- hostApiSpecificStreamInfo: {:p}" ), parameters_.hostApiSpecificStreamInfo );
    logger_->info( fmt::runtime( "- samplerate: {:f}" ), samplerate_ );
    logger_->info( fmt::runtime( "- framesPerBuffer: {:d}" ), framesPerBuffer_ );
    logger_->info( fmt::runtime( "- flags: {:d}" ), flags_ );
    logger_->info( fmt::runtime( "- pulling: {:d}" ), pulling_.load( std::memory_order_relaxed ) );
  }
  {
    PaStream* tmpStream = nullptr;
    if( PaError error = Pa_OpenStream( &tmpStream, &parameters_, nullptr, samplerate_, framesPerBuffer_, flags_, s_callback, this );
        error != PaErrorCode::paNoError ) {
      logger_->error( fmt::runtime( "PortAudio Pa_OpenStream error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
      return stop();
    }
    stream_ = std::shared_ptr< PaStream >( tmpStream, []( PaStream* p ) { Pa_CloseStream( p ); } );
  }

  audioQueues_.reserve( parameters_.channelCount );
  for( size_t i = 0; i < parameters_.channelCount; i++ ) {
    audioQueues_.push_back( makeQueue() );
  }
  pushSignals_.resize( parameters_.channelCount );
}

void PortAudioSource::start() {
  logger_->trace( fmt::runtime( "start()" ) );

  running_ = true;
  if( PaError error = Pa_StartStream( stream_.get() ); error != PaErrorCode::paNoError ) {
    logger_->error( fmt::runtime( "PortAudio Pa_StartStream error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
    return stop();
  }
  thread_ = std::thread( &PortAudioSource::threadRun, this );
}

void PortAudioSource::stop() {
  logger_->trace( fmt::runtime( "stop()" ) );

  running_ = false;

  if( thread_.joinable() ) {
    thread_.join();
  }

  if( PaError error = Pa_StopStream( stream_.get() ); error != PaErrorCode::paNoError ) {
    logger_->error( fmt::runtime( "PortAudio Pa_StopStream error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
  }

  stream_.reset();

  decltype( audioQueues_ )( 0 ).swap( audioQueues_ );
  decltype( pushSignals_ )( 0 ).swap( pushSignals_ );
}

std::vector< PushAudioSignal >& PortAudioSource::pushSignals() {
  logger_->trace( fmt::runtime( "pushSignals()" ) );

  return pushSignals_;
}

AudioChunk PortAudioSource::onPullAudio( size_t channel, size_t frames ) {
  if( pulling_.load( std::memory_order_relaxed ) ) {
    size_t framesToCopy = std::min( frames, audioQueues_[channel]->read_available() );
    AudioChunk ret( framesToCopy, 0.0f );
    audioQueues_[channel]->pop( ret.data(), framesToCopy );
    return ret;
  }
  return AudioChunk( 0 );
}

void PortAudioSource::threadRun() {
  while( running_.load( std::memory_order_relaxed ) ) {
    if( !pulling_.load( std::memory_order_relaxed ) ) {
      for( size_t channel = 0; channel < parameters_.channelCount; channel++ ) {
        if( audioQueues_[channel]->read_available() >= framesPerBuffer_ ) {
          AudioChunk samples( framesPerBuffer_, 0.0f );
          audioQueues_[channel]->pop( samples.data(), framesPerBuffer_ );
          pushSignals_[channel]( samples );
        }
      }
    }
  }
}

PaStreamCallbackResult PortAudioSource::callback( void const* inputBuffer,
                                                  void* /*outputBuffer*/,
                                                  unsigned long framesPerBuffer,
                                                  PaStreamCallbackTimeInfo const* /*timeInfo*/,
                                                  PaStreamCallbackFlags /*statusFlags*/ ) {
  float const* in = reinterpret_cast< float const* >( inputBuffer );

  for( size_t frame = 0; frame < framesPerBuffer; frame++ ) {
    for( size_t channel = 0; channel < parameters_.channelCount; channel++ ) {
      audioQueues_[channel]->push( in[( frame * parameters_.channelCount ) + channel] );
    }
  }

  return running_.load( std::memory_order_relaxed ) ? PaStreamCallbackResult::paContinue : PaStreamCallbackResult::paComplete;
}

int PortAudioSource::s_callback( void const* inputBuffer,
                                 void* outputBuffer,
                                 unsigned long framesPerBuffer,
                                 PaStreamCallbackTimeInfo const* timeInfo,
                                 PaStreamCallbackFlags statusFlags,
                                 void* userData ) {
  return reinterpret_cast< PortAudioSource* >( userData )->callback( inputBuffer, outputBuffer, framesPerBuffer, timeInfo, statusFlags );
}

}  // namespace SFG::SystemSimulator::AudioInterface
