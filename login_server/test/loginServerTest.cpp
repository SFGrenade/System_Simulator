#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/LoginServer/loginServer.h>
#include <string>
#include <thread>
#include <vector>

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "testLogs/loginServerTest.log", false );
  std::vector< std::string > args;
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  std::pair< bool, std::string > tmp;

  SFG::SystemSimulator::LoginServer::LoginServer server;

  tmp = server.registerUser( "TestUser", "MyPassword" );
  if( !tmp.first )
    throw tmp.second;

  tmp = server.loginUser( "TestUser", "MyPassword" );
  if( !tmp.first )
    throw tmp.second;
  std::string userSessionToken = tmp.second;

  tmp = server.checkUserSession( userSessionToken );
  if( !tmp.first )
    throw tmp.second;

  tmp = server.logoutUserSession( userSessionToken );
  if( !tmp.first )
    throw tmp.second;

  tmp = server.deleteUser( "TestUser", "MyPassword" );
  if( !tmp.first )
    throw tmp.second;

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return 0;
}
