#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/NetworkMessages/Users.h>
#include <string>
#include <vector>

#include "SFG/SystemSimulator/LoginServer/loginServer.h"
#include "SFG/SystemSimulator/LoginServer/netConnector.h"

namespace SSSNM = SFG::SystemSimulator::NetworkMessages;

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

  netConnector->subscribe( NetworkingHelper::NetworkMessage::from( "SFG.SystemSimulator.NetworkMessages.RegisterRequest", SSSNM::RegisterRequest() ),
                           [&]( NetworkingHelper::NetworkMessage const& req ) {
                             SSSNM::RegisterRequest actualReq = req.to< SSSNM::RegisterRequest >( "SFG.SystemSimulator.NetworkMessages.RegisterRequest" );
                             auto tmp = loginServer.registerUser( actualReq.username, actualReq.password_hash );
                             auto ret = SSSNM::RegisterResponse();
                             ret.success = tmp.first;
                             ret.reason_for_fail = tmp.second;
                             netConnector->sendMessage( NetworkingHelper::NetworkMessage::from( "SFG.SystemSimulator.NetworkMessages.RegisterResponse", ret ) );
                           } );
  netConnector->subscribe( NetworkingHelper::NetworkMessage::from( "SFG.SystemSimulator.NetworkMessages.LoginRequest", SSSNM::LoginRequest() ),
                           [&]( NetworkingHelper::NetworkMessage const& req ) {
                             SSSNM::LoginRequest actualReq = req.to< SSSNM::LoginRequest >( "SFG.SystemSimulator.NetworkMessages.LoginRequest" );
                             auto tmp = loginServer.loginUser( actualReq.username, actualReq.password_hash );
                             auto ret = SSSNM::LoginResponse();
                             ret.success = tmp.first;
                             if( tmp.first )
                               ret.session_token = tmp.second;
                             else
                               ret.reason_for_fail = tmp.second;
                             netConnector->sendMessage( NetworkingHelper::NetworkMessage::from( "SFG.SystemSimulator.NetworkMessages.LoginResponse", ret ) );
                           } );
  netConnector->subscribe( NetworkingHelper::NetworkMessage::from( "SFG.SystemSimulator.NetworkMessages.CheckSessionRequest", SSSNM::CheckSessionRequest() ),
                           [&]( NetworkingHelper::NetworkMessage const& req ) {
                             SSSNM::CheckSessionRequest actualReq
                                 = req.to< SSSNM::CheckSessionRequest >( "SFG.SystemSimulator.NetworkMessages.CheckSessionRequest" );
                             auto tmp = loginServer.checkUserSession( actualReq.session_token );
                             auto ret = SSSNM::CheckSessionResponse();
                             ret.is_valid = tmp.first;
                             netConnector->sendMessage(
                                 NetworkingHelper::NetworkMessage::from( "SFG.SystemSimulator.NetworkMessages.CheckSessionResponse", ret ) );
                           } );
  netConnector->subscribe( NetworkingHelper::NetworkMessage::from( "SFG.SystemSimulator.NetworkMessages.LogoutRequest", SSSNM::LogoutRequest() ),
                           [&]( NetworkingHelper::NetworkMessage const& req ) {
                             SSSNM::LogoutRequest actualReq = req.to< SSSNM::LogoutRequest >( "SFG.SystemSimulator.NetworkMessages.LogoutRequest" );
                             auto tmp = loginServer.logoutUserSession( actualReq.session_token );
                             auto ret = SSSNM::LogoutResponse();
                             ret.success = tmp.first;
                             ret.reason_for_fail = tmp.second;
                             netConnector->sendMessage( NetworkingHelper::NetworkMessage::from( "SFG.SystemSimulator.NetworkMessages.LogoutResponse", ret ) );
                           } );
  netConnector->subscribe( NetworkingHelper::NetworkMessage::from( "SFG.SystemSimulator.NetworkMessages.DeleteUserRequest", SSSNM::DeleteUserRequest() ),
                           [&]( NetworkingHelper::NetworkMessage const& req ) {
                             SSSNM::DeleteUserRequest actualReq = req.to< SSSNM::DeleteUserRequest >( "SFG.SystemSimulator.NetworkMessages.DeleteUserRequest" );
                             auto tmp = loginServer.deleteUser( actualReq.username, actualReq.password_hash );
                             auto ret = SSSNM::DeleteUserResponse();
                             ret.success = tmp.first;
                             ret.reason_for_fail = tmp.second;
                             netConnector->sendMessage(
                                 NetworkingHelper::NetworkMessage::from( "SFG.SystemSimulator.NetworkMessages.DeleteUserResponse", ret ) );
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
