#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/LoginServer/loginServer.h>
#include <string>
#include <thread>
#include <vector>
#include <zmqPb/reqRep.hpp>

void clientThreadFunc( bool* donePtr ) {
  SFG::SystemSimulator::Configuration::Configuration config( "config/login_server.ini" );

  ZmqPb::ReqRep client( config.get< std::string >( "Network", "ServerEndpoint" ), false );

  std::string sessionToken;

  client.subscribe( new SFG::SystemSimulator::ProtoMessages::RegisterResponse(), [&client]( google::protobuf::Message const& rep ) {
    SFG::SystemSimulator::ProtoMessages::RegisterResponse const& actualRep = static_cast< SFG::SystemSimulator::ProtoMessages::RegisterResponse const& >( rep );
    spdlog::info( fmt::runtime( "rep = {}, '{:s}'" ), actualRep.success(), actualRep.reason_for_fail() );

    std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

    SFG::SystemSimulator::ProtoMessages::LoginRequest* nextReq = new SFG::SystemSimulator::ProtoMessages::LoginRequest();
    nextReq->set_username( "TestName" );
    nextReq->set_password_hash( "00000000" );
    client.sendMessage( nextReq );
  } );
  client.subscribe( new SFG::SystemSimulator::ProtoMessages::LoginResponse(), [&client, &sessionToken]( google::protobuf::Message const& rep ) {
    SFG::SystemSimulator::ProtoMessages::LoginResponse const& actualRep = static_cast< SFG::SystemSimulator::ProtoMessages::LoginResponse const& >( rep );
    spdlog::info( fmt::runtime( "rep = {}, '{:s}', '{:s}'" ), actualRep.success(), actualRep.reason_for_fail(), actualRep.session_token() );

    sessionToken = actualRep.session_token();

    std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

    SFG::SystemSimulator::ProtoMessages::CheckSessionRequest* nextReq = new SFG::SystemSimulator::ProtoMessages::CheckSessionRequest();
    nextReq->set_session_token( sessionToken );
    client.sendMessage( nextReq );
  } );
  client.subscribe( new SFG::SystemSimulator::ProtoMessages::CheckSessionResponse(), [&client, &sessionToken]( google::protobuf::Message const& rep ) {
    SFG::SystemSimulator::ProtoMessages::CheckSessionResponse const& actualRep
        = static_cast< SFG::SystemSimulator::ProtoMessages::CheckSessionResponse const& >( rep );
    spdlog::info( fmt::runtime( "rep = {}" ), actualRep.is_valid() );

    std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

    SFG::SystemSimulator::ProtoMessages::LogoutRequest* nextReq = new SFG::SystemSimulator::ProtoMessages::LogoutRequest();
    nextReq->set_session_token( sessionToken );
    client.sendMessage( nextReq );
  } );
  client.subscribe( new SFG::SystemSimulator::ProtoMessages::LogoutResponse(), [&client, donePtr]( google::protobuf::Message const& rep ) {
    SFG::SystemSimulator::ProtoMessages::LogoutResponse const& actualRep = static_cast< SFG::SystemSimulator::ProtoMessages::LogoutResponse const& >( rep );
    spdlog::info( fmt::runtime( "rep = {}, '{:s}'" ), actualRep.success(), actualRep.reason_for_fail() );

    std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

    *donePtr = true;
  } );
  {
    SFG::SystemSimulator::ProtoMessages::RegisterRequest* nextReq = new SFG::SystemSimulator::ProtoMessages::RegisterRequest();
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

void serverThreadFunc( bool* donePtr, SFG::SystemSimulator::LoginServer::LoginServer* serverPtr ) {
  while( !( *donePtr ) ) {
    try {
      serverPtr->run();
    } catch( std::exception const& e ) {
      spdlog::error( fmt::runtime( "error calling server.run: {:s}" ), e.what() );
    }
  }
}

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "testLogs/loginServerTest.log", false );
  std::vector< std::string > args;
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  bool done = false;

  SFG::SystemSimulator::LoginServer::LoginServer server;
  std::thread serverThread( serverThreadFunc, &done, &server );
  std::thread clientThread( clientThreadFunc, &done );

  clientThread.join();
  serverThread.join();

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return 0;
}
