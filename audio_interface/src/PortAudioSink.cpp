// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/PortAudioSink.h"

namespace SFG::SystemSimulator::AudioInterface {

void PortAudioSink::start( std::string const& sourceName, std::string const& apiName, bool pushing, size_t framesPerBuffer ) {
  logger_->trace( fmt::runtime( "start( {:?}, {:?}, {}, {:d} )" ), sourceName, apiName, pushing, framesPerBuffer );

  PaDeviceIndex outputDeviceIndex = PA::GetDevice( sourceName, apiName );

  {
    PaDeviceInfo const* deviceInfo = Pa_GetDeviceInfo( outputDeviceIndex );
    parameters_.device = outputDeviceIndex;
    parameters_.channelCount = 1;
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
    if( PaError error = Pa_OpenStream( &tmpStream, nullptr, &parameters_, samplerate_, framesPerBuffer_, flags_, pushing ? nullptr : s_callback, this );
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

void PortAudioSink::stop() {
  running_ = false;

  if( PaError error = Pa_StopStream( stream_.get() ); error != PaErrorCode::paNoError ) {
    logger_->error( fmt::runtime( "PortAudio Pa_StopStream error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
  }

  stream_.reset();
}

void PortAudioSink::onPushAudio( AudioChunk const& samples ) {
  if( PaError error = Pa_WriteStream( stream_.get(), samples.data(), samples.size() / parameters_.channelCount ); error != PaErrorCode::paNoError ) {
    logger_->error( fmt::runtime( "PortAudio Pa_WriteStream error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
  }
}

void PortAudioSink::onPushFormat( AudioFormat const& format ) {
  // todo: code
}

int PortAudioSink::s_callback( void const* inputBuffer,
                               void* outputBuffer,
                               unsigned long framesPerBuffer,
                               PaStreamCallbackTimeInfo const* timeInfo,
                               PaStreamCallbackFlags statusFlags,
                               void* userData ) {
  PortAudioSink* self = reinterpret_cast< PortAudioSink* >( userData );
  return self->callback( inputBuffer, outputBuffer, framesPerBuffer, timeInfo, statusFlags );
}

PaStreamCallbackResult PortAudioSink::callback( void const* /*inputBuffer*/,
                                                void* outputBuffer,
                                                unsigned long framesPerBuffer,
                                                PaStreamCallbackTimeInfo const* /*timeInfo*/,
                                                PaStreamCallbackFlags /*statusFlags*/ ) {
  float* out = reinterpret_cast< float* >( outputBuffer );
  std::optional< std::vector< float > > samples = requestAudio( framesPerBuffer );
  if( samples ) {
    std::copy( samples->begin(), samples->end(), out );
  } else {
    std::fill( out, out + ( framesPerBuffer * parameters_.channelCount ), 0.0f );
  }
  return running_.load( std::memory_order_relaxed ) ? PaStreamCallbackResult::paContinue : PaStreamCallbackResult::paComplete;
}

}  // namespace SFG::SystemSimulator::AudioInterface
