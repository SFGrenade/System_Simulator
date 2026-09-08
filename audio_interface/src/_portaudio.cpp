#include "SFG/SystemSimulator/AudioInterface/_portaudio.h"

// Project Includes
#include <SFG/SystemSimulator/Logger/_spdlog.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

namespace PA {

void ListInfo() {
  SFG::SystemSimulator::Logger::spdlogger logger_ = SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "PortAudio" );
  logger_->trace( fmt::runtime( "ListInfo()" ) );

  PaHostApiIndex numHostApis = 0;
  if( numHostApis = Pa_GetHostApiCount(); numHostApis <= 0 ) {
    logger_->error( fmt::runtime( "PortAudio Pa_GetHostApiCount error: {:d}, {:s}" ), numHostApis, Pa_GetErrorText( numHostApis ) );
    return;
  }
  {
    logger_->info( fmt::runtime( "APIs:" ) );
    for( PaHostApiIndex i = 0; i < numHostApis; i++ ) {
      PaHostApiInfo const* hostApiInfo = Pa_GetHostApiInfo( i );
      logger_->info( fmt::runtime( "- {:d}: '{:s}', version {:d}:" ), i, hostApiInfo->name, hostApiInfo->structVersion );
      logger_->info( fmt::runtime( "  - type: {:d}" ), static_cast< int >( hostApiInfo->type ) );
      logger_->info( fmt::runtime( "  - deviceCount: {:d}" ), hostApiInfo->deviceCount );
      logger_->info( fmt::runtime( "  - defaultInputDevice: '{:s}'" ), Pa_GetDeviceInfo( hostApiInfo->defaultInputDevice )->name );
      logger_->info( fmt::runtime( "  - defaultOutputDevice: '{:s}'" ), Pa_GetDeviceInfo( hostApiInfo->defaultOutputDevice )->name );
    }
  }

  PaDeviceIndex numDevices;
  if( numDevices = Pa_GetDeviceCount(); numDevices <= 0 ) {
    logger_->error( fmt::runtime( "PortAudio Pa_GetDeviceCount error: {:d}, {:s}" ), numDevices, Pa_GetErrorText( numDevices ) );
    return;
  }
  {
    logger_->info( fmt::runtime( "Devices:" ) );
    for( PaDeviceIndex i = 0; i < numDevices; i++ ) {
      PaDeviceInfo const* deviceInfo = Pa_GetDeviceInfo( i );
      PaHostApiInfo const* deviceApiInfo = Pa_GetHostApiInfo( deviceInfo->hostApi );
      logger_->info( fmt::runtime( "- {:d}: '{:s}', version {:d}{:s}:" ),
                     i,
                     deviceInfo->name,
                     deviceInfo->structVersion,
                     i == Pa_GetDefaultInputDevice() ? ", (default input)" : ( i == Pa_GetDefaultOutputDevice() ? ", (default output)" : "" ) );
      logger_->info( fmt::runtime( "  - hostApi: '{:s}'" ), deviceApiInfo->name );
      logger_->info( fmt::runtime( "  - maxInputChannels: {:d}" ), deviceInfo->maxInputChannels );
      logger_->info( fmt::runtime( "  - maxOutputChannels: {:d}" ), deviceInfo->maxOutputChannels );
      logger_->info( fmt::runtime( "  - defaultLowInputLatency: {:f}" ), deviceInfo->defaultLowInputLatency );
      logger_->info( fmt::runtime( "  - defaultLowOutputLatency: {:f}" ), deviceInfo->defaultLowOutputLatency );
      logger_->info( fmt::runtime( "  - defaultHighInputLatency: {:f}" ), deviceInfo->defaultHighInputLatency );
      logger_->info( fmt::runtime( "  - defaultHighOutputLatency: {:f}" ), deviceInfo->defaultHighOutputLatency );
      logger_->info( fmt::runtime( "  - defaultSampleRate: {:f}" ), deviceInfo->defaultSampleRate );
    }
  }
}

PaDeviceIndex GetDevice( std::string const& deviceName, std::string const& apiName ) {
  SFG::SystemSimulator::Logger::spdlogger logger_ = SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "PortAudio" );
  logger_->trace( fmt::runtime( "GetDevice( {:?}, {:?} )" ), deviceName, apiName );

  PaDeviceIndex numDevices;
  if( numDevices = Pa_GetDeviceCount(); numDevices <= 0 ) {
    logger_->error( fmt::runtime( "PortAudio Pa_GetDeviceCount error: {:d}, {:s}" ), numDevices, Pa_GetErrorText( numDevices ) );
    return PA::noDevice;
  }
  {
    for( PaDeviceIndex i = 0; i < numDevices; i++ ) {
      PaDeviceInfo const* deviceInfo = Pa_GetDeviceInfo( i );
      PaHostApiInfo const* deviceApiInfo = Pa_GetHostApiInfo( deviceInfo->hostApi );
      if( !apiName.empty() && std::string( deviceApiInfo->name ).find( apiName ) == std::string::npos ) {
        continue;
      }
      if( !deviceName.empty() && std::string( deviceInfo->name ).find( deviceName ) != std::string::npos ) {
        return i;
      }
    }
  }
  return PA::noDevice;
}

}  // namespace PA
