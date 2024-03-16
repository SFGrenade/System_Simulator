#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/RecordingServer/recordingServer.h>
#include <limits>
#include <string>
#include <vector>

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "testLogs/recordingServerTest.log", false );
  std::vector< std::string > args;
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  uint32_t const sampleRate = 48000;

  SFG::SystemSimulator::RecordingServer::RecordingServer server;
  std::list< int16_t > valuesRaw;
  for( int i = 0; i < sampleRate * 2; i++ ) {
    valuesRaw.push_back( std::numeric_limits< int16_t >::min()
                         + static_cast< int16_t >( static_cast< double >( std::numeric_limits< int16_t >::max() - std::numeric_limits< int16_t >::min() )
                                                   * ( static_cast< double >( ( i * 150 ) % sampleRate ) / static_cast< double >( sampleRate ) ) ) );
  }
  std::list< char > valuesBytes;
  for( int16_t value : valuesRaw ) {
    valuesBytes.push_back( static_cast< char >( ( value >> 0 ) & 0xFF ) );
    valuesBytes.push_back( static_cast< char >( ( value >> 8 ) & 0xFF ) );
  }

  server.setupAudioGenerator( "TestGenerator", SFG::SystemSimulator::RecordingServer::AudioFormatType::PCM, 1, sampleRate, 16 );
  server.printDebugInfo();

  server.streamAudioFrame( "TestGenerator", valuesBytes );
  server.printDebugInfo();

  server.saveAudioGenerator( "TestGenerator" );

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return 0;
}
