#include <SFG/SystemSimulator/Configuration/configuration.h>
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
  PortAudio::PaStreamParameters inputSettings;
  PortAudio::PaStreamParameters outputSettings;
  double sampleRate;
  unsigned long framesPerBuffer;
  PortAudio::PaStreamFlags flags;
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

  SFG::SystemSimulator::Configuration::Configuration config( "config/audio_interface.ini" );

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
      spdlog::info( fmt::runtime( "APIs:" ) );
      for( PortAudio::PaHostApiIndex i = 0; i < numHostApis; i++ ) {
        PortAudio::PaHostApiInfo const *hostApiInfo = PortAudio::Pa_GetHostApiInfo( i );
        spdlog::info( fmt::runtime( "- {:d}: '{:s}', version {:d}:" ), i, hostApiInfo->name, hostApiInfo->structVersion );
        spdlog::info( fmt::runtime( "  - type: {:d}" ), static_cast< int >( hostApiInfo->type ) );
        spdlog::info( fmt::runtime( "  - deviceCount: {:d}" ), hostApiInfo->deviceCount );
        spdlog::info( fmt::runtime( "  - defaultInputDevice: '{:s}'" ), PortAudio::Pa_GetDeviceInfo( hostApiInfo->defaultInputDevice )->name );
        spdlog::info( fmt::runtime( "  - defaultOutputDevice: '{:s}'" ), PortAudio::Pa_GetDeviceInfo( hostApiInfo->defaultOutputDevice )->name );
      }
    }

    PortAudio::PaDeviceIndex numDevices;
    PortAudio::PaDeviceIndex inputDeviceIndex = PortAudio::Pa_GetDefaultInputDevice();
    PortAudio::PaDeviceIndex outputDeviceIndex = PortAudio::Pa_GetDefaultOutputDevice();
    if( ( numDevices = PortAudio::Pa_GetDeviceCount() ) < 0 ) {
      spdlog::error( fmt::runtime( "PortAudio Pa_GetDeviceCount error: {:#x}, {:s}" ), numDevices, PortAudio::Pa_GetErrorText( numDevices ) );
    } else {
      spdlog::info( fmt::runtime( "Devices:" ) );
      for( PortAudio::PaDeviceIndex i = 0; i < numDevices; i++ ) {
        PortAudio::PaDeviceInfo const *deviceInfo = PortAudio::Pa_GetDeviceInfo( i );
        spdlog::info( fmt::runtime( "- {:d}: '{:s}', version {:d}:" ), i, deviceInfo->name, deviceInfo->structVersion );
        spdlog::info( fmt::runtime( "  - hostApi: '{:s}'" ), PortAudio::Pa_GetHostApiInfo( deviceInfo->hostApi )->name );
        spdlog::info( fmt::runtime( "  - maxInputChannels: {:d}" ), deviceInfo->maxInputChannels );
        spdlog::info( fmt::runtime( "  - maxOutputChannels: {:d}" ), deviceInfo->maxOutputChannels );
        spdlog::info( fmt::runtime( "  - defaultLowInputLatency: {:f}" ), deviceInfo->defaultLowInputLatency );
        spdlog::info( fmt::runtime( "  - defaultLowOutputLatency: {:f}" ), deviceInfo->defaultLowOutputLatency );
        spdlog::info( fmt::runtime( "  - defaultHighInputLatency: {:f}" ), deviceInfo->defaultHighInputLatency );
        spdlog::info( fmt::runtime( "  - defaultHighOutputLatency: {:f}" ), deviceInfo->defaultHighOutputLatency );
        spdlog::info( fmt::runtime( "  - defaultSampleRate: {:f}" ), deviceInfo->defaultSampleRate );
        if( ( config.get< std::string >( "Input", "DeviceName" ) == deviceInfo->name )
            && ( config.get< std::string >( "Input", "DeviceApi" ) == PortAudio::Pa_GetHostApiInfo( deviceInfo->hostApi )->name ) ) {
          inputDeviceIndex = i;
        }
        if( ( config.get< std::string >( "Output", "DeviceName" ) == deviceInfo->name )
            && ( config.get< std::string >( "Output", "DeviceApi" ) == PortAudio::Pa_GetHostApiInfo( deviceInfo->hostApi )->name ) ) {
          outputDeviceIndex = i;
        }
      }
    }

    MySettingsStruct myData;
    memset( &myData, 0, sizeof( myData ) );
    myData.outputMultiplier = 0.25f;
    myData.portAudioStream = nullptr;
    myData.inputSettings.device = inputDeviceIndex;
    myData.inputSettings.channelCount = config.get< int >( "Input", "StreamChannels" );
    myData.inputSettings.sampleFormat = static_cast< PortAudio::PaSampleFormat >( config.get< unsigned long >( "Input", "SampleFormat" ) );
    myData.inputSettings.suggestedLatency = PortAudio::Pa_GetDeviceInfo( myData.inputSettings.device )->defaultLowInputLatency;
    myData.inputSettings.hostApiSpecificStreamInfo = nullptr;
    myData.outputSettings.device = outputDeviceIndex;
    myData.outputSettings.channelCount = config.get< int >( "Output", "StreamChannels" );
    myData.outputSettings.sampleFormat = static_cast< PortAudio::PaSampleFormat >( config.get< unsigned long >( "Output", "SampleFormat" ) );
    myData.outputSettings.suggestedLatency = PortAudio::Pa_GetDeviceInfo( myData.outputSettings.device )->defaultLowInputLatency;
    myData.outputSettings.hostApiSpecificStreamInfo = nullptr;
    myData.sampleRate = config.get< int >( "Input", "SampleRate" );
    myData.framesPerBuffer = config.get< int >( "Input", "FramesPerBuffer" );
    myData.flags = static_cast< PortAudio::PaStreamFlags >( config.get< unsigned long >( "Input", "StreamFlags" ) );

    if( ( err = PortAudio::Pa_OpenStream( &myData.portAudioStream,
                                          &myData.inputSettings,
                                          &myData.outputSettings,
                                          myData.sampleRate,
                                          myData.framesPerBuffer,
                                          myData.flags,
                                          audioMonitoringCallback,
                                          &myData ) )
        != PortAudio::PaErrorCode::paNoError ) {
      spdlog::error( fmt::runtime( "PortAudio Pa_OpenStream error: {:#x}, {:s}" ), err, PortAudio::Pa_GetErrorText( err ) );
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
