#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/NetworkMessages/Users.pb.h>
#include <string>
#include <vector>

#include "SFG/SystemSimulator/LoginServer/loginServer.h"
#include "SFG/SystemSimulator/LoginServer/netConnector.h"

namespace SSSNM = SFG::SystemSimulator::NetworkMessages;

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "LoginServerLog.log" );
  std::vector< std::string > args;
  args.reserve( argc );
  for( int i = 0; i < argc; i++ ) {
    args.emblace_back( argv[i] );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  int retCode = 0;
  SFG::SystemSimulator::LoginServer::LoginServer loginServer;
  SFG::SystemSimulator::LoginServer::NetConnector netConnector;

  netConnector->subscribe( new SSSNM::RegisterRequest(), [&]( google::protobuf::Message const& req ) {
    SSSNM::RegisterRequest const& actualReq = static_cast< SSSNM::RegisterRequest const& >( req );
    auto tmp = loginServer.registerUser( actualReq.username(), actualReq.password_hash() );
    auto ret = new SSSNM::RegisterResponse();
    ret->set_success( tmp.first );
    ret->set_reason_for_fail( tmp.second );
    netConnector->sendMessage( ret );
  } );
  netConnector->subscribe( new SSSNM::LoginRequest(), [&]( google::protobuf::Message const& req ) {
    SSSNM::LoginRequest const& actualReq = static_cast< SSSNM::LoginRequest const& >( req );
    auto tmp = loginServer.loginUser( actualReq.username(), actualReq.password_hash() );
    auto ret = new SSSNM::LoginResponse();
    ret->set_success( tmp.first );
    if( tmp.first )
      ret->set_session_token( tmp.second );
    else
      ret->set_reason_for_fail( tmp.second );
    netConnector->sendMessage( ret );
  } );
  netConnector->subscribe( new SSSNM::CheckSessionRequest(), [&]( google::protobuf::Message const& req ) {
    SSSNM::CheckSessionRequest const& actualReq = static_cast< SSSNM::CheckSessionRequest const& >( req );
    auto tmp = loginServer.checkUserSession( actualReq.session_token() );
    auto ret = new SSSNM::CheckSessionResponse();
    ret->set_is_valid( tmp.first );
    netConnector->sendMessage( ret );
  } );
  netConnector->subscribe( new SSSNM::LogoutRequest(), [&]( google::protobuf::Message const& req ) {
    SSSNM::LogoutRequest const& actualReq = static_cast< SSSNM::LogoutRequest const& >( req );
    auto tmp = loginServer.logoutUserSession( actualReq.session_token() );
    auto ret = new SSSNM::LogoutResponse();
    ret->set_success( tmp.first );
    ret->set_reason_for_fail( tmp.second );
    netConnector->sendMessage( ret );
  } );
  netConnector->subscribe( new SSSNM::DeleteUserRequest(), [&]( google::protobuf::Message const& req ) {
    SSSNM::DeleteUserRequest const& actualReq = static_cast< SSSNM::DeleteUserRequest const& >( req );
    auto tmp = loginServer.deleteUser( actualReq.username(), actualReq.password_hash() );
    auto ret = new SSSNM::DeleteUserResponse();
    ret->set_success( tmp.first );
    ret->set_reason_for_fail( tmp.second );
    netConnector->sendMessage( ret );
  } );

  while( 1 ) {
    try {
      netConnector->run();
    } catch( std::exception const& e ) {
      spdlog::error( fmt::runtime( "error calling netConnector.run: {:s}" ), e.what() );
    }
  }

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return retCode;
}
