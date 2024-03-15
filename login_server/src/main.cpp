#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <string>
#include <users.pb.h>
#include <vector>

#include "SFG/SystemSimulator/LoginServer/loginServer.h"
#include "SFG/SystemSimulator/LoginServer/netConnector.h"

namespace SSP = SFG::SystemSimulator::ProtoMessages;

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "LoginServerLog.log" );
  std::vector< std::string > args;
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  int retCode = 0;
  SFG::SystemSimulator::LoginServer::LoginServer loginServer;
  SFG::SystemSimulator::LoginServer::NetConnector netConnector;
  netConnector->subscribe( new SSP::RegisterRequest(), [&]( google::protobuf::Message const& req ) {
    auto tmp = loginServer.registerUser( dynamic_cast< SSP::RegisterRequest const& >( req ).username(),
                                         dynamic_cast< SSP::RegisterRequest const& >( req ).password_hash() );
    auto ret = new SSP::RegisterResponse();
    ret->set_success( tmp.first );
    ret->set_reason_for_fail( tmp.second );
    netConnector->sendMessage( ret );
  } );
  netConnector->subscribe( new SSP::LoginRequest(), [&]( google::protobuf::Message const& req ) {
    auto tmp
        = loginServer.loginUser( dynamic_cast< SSP::LoginRequest const& >( req ).username(), dynamic_cast< SSP::LoginRequest const& >( req ).password_hash() );
    auto ret = new SSP::LoginResponse();
    ret->set_success( tmp.first );
    if( tmp.first )
      ret->set_session_token( tmp.second );
    else
      ret->set_reason_for_fail( tmp.second );
    netConnector->sendMessage( ret );
  } );
  netConnector->subscribe( new SSP::CheckSessionRequest(), [&]( google::protobuf::Message const& req ) {
    auto tmp = loginServer.checkUserSession( dynamic_cast< SSP::CheckSessionRequest const& >( req ).session_token() );
    auto ret = new SSP::CheckSessionResponse();
    ret->set_is_valid( tmp.first );
    netConnector->sendMessage( ret );
  } );
  netConnector->subscribe( new SSP::LogoutRequest(), [&]( google::protobuf::Message const& req ) {
    auto tmp = loginServer.logoutUserSession( dynamic_cast< SSP::LogoutRequest const& >( req ).session_token() );
    auto ret = new SSP::LogoutResponse();
    ret->set_success( tmp.first );
    ret->set_reason_for_fail( tmp.second );
    netConnector->sendMessage( ret );
  } );
  netConnector->subscribe( new SSP::DeleteUserRequest(), [&]( google::protobuf::Message const& req ) {
    auto tmp = loginServer.deleteUser( dynamic_cast< SSP::DeleteUserRequest const& >( req ).username(),
                                       dynamic_cast< SSP::DeleteUserRequest const& >( req ).password_hash() );
    auto ret = new SSP::DeleteUserResponse();
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
