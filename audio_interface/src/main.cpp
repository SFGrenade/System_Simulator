// Project Includes
#include "SFG/SystemSimulator/AudioInterface/Sinks/PortAudio.h"
#include "SFG/SystemSimulator/AudioInterface/Sources/PortAudio.h"
#include "SFG/SystemSimulator/AudioInterface/Transforms/MonoToN.h"
#include "SFG/SystemSimulator/AudioInterface/Transforms/NtoMono.h"
#include "SFG/SystemSimulator/AudioInterface/_portaudio.h"

// Project Includes
#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/NetworkMessages/Audio.pb.h>

// C++ Includes
#include <chrono>
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

  std::shared_ptr< Sources::PortAudio > source = std::make_shared< Sources::PortAudio >();
  std::shared_ptr< Transforms::NtoMono > ntoMono = std::make_shared< Transforms::NtoMono >();
  std::shared_ptr< Transforms::MonoToN > monoToN = std::make_shared< Transforms::MonoToN >();
  std::shared_ptr< Sinks::PortAudio > sink = std::make_shared< Sinks::PortAudio >();

  source->init( { { "sourceName", std::string( "Microphone" ) }, { "apiName", std::string( "WASAPI" ) }, { "channels", size_t( 2 ) }, { "sampleRate", double( 0.0 ) }, { "framesPerBuffer", size_t( 0 ) } } );
  ntoMono->init( { { "amount", size_t( 2 ) } } );
  monoToN->init( { { "amount", size_t( 2 ) } } );
  sink->init( { { "sourceName", std::string( "Headphones" ) }, { "apiName", std::string( "WASAPI" ) }, { "channels", size_t( 2 ) }, { "sampleRate", double( 0.0 ) }, { "framesPerBuffer", size_t( 0 ) } } );

  // connections
  ( ntoMono->inPorts["main"][0] ) = ( source->outPorts["main"][0] );
  ( ntoMono->inPorts["main"][1] ) = ( source->outPorts["main"][1] );
  ( monoToN->inPorts["main"][0] ) = ( ntoMono->outPorts["main"][0] );
  ( sink->inPorts["main"][0] ) = ( monoToN->outPorts["main"][0] );
  ( sink->inPorts["main"][1] ) = ( monoToN->outPorts["main"][1] );

  bool done = false;
  std::thread tmp( [&]() {
    while( !done ) {
      source->update();
      ntoMono->update();
      monoToN->update();
      sink->update();
    }
  } );

  std::this_thread::sleep_for( std::chrono::seconds( 10 ) );

  done = true;
  if( tmp.joinable() ) {
    tmp.join();
  }

  source->deinit();
  sink->deinit();

  source.reset();
  sink.reset();

  if( PaError error = Pa_Terminate(); error != PaErrorCode::paNoError ) {
    spdlog::error( fmt::runtime( "PortAudio Pa_Terminate error: {:d}, {:s}" ), error, Pa_GetErrorText( error ) );
  }

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return retCode;
}
