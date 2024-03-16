#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/RecordingServer/recordingServer.h>
#include <climits>
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
    valuesRaw.push_back( MININT16
                         + static_cast< int16_t >( static_cast< double >( MAXINT16 - MININT16 )
                                                   * ( static_cast< double >( ( i * 150 ) % sampleRate ) / static_cast< double >( sampleRate ) ) ) );
  }
  std::list< uint8_t > valuesBytes;
  for( int16_t value : valuesRaw ) {
    valuesBytes.push_back( reinterpret_cast< uint8_t* >( &value )[0] );
    valuesBytes.push_back( reinterpret_cast< uint8_t* >( &value )[1] );
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
