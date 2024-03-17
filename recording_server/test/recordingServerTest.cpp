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
  for( int unused = 0; unused < 6; unused++ ) {
    for( int i = 0; i < sampleRate / 6; i++ ) {
      int64_t freq = 55;
      valuesRaw.push_back( std::numeric_limits< int16_t >::min()
                           + static_cast< int16_t >( static_cast< double >( std::numeric_limits< int16_t >::max() - std::numeric_limits< int16_t >::min() )
                                                     * ( static_cast< double >( ( i * freq ) % sampleRate ) / static_cast< double >( sampleRate ) ) ) );
    }
    for( int i = 0; i < sampleRate / 6; i++ ) {
      int64_t freq = 110;
      valuesRaw.push_back( std::numeric_limits< int16_t >::min()
                           + static_cast< int16_t >( static_cast< double >( std::numeric_limits< int16_t >::max() - std::numeric_limits< int16_t >::min() )
                                                     * ( static_cast< double >( ( i * freq ) % sampleRate ) / static_cast< double >( sampleRate ) ) ) );
    }
  }
  std::list< char > valuesBytes;
  for( int16_t value : valuesRaw ) {
    valuesBytes.push_back( static_cast< char >( ( value >> 0 ) & 0xFF ) );
    valuesBytes.push_back( static_cast< char >( ( value >> 8 ) & 0xFF ) );
  }

  server.setupAudioGenerator( "TestGenerator", 1, sampleRate, 16 );

  server.streamAudioFrame( "TestGenerator", valuesBytes );

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return 0;
}
