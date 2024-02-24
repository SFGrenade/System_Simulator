#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <chrono>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

#include "SFG/SystemSimulator/AudioInterface/_portaudio.h"

struct MySettingsStruct {
  float outputMultiplier;

  PortAudio::PaStream *portAudioStream;
  int numInputChannels;
  int numOutputChannels;
  PortAudio::PaSampleFormat sampleFormat;
  double sampleRate;
  unsigned long framesPerBuffer;
};

int audioMonitoringCallback( const void *inputBuffer,
                             void *outputBuffer,
                             unsigned long framesPerBuffer,
                             const PortAudio::PaStreamCallbackTimeInfo *timeInfo,
                             PortAudio::PaStreamCallbackFlags statusFlags,
                             void *userData ) {
  MySettingsStruct *data = (MySettingsStruct *)userData;
  float *in = (float *)inputBuffer;
  float *out = (float *)outputBuffer;
  unsigned int i;

  if( ( statusFlags & PortAudio::inputUnderflow ) == PortAudio::inputUnderflow ) {
    spdlog::warn( fmt::runtime( "PortAudioStream - Input underflow" ) );
  }
  if( ( statusFlags & PortAudio::inputOverflow ) == PortAudio::inputOverflow ) {
    spdlog::warn( fmt::runtime( "PortAudioStream - Input overflow" ) );
  }
  if( ( statusFlags & PortAudio::outputUnderflow ) == PortAudio::outputUnderflow ) {
    spdlog::warn( fmt::runtime( "PortAudioStream - output underflow" ) );
  }
  if( ( statusFlags & PortAudio::outputOverflow ) == PortAudio::outputOverflow ) {
    spdlog::warn( fmt::runtime( "PortAudioStream - output overflow" ) );
  }
  if( ( statusFlags & PortAudio::primingOutput ) == PortAudio::primingOutput ) {
    spdlog::warn( fmt::runtime( "PortAudioStream - output priming" ) );
  }

  for( i = 0; i < framesPerBuffer; i++ ) {
    *out++ = *in++;
  }

  return PortAudio::PaStreamCallbackResult::paContinue;
}

int main( int argc, char **argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "AudioInterfaceLog.log" );
  std::vector< std::string > args;
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  int retCode = 0;
  PortAudio::PaError err;
  spdlog::trace( fmt::runtime( "using {:s}" ), PortAudio::Pa_GetVersionText() );

  if( ( err = PortAudio::Pa_Initialize() ) != PortAudio::PaErrorCode::paNoError ) {
    spdlog::error( fmt::runtime( "PortAudio Pa_Initialize error: {:#x}, {:s}" ), err, PortAudio::Pa_GetErrorText( err ) );
  } else {
    PortAudio::PaHostApiIndex numHostApis;
    if( ( numHostApis = PortAudio::Pa_GetHostApiCount() ) < 0 ) {
      spdlog::error( fmt::runtime( "PortAudio Pa_GetHostApiCount error: {:#x}, {:s}" ), numHostApis, PortAudio::Pa_GetErrorText( numHostApis ) );
    } else {
      spdlog::error( fmt::runtime( "APIs:" ) );
      for( PortAudio::PaHostApiIndex i = 0; i < numHostApis; i++ ) {
        PortAudio::PaHostApiInfo const *hostApiInfo = PortAudio::Pa_GetHostApiInfo( i );
        spdlog::error( fmt::runtime( "- '{:s}', version {:d}:" ), hostApiInfo->name, hostApiInfo->structVersion );
        spdlog::error( fmt::runtime( "  - type: {:d}" ), static_cast< int >( hostApiInfo->type ) );
        spdlog::error( fmt::runtime( "  - deviceCount: {:d}" ), hostApiInfo->deviceCount );
        spdlog::error( fmt::runtime( "  - defaultInputDevice: {:d}" ), hostApiInfo->defaultInputDevice );
        spdlog::error( fmt::runtime( "  - defaultOutputDevice: {:d}" ), hostApiInfo->defaultOutputDevice );
      }
    }

    PortAudio::PaDeviceIndex numDevices;
    if( ( numDevices = PortAudio::Pa_GetDeviceCount() ) < 0 ) {
      spdlog::error( fmt::runtime( "PortAudio Pa_GetDeviceCount error: {:#x}, {:s}" ), numDevices, PortAudio::Pa_GetErrorText( numDevices ) );
    } else {
      spdlog::error( fmt::runtime( "Devices:" ) );
      for( PortAudio::PaDeviceIndex i = 0; i < numDevices; i++ ) {
        PortAudio::PaDeviceInfo const *deviceInfo = PortAudio::Pa_GetDeviceInfo( i );
        spdlog::error( fmt::runtime( "- '{:s}', version {:d}:" ), deviceInfo->name, deviceInfo->structVersion );
        spdlog::error( fmt::runtime( "  - hostApi: {:d}" ), deviceInfo->hostApi );
        spdlog::error( fmt::runtime( "  - maxInputChannels: {:d}" ), deviceInfo->maxInputChannels );
        spdlog::error( fmt::runtime( "  - maxOutputChannels: {:d}" ), deviceInfo->maxOutputChannels );
        spdlog::error( fmt::runtime( "  - defaultLowInputLatency: {:f}" ), deviceInfo->defaultLowInputLatency );
        spdlog::error( fmt::runtime( "  - defaultLowOutputLatency: {:f}" ), deviceInfo->defaultLowOutputLatency );
        spdlog::error( fmt::runtime( "  - defaultHighInputLatency: {:f}" ), deviceInfo->defaultHighInputLatency );
        spdlog::error( fmt::runtime( "  - defaultHighOutputLatency: {:f}" ), deviceInfo->defaultHighOutputLatency );
        spdlog::error( fmt::runtime( "  - defaultSampleRate: {:f}" ), deviceInfo->defaultSampleRate );
      }
    }


    MySettingsStruct myData;
    myData.outputMultiplier = 0.25f;
    myData.portAudioStream = nullptr;
    myData.numInputChannels = 2;
    myData.numOutputChannels = 2;
    myData.sampleFormat = PortAudio::float32;
    myData.sampleRate = 48000;
    myData.framesPerBuffer = 256;

    if( ( err = PortAudio::Pa_OpenDefaultStream( &myData.portAudioStream,
                                                 myData.numInputChannels,
                                                 myData.numOutputChannels,
                                                 myData.sampleFormat,
                                                 myData.sampleRate,
                                                 myData.framesPerBuffer,
                                                 audioMonitoringCallback,
                                                 &myData ) )
        != PortAudio::PaErrorCode::paNoError ) {
      spdlog::error( fmt::runtime( "PortAudio Pa_OpenDefaultStream error: {:#x}, {:s}" ), err, PortAudio::Pa_GetErrorText( err ) );
    } else {
      if( ( err = PortAudio::Pa_StartStream( myData.portAudioStream ) ) != PortAudio::PaErrorCode::paNoError ) {
        spdlog::error( fmt::runtime( "PortAudio Pa_StartStream error: {:#x}, {:s}" ), err, PortAudio::Pa_GetErrorText( err ) );
      } else {
        PortAudio::Pa_Sleep( 1000 * 5 );

        if( ( err = PortAudio::Pa_StopStream( myData.portAudioStream ) ) != PortAudio::PaErrorCode::paNoError ) {
          spdlog::error( fmt::runtime( "PortAudio Pa_StopStream error: {:#x}, {:s}" ), err, PortAudio::Pa_GetErrorText( err ) );
        } else {
        }
      }
    }

    if( ( err = PortAudio::Pa_Terminate() ) != PortAudio::PaErrorCode::paNoError ) {
      spdlog::error( fmt::runtime( "PortAudio Pa_Terminate error: {:#x}, {:s}" ), err, PortAudio::Pa_GetErrorText( err ) );
    }
  }

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return retCode;
}
