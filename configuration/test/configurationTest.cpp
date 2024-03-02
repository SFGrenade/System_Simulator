#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <string>

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "testLogs/configurationTest.log", false );
  std::vector< std::string > args;
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  int retVal = 0;
  SFG::SystemSimulator::Configuration::Configuration config( "config/test_conf.ini" );
  std::string myVal = config.get< std::string >( "Test", "Key" );
  spdlog::trace( fmt::runtime( "myVal = {:s}" ), myVal );
  if( myVal != "value" ) {
    retVal = 1;
  }

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return retVal;
}
