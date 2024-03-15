#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/LoginServer/loginServer.h>
#include <SFG/SystemSimulator/LoginServer/netConnector.h>
#include <string>
#include <thread>
#include <vector>
#include <zmqPb/reqRep.hpp>

namespace SSP = SFG::SystemSimulator::ProtoMessages;

void clientThreadFunc( bool* donePtr ) {
  SFG::SystemSimulator::Configuration::Configuration config( "config/login_server.ini" );

  ZmqPb::ReqRep client( config.get< std::string >( "Network", "ServerEndpoint" ), false );

  std::string sessionToken;

  client.subscribe( new SSP::RegisterResponse(), [&client]( google::protobuf::Message const& rep ) {
    SSP::RegisterResponse const& actualRep = static_cast< SSP::RegisterResponse const& >( rep );
    spdlog::info( fmt::runtime( "rep = '{:s}'" ), rep.DebugString() );

    std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

    SSP::LoginRequest* nextReq = new SSP::LoginRequest();
    nextReq->set_username( "TestName" );
    nextReq->set_password_hash( "00000000" );
    client.sendMessage( nextReq );
  } );
  client.subscribe( new SSP::LoginResponse(), [&client, &sessionToken]( google::protobuf::Message const& rep ) {
    SSP::LoginResponse const& actualRep = static_cast< SSP::LoginResponse const& >( rep );
    spdlog::info( fmt::runtime( "rep = '{:s}'" ), rep.DebugString() );

    sessionToken = actualRep.session_token();

    std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

    SSP::CheckSessionRequest* nextReq = new SSP::CheckSessionRequest();
    nextReq->set_session_token( sessionToken );
    client.sendMessage( nextReq );
  } );
  client.subscribe( new SSP::CheckSessionResponse(), [&client, &sessionToken]( google::protobuf::Message const& rep ) {
    SSP::CheckSessionResponse const& actualRep = static_cast< SSP::CheckSessionResponse const& >( rep );
    spdlog::info( fmt::runtime( "rep = '{:s}'" ), rep.DebugString() );

    std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

    SSP::LogoutRequest* nextReq = new SSP::LogoutRequest();
    nextReq->set_session_token( sessionToken );
    client.sendMessage( nextReq );
  } );
  client.subscribe( new SSP::LogoutResponse(), [&client, donePtr]( google::protobuf::Message const& rep ) {
    SSP::LogoutResponse const& actualRep = static_cast< SSP::LogoutResponse const& >( rep );
    spdlog::info( fmt::runtime( "rep = '{:s}'" ), rep.DebugString() );

    std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

    SSP::DeleteUserRequest* nextReq = new SSP::DeleteUserRequest();
    nextReq->set_username( "TestName" );
    nextReq->set_password_hash( "00000000" );
    client.sendMessage( nextReq );
  } );
  client.subscribe( new SSP::DeleteUserResponse(), [&client, donePtr]( google::protobuf::Message const& rep ) {
    SSP::DeleteUserResponse const& actualRep = static_cast< SSP::DeleteUserResponse const& >( rep );
    spdlog::info( fmt::runtime( "rep = '{:s}'" ), rep.DebugString() );

    std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

    *donePtr = true;
  } );
  {
    SSP::RegisterRequest* nextReq = new SSP::RegisterRequest();
    nextReq->set_username( "TestName" );
    nextReq->set_password_hash( "00000000" );
    client.sendMessage( nextReq );
  }
  while( !( *donePtr ) ) {
    try {
      client.run();
    } catch( std::exception const& e ) {
      spdlog::error( fmt::runtime( "error calling server.run: {:s}" ), e.what() );
    }
  }
}

void serverThreadFunc( bool* donePtr, SFG::SystemSimulator::LoginServer::LoginServer* serverPtr, SFG::SystemSimulator::LoginServer::NetConnector* netConPtr ) {
  while( !( *donePtr ) ) {
    try {
      ( *netConPtr )->run();
    } catch( std::exception const& e ) {
      spdlog::error( fmt::runtime( "error calling server.run: {:s}" ), e.what() );
    }
  }
}

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "testLogs/loginServerNetworkTest.log", false );
  std::vector< std::string > args;
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  bool done = false;

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

  std::thread serverThread( serverThreadFunc, &done, &loginServer, &netConnector );
  std::thread clientThread( clientThreadFunc, &done );

  clientThread.join();
  serverThread.join();

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return 0;
}
