// Project Includes
#include "SFG/SystemSimulator/AudioInterface/BufferTransform.h"
#include "SFG/SystemSimulator/AudioInterface/PortAudioSink.h"
#include "SFG/SystemSimulator/AudioInterface/PortAudioSource.h"
#include "SFG/SystemSimulator/AudioInterface/_portaudio.h"

// Project Includes
#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/NetworkMessages/Audio.pb.h>

// C++ Includes
#include <chrono>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

using namespace SFG::SystemSimulator::AudioInterface;

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "AudioInterfaceLog.log" );
  std::vector< std::string > args;
  args.reserve( argc );
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  SFG::SystemSimulator::Configuration::Configuration config( "config/audio_interface.ini" );

  int retCode = 0;

  spdlog::info( fmt::runtime( "Using {:s}" ), Pa_GetVersionInfo()->versionText );
  if( PaError error = Pa_Initialize(); error != PaErrorCode::paNoError ) {
    spdlog::error( fmt::runtime( "PortAudio Pa_Initialize error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
    retCode = -1;
  }
  PA::ListInfo();

  std::shared_ptr< PortAudioSource > source = std::make_shared< PortAudioSource >();
  std::shared_ptr< PortAudioSink > sink = std::make_shared< PortAudioSink >();

  source->init( "Microphone", "WASAPI", false, 512 );
  sink->init( "Headphones", "WASAPI", false, 512 );

  std::vector< PushAudioSignal >& sourceOutput = source->pushSignals();
  std::vector< PullAudioSignal >& sinkInput = sink->pullSignals();

  std::vector< std::shared_ptr< BufferTransform > > buffers;
  buffers.reserve( sourceOutput.size() );
  for( size_t i = 0; i < sourceOutput.size(); i++ ) {
    std::shared_ptr< BufferTransform > buffer = std::make_shared< BufferTransform >();

    buffers.push_back( buffer );

    conPush2Down< PushAudioSignal, BufferTransform >( sourceOutput[i], buffer, &BufferTransform::onPushAudio );
    conPull2Up< PullAudioSignal, BufferTransform >( sinkInput[i], buffer, &BufferTransform::onPullAudio );
  }

  source->start();
  sink->start();

  std::this_thread::sleep_for( std::chrono::seconds( 10 ) );

  source->stop();
  sink->stop();

  buffers.clear();
  source.reset();
  sink.reset();

  if( PaError error = Pa_Terminate(); error != PaErrorCode::paNoError ) {
    spdlog::error( fmt::runtime( "PortAudio Pa_Terminate error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
  }

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return retCode;
}
