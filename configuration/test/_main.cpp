#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "testLogs/configuration_test.log", false );
  std::vector< std::string > args;
  args.reserve( argc );
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  testing::InitGoogleTest( &argc, argv );
  int retVal = RUN_ALL_TESTS();

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return retVal;
}
