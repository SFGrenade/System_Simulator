#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <string>
#include <vector>

#include "SFG/SystemSimulator/LoginServer/loginServer.h"

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "LoginServerLog.log" );
  std::vector< std::string > args;
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  int retCode = 0;
  SFG::SystemSimulator::LoginServer::LoginServer server;
  while( 1 ) {
    try {
      server.run();
    } catch( std::exception const& e ) {
      spdlog::error( fmt::runtime( "error calling server.run: {:s}" ), e.what() );
    }
  }

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return retCode;
}
