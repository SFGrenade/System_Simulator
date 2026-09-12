// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/PortAudioSink.h"

namespace SFG::SystemSimulator::AudioInterface {

void PortAudioSink::init( std::string const& sourceName, std::string const& apiName, bool pushing, size_t framesPerBuffer ) {
  logger_->trace( fmt::runtime( "init( {:?}, {:?}, {}, {:d} )" ), sourceName, apiName, pushing, framesPerBuffer );

  PaDeviceIndex outputDeviceIndex = PA::GetDevice( sourceName, apiName );

  {
    PaDeviceInfo const* deviceInfo = Pa_GetDeviceInfo( outputDeviceIndex );
    parameters_.device = outputDeviceIndex;
    parameters_.channelCount = deviceInfo->maxOutputChannels;
    parameters_.sampleFormat = PA::float32;
    parameters_.suggestedLatency = deviceInfo->defaultLowOutputLatency;
    parameters_.hostApiSpecificStreamInfo = nullptr;
    samplerate_ = deviceInfo->defaultSampleRate;
    framesPerBuffer_ = ( framesPerBuffer == size_t( -1 ) ) ? size_t( std::ceil( parameters_.suggestedLatency * samplerate_ ) ) : framesPerBuffer;
    flags_ = PA::noFlag;
    pushing_ = pushing;

    logger_->info( fmt::runtime( "Settings:" ) );
    logger_->info( fmt::runtime( "- device: {:d}" ), parameters_.device );
    logger_->info( fmt::runtime( "- channelCount: {:d}" ), parameters_.channelCount );
    logger_->info( fmt::runtime( "- sampleFormat: {:d}" ), parameters_.sampleFormat );
    logger_->info( fmt::runtime( "- suggestedLatency: {:f}" ), parameters_.suggestedLatency );
    logger_->info( fmt::runtime( "- hostApiSpecificStreamInfo: {:p}" ), parameters_.hostApiSpecificStreamInfo );
    logger_->info( fmt::runtime( "- samplerate: {:f}" ), samplerate_ );
    logger_->info( fmt::runtime( "- framesPerBuffer: {:d}" ), framesPerBuffer_ );
    logger_->info( fmt::runtime( "- flags: {:d}" ), flags_ );
    logger_->info( fmt::runtime( "- pushing: {}" ), pushing_.load( std::memory_order_relaxed ) );
  }
  {
    PaStream* tmpStream = nullptr;
    if( PaError error = Pa_OpenStream( &tmpStream, nullptr, &parameters_, samplerate_, framesPerBuffer_, flags_, s_callback, this );
        error != PaErrorCode::paNoError ) {
      logger_->error( fmt::runtime( "PortAudio Pa_OpenStream error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
      return stop();
    }
    stream_ = std::shared_ptr< PaStream >( tmpStream, []( PaStream* p ) { Pa_CloseStream( p ); } );
  }

  soxrs_.reserve( parameters_.channelCount );
  for( size_t i = 0; i < parameters_.channelCount; i++ ) {
    soxr_error_t soxError;
    std::shared_ptr< soxr > tmp = std::shared_ptr< soxr >( soxr_create( INTERNAL_SAMPLERATE, samplerate_, 1, &soxError, nullptr, nullptr, nullptr ),
                                                           []( soxr_t p ) { soxr_delete( p ); } );
    if( soxError ) {
      logger_->error( fmt::runtime( "soxr soxr_create error: {:s}" ), soxError );
      return stop();
    }
    soxrs_.push_back( tmp );
  }
  audioQueues_.reserve( parameters_.channelCount );
  for( size_t i = 0; i < parameters_.channelCount; i++ ) {
    audioQueues_.push_back( makeQueue() );
  }
  pullSignals_.resize( parameters_.channelCount );
}

void PortAudioSink::start() {
  logger_->trace( fmt::runtime( "start()" ) );

  running_ = true;
  if( PaError error = Pa_StartStream( stream_.get() ); error != PaErrorCode::paNoError ) {
    logger_->error( fmt::runtime( "PortAudio Pa_StartStream error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
    return stop();
  }
  thread_ = std::thread( &PortAudioSink::threadRun, this );
}

void PortAudioSink::stop() {
  logger_->trace( fmt::runtime( "stop()" ) );

  running_ = false;

  if( thread_.joinable() ) {
    thread_.join();
  }

  if( PaError error = Pa_StopStream( stream_.get() ); error != PaErrorCode::paNoError ) {
    logger_->error( fmt::runtime( "PortAudio Pa_StopStream error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
  }

  stream_.reset();

  decltype( soxrs_ )( 0 ).swap( soxrs_ );
  decltype( audioQueues_ )( 0 ).swap( audioQueues_ );
  decltype( pullSignals_ )( 0 ).swap( pullSignals_ );
}

std::vector< PullAudioSignal >& PortAudioSink::pullSignals() {
  logger_->trace( fmt::runtime( "pullSignals()" ) );

  return pullSignals_;
}

void PortAudioSink::onPushAudio( size_t channel, AudioChunk const& samples ) {
  if( pushing_.load( std::memory_order_relaxed ) ) {
    audioQueues_[channel]->push( samples.data(), samples.size() );
  }
}

void PortAudioSink::threadRun() {
  while( running_.load( std::memory_order_relaxed ) ) {
    if( !pushing_.load( std::memory_order_relaxed ) ) {
      for( size_t channel = 0; channel < parameters_.channelCount; channel++ ) {
        if( audioQueues_[channel]->read_available() < framesPerBuffer_ ) {
          std::optional< std::vector< float > > samples = pullSignals_[channel]( framesPerBuffer_ );
          if( samples ) {
            audioQueues_[channel]->push( samples->data(), samples->size() );
          }
        }
      }
    }
  }
}

PaStreamCallbackResult PortAudioSink::callback( void const* /*input*/,
                                                void* output,
                                                unsigned long frames,
                                                PaStreamCallbackTimeInfo const* /*timeInfo*/,
                                                PaStreamCallbackFlags /*statusFlags*/ ) {
  float* castOutput = reinterpret_cast< float* >( output );

  for( size_t channel = 0; channel < parameters_.channelCount; channel++ ) {
    std::vector< float > resampledOutput( std::ceil( frames * ( INTERNAL_SAMPLERATE / samplerate_ ) ), 0.0f );
    std::vector< float > rawOutput( frames );
    audioQueues_[channel]->pop( resampledOutput.data(), resampledOutput.size() );
    size_t rawOutputFrames;
    soxr_process( soxrs_[channel].get(), resampledOutput.data(), resampledOutput.size(), nullptr, rawOutput.data(), rawOutput.size(), &rawOutputFrames );
    for( size_t frame = 0; frame < frames; frame++ ) {
      castOutput[( frame * parameters_.channelCount ) + channel] = rawOutput[frame];
    }
  }

  return running_.load( std::memory_order_relaxed ) ? PaStreamCallbackResult::paContinue : PaStreamCallbackResult::paComplete;
}

int PortAudioSink::s_callback( void const* input,
                               void* output,
                               unsigned long frames,
                               PaStreamCallbackTimeInfo const* timeInfo,
                               PaStreamCallbackFlags statusFlags,
                               void* userData ) {
  return reinterpret_cast< PortAudioSink* >( userData )->callback( input, output, frames, timeInfo, statusFlags );
}

}  // namespace SFG::SystemSimulator::AudioInterface
