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
  std::shared_ptr< BufferTransform > buffer = std::make_shared< BufferTransform >();
  std::shared_ptr< PortAudioSink > sink = std::make_shared< PortAudioSink >();

  source->pushAudioSignal().connect(
      AudioNode::PushAudioSignal::slot_type( std::bind( &BufferTransform::onPushAudio, buffer.get(), std::placeholders::_1 ) ).track_foreign( buffer ) );
  source->pushFormatSignal().connect(
      AudioNode::PushFormatSignal::slot_type( std::bind( &BufferTransform::onPushFormat, buffer.get(), std::placeholders::_1 ) ).track_foreign( buffer ) );

  sink->pullAudioSignal().connect(
      AudioNode::PullAudioSignal::slot_type( std::bind( &BufferTransform::onPullAudio, buffer.get(), std::placeholders::_1 ) ).track_foreign( buffer ) );
  sink->pullFormatSignal().connect(
      AudioNode::PullFormatSignal::slot_type( std::bind( &BufferTransform::onPullFormat, buffer.get() ) ).track_foreign( buffer ) );

  source->start( "Microphone", "WASAPI", false, 512 );
  sink->start( "Headphones", "WASAPI", false, 512 );

  std::this_thread::sleep_for( std::chrono::seconds( 10 ) );

  source->stop();
  sink->stop();

  source.reset();
  buffer.reset();
  sink.reset();

  if( PaError error = Pa_Terminate(); error != PaErrorCode::paNoError ) {
    spdlog::error( fmt::runtime( "PortAudio Pa_Terminate error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
  }

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return retCode;
}
