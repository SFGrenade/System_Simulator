// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/PortAudioSource.h"

namespace SFG::SystemSimulator::AudioInterface {

void PortAudioSource::start( std::string const& sourceName, std::string const& apiName, bool pulling, size_t framesPerBuffer ) {
  logger_->trace( fmt::runtime( "start( {:?}, {:?}, {}, {:d} )" ), sourceName, apiName, pulling, framesPerBuffer );

  PaDeviceIndex inputDeviceIndex = PA::GetDevice( sourceName, apiName );

  {
    PaDeviceInfo const* deviceInfo = Pa_GetDeviceInfo( inputDeviceIndex );
    parameters_.device = inputDeviceIndex;
    parameters_.channelCount = 1;
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
    if( PaError error = Pa_OpenStream( &tmpStream, &parameters_, nullptr, samplerate_, framesPerBuffer_, flags_, pulling ? nullptr : s_callback, this );
        error != PaErrorCode::paNoError ) {
      logger_->error( fmt::runtime( "PortAudio Pa_OpenStream error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
      return stop();
    }
    stream_ = std::shared_ptr< PaStream >( tmpStream, []( PaStream* p ) { Pa_CloseStream( p ); } );
  }

  running_ = true;
  if( PaError error = Pa_StartStream( stream_.get() ); error != PaErrorCode::paNoError ) {
    logger_->error( fmt::runtime( "PortAudio Pa_StartStream error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
    return stop();
  }
}

void PortAudioSource::stop() {
  running_ = false;

  if( PaError error = Pa_StopStream( stream_.get() ); error != PaErrorCode::paNoError ) {
    logger_->error( fmt::runtime( "PortAudio Pa_StopStream error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
  }

  stream_.reset();
}

AudioChunk PortAudioSource::onPullAudio( size_t frames ) {
  AudioChunk ret( frames * parameters_.channelCount, 0.0f );
  if( PaError error = Pa_ReadStream( stream_.get(), ret.data(), frames ); error != PaErrorCode::paNoError ) {
    logger_->error( fmt::runtime( "PortAudio Pa_ReadStream error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
  }
  return ret;
}

AudioFormat PortAudioSource::onPullFormat() {
  AudioFormat ret;
  ret.sampleRate = samplerate_;
  ret.channels = parameters_.channelCount;
  return ret;
}

int PortAudioSource::s_callback( void const* inputBuffer,
                                 void* outputBuffer,
                                 unsigned long framesPerBuffer,
                                 PaStreamCallbackTimeInfo const* timeInfo,
                                 PaStreamCallbackFlags statusFlags,
                                 void* userData ) {
  PortAudioSource* self = reinterpret_cast< PortAudioSource* >( userData );
  return self->callback( inputBuffer, outputBuffer, framesPerBuffer, timeInfo, statusFlags );
}

PaStreamCallbackResult PortAudioSource::callback( void const* inputBuffer,
                                                  void* /*outputBuffer*/,
                                                  unsigned long framesPerBuffer,
                                                  PaStreamCallbackTimeInfo const* /*timeInfo*/,
                                                  PaStreamCallbackFlags /*statusFlags*/ ) {
  float const* in = reinterpret_cast< float const* >( inputBuffer );
  emitAudio( std::vector< float >( in, in + size_t( framesPerBuffer * parameters_.channelCount ) ) );
  return running_.load( std::memory_order_relaxed ) ? PaStreamCallbackResult::paContinue : PaStreamCallbackResult::paComplete;
}

}  // namespace SFG::SystemSimulator::AudioInterface
