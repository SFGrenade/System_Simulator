#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/LoginServer/loginServer.h>
#include <string>
#include <thread>
#include <vector>

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "testLogs/loginTimeoutTest.log", false );
  std::vector< std::string > args;
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  SFG::SystemSimulator::Configuration::Configuration config( "config/login_server.ini" );

  std::pair< bool, std::string > tmp;

  SFG::SystemSimulator::LoginServer::LoginServer server;

  tmp = server.registerUser( "TestUser", "MyPassword" );
  spdlog::debug( fmt::runtime( "tmp = {}, '{:s}'" ), tmp.first, tmp.second );
  if( !tmp.first )
    throw tmp.second;

  server.printDebugInfo();

  tmp = server.loginUser( "TestUser", "MyPassword" );
  spdlog::debug( fmt::runtime( "tmp = {}, '{:s}'" ), tmp.first, tmp.second );
  if( !tmp.first )
    throw tmp.second;
  std::string userSessionToken = tmp.second;

  server.printDebugInfo();

  std::this_thread::sleep_for( std::chrono::seconds( config.get< uint32_t >( "Database", "SessionTokenValidTime" ) + 1 ) );

  tmp = server.checkUserSession( userSessionToken );
  spdlog::debug( fmt::runtime( "tmp = {}, '{:s}'" ), tmp.first, tmp.second );
  if( tmp.first )
    throw "Session valid despite fact it shouldn't be.";

  server.printDebugInfo();

  tmp = server.deleteUser( "TestUser", "MyPassword" );
  spdlog::debug( fmt::runtime( "tmp = {}, '{:s}'" ), tmp.first, tmp.second );
  if( !tmp.first )
    throw tmp.second;

  server.printDebugInfo();

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return 0;
}
