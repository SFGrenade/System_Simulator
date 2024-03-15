#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/LoginServer/loginServer.h>
#include <string>
#include <thread>
#include <vector>

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "testLogs/logingServerMassiveDataTest.log", false );
  std::vector< std::string > args;
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  std::pair< bool, std::string > tmp;
  std::stringstream usernameStream;
  std::stringstream passwordHashStream;

  SFG::SystemSimulator::LoginServer::LoginServer server;

  for( int i = 1; i <= 200; i++ ) {
    spdlog::info( fmt::runtime( "Loop {:d}" ), i );

    usernameStream << "A";
    passwordHashStream << "0";

    tmp = server.registerUser( usernameStream.str(), passwordHashStream.str() );
    spdlog::debug( fmt::runtime( "tmp = {}, '{:s}'" ), tmp.first, tmp.second );
    if( ( i <= 128 ) && ( !tmp.first ) )
      throw tmp.second;
    if( ( i > 128 ) && ( tmp.first ) )
      throw "User shouldn't have been created";
  }
  server.printDebugInfo();

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return 0;
}
