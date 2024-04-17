#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/RecordingServer/recordingServer.h>
#include <gtest/gtest.h>
#include <limits>
#include <string>
#include <vector>

TEST( NetworkMessages, RegularTest ) {
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

  EXPECT_TRUE( true );
}

void generatorFunc( SFG::SystemSimulator::RecordingServer::RecordingServer* serverPtr, std::string const& generatorName ) {
  uint32_t const sampleRate = 48000;

  serverPtr->setupAudioGenerator( generatorName, 1, sampleRate, 16 );

  std::list< int16_t > valuesRaw;
  for( int z = 0; z < 3; z++ ) {
    for( int unused = 0; unused < 2; unused++ ) {
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

    serverPtr->streamAudioFrame( generatorName, valuesBytes );
  }
}

TEST( NetworkMessages, StressTest ) {
  SFG::SystemSimulator::RecordingServer::RecordingServer server;

  std::thread gen00( generatorFunc, &server, "TestGeneratorStress00" );
  std::thread gen01( generatorFunc, &server, "TestGeneratorStress01" );
  std::thread gen02( generatorFunc, &server, "TestGeneratorStress02" );
  std::thread gen03( generatorFunc, &server, "TestGeneratorStress03" );
  std::thread gen04( generatorFunc, &server, "TestGeneratorStress04" );
  std::thread gen05( generatorFunc, &server, "TestGeneratorStress05" );
  std::thread gen06( generatorFunc, &server, "TestGeneratorStress06" );
  std::thread gen07( generatorFunc, &server, "TestGeneratorStress07" );
  std::thread gen08( generatorFunc, &server, "TestGeneratorStress08" );
  std::thread gen09( generatorFunc, &server, "TestGeneratorStress09" );

  gen00.join();
  gen01.join();
  gen02.join();
  gen03.join();
  gen04.join();
  gen05.join();
  gen06.join();
  gen07.join();
  gen08.join();
  gen09.join();

  EXPECT_TRUE( true );
}
