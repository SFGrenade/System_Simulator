#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/LoginServer/loginServer.h>
#include <SFG/SystemSimulator/LoginServer/netConnector.h>
#include <gtest/gtest.h>
#include <string>
#include <thread>
#include <vector>

// // todo
// namespace SSP = SFG::SystemSimulator::ProtoMessages;
//
// void networkClientThreadFunc( bool* donePtr ) {
//   SFG::SystemSimulator::Configuration::Configuration config( "config/login_server.ini" );
//
//   ZmqPb::ReqRep client( config.get< std::string >( "Network", "ServerEndpoint" ), false );
//
//   std::string sessionToken;
//
//   client.subscribe( new SSP::RegisterResponse(), [&client]( google::protobuf::Message const& rep ) {
//     SSP::RegisterResponse const& actualRep = static_cast< SSP::RegisterResponse const& >( rep );
//     spdlog::info( fmt::runtime( "rep = '{:s}'" ), rep.DebugString() );
//
//     std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
//
//     SSP::LoginRequest* nextReq = new SSP::LoginRequest();
//     nextReq->set_username( "TestName" );
//     nextReq->set_password_hash( "00000000" );
//     client.sendMessage( nextReq );
//   } );
//   client.subscribe( new SSP::LoginResponse(), [&client, &sessionToken]( google::protobuf::Message const& rep ) {
//     SSP::LoginResponse const& actualRep = static_cast< SSP::LoginResponse const& >( rep );
//     spdlog::info( fmt::runtime( "rep = '{:s}'" ), rep.DebugString() );
//
//     sessionToken = actualRep.session_token();
//
//     std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
//
//     SSP::CheckSessionRequest* nextReq = new SSP::CheckSessionRequest();
//     nextReq->set_session_token( sessionToken );
//     client.sendMessage( nextReq );
//   } );
//   client.subscribe( new SSP::CheckSessionResponse(), [&client, &sessionToken]( google::protobuf::Message const& rep ) {
//     SSP::CheckSessionResponse const& actualRep = static_cast< SSP::CheckSessionResponse const& >( rep );
//     spdlog::info( fmt::runtime( "rep = '{:s}'" ), rep.DebugString() );
//
//     std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
//
//     SSP::LogoutRequest* nextReq = new SSP::LogoutRequest();
//     nextReq->set_session_token( sessionToken );
//     client.sendMessage( nextReq );
//   } );
//   client.subscribe( new SSP::LogoutResponse(), [&client, donePtr]( google::protobuf::Message const& rep ) {
//     SSP::LogoutResponse const& actualRep = static_cast< SSP::LogoutResponse const& >( rep );
//     spdlog::info( fmt::runtime( "rep = '{:s}'" ), rep.DebugString() );
//
//     std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
//
//     SSP::DeleteUserRequest* nextReq = new SSP::DeleteUserRequest();
//     nextReq->set_username( "TestName" );
//     nextReq->set_password_hash( "00000000" );
//     client.sendMessage( nextReq );
//   } );
//   client.subscribe( new SSP::DeleteUserResponse(), [&client, donePtr]( google::protobuf::Message const& rep ) {
//     SSP::DeleteUserResponse const& actualRep = static_cast< SSP::DeleteUserResponse const& >( rep );
//     spdlog::info( fmt::runtime( "rep = '{:s}'" ), rep.DebugString() );
//
//     std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
//
//     *donePtr = true;
//   } );
//   {
//     SSP::RegisterRequest* nextReq = new SSP::RegisterRequest();
//     nextReq->set_username( "TestName" );
//     nextReq->set_password_hash( "00000000" );
//     client.sendMessage( nextReq );
//   }
//   while( !( *donePtr ) ) {
//     try {
//       client.run();
//     } catch( std::exception const& e ) {
//       spdlog::error( fmt::runtime( "error calling server.run: {:s}" ), e.what() );
//     }
//   }
// }
//
// void networkServerThreadFunc( bool* donePtr,
//                               SFG::SystemSimulator::LoginServer::LoginServer* serverPtr,
//                               SFG::SystemSimulator::LoginServer::NetConnector* netConPtr ) {
//   while( !( *donePtr ) ) {
//     try {
//       ( *netConPtr )->run();
//     } catch( std::exception const& e ) {
//       spdlog::error( fmt::runtime( "error calling server.run: {:s}" ), e.what() );
//     }
//   }
// }

TEST( LoginServer, FullTest ) {
  std::pair< bool, std::string > tmp;

  SFG::SystemSimulator::Configuration::Configuration config( "config/login_server.ini" );
  SFG::SystemSimulator::LoginServer::LoginServer server;

  // REGULAR TEST
  spdlog::info( fmt::runtime( "!!! - REGULAR TEST - !!!" ) );
  spdlog::info( fmt::runtime( "!!! - REGULAR TEST - !!!" ) );
  spdlog::info( fmt::runtime( "!!! - REGULAR TEST - !!!" ) );
  // REGULAR TEST

  tmp = server.registerUser( "TestUser", "MyPassword" );
  spdlog::debug( fmt::runtime( "tmp = {}, '{:s}'" ), tmp.first, tmp.second );
  EXPECT_TRUE( tmp.first ) << tmp.second;

  server.printDebugInfo();

  tmp = server.loginUser( "TestUser", "MyPassword" );
  spdlog::debug( fmt::runtime( "tmp = {}, '{:s}'" ), tmp.first, tmp.second );
  EXPECT_TRUE( tmp.first ) << tmp.second;
  std::string userSessionToken = tmp.second;

  server.printDebugInfo();

  tmp = server.checkUserSession( userSessionToken );
  spdlog::debug( fmt::runtime( "tmp = {}, '{:s}'" ), tmp.first, tmp.second );
  EXPECT_TRUE( tmp.first ) << tmp.second;

  server.printDebugInfo();

  tmp = server.logoutUserSession( userSessionToken );
  spdlog::debug( fmt::runtime( "tmp = {}, '{:s}'" ), tmp.first, tmp.second );
  EXPECT_TRUE( tmp.first ) << tmp.second;

  server.printDebugInfo();

  tmp = server.deleteUser( "TestUser", "MyPassword" );
  spdlog::debug( fmt::runtime( "tmp = {}, '{:s}'" ), tmp.first, tmp.second );
  EXPECT_TRUE( tmp.first ) << tmp.second;

  server.printDebugInfo();

  // TIMEOUT TEST
  spdlog::info( fmt::runtime( "!!! - TIMEOUT TEST - !!!" ) );
  spdlog::info( fmt::runtime( "!!! - TIMEOUT TEST - !!!" ) );
  spdlog::info( fmt::runtime( "!!! - TIMEOUT TEST - !!!" ) );
  // TIMEOUT TEST

  tmp = server.registerUser( "TestUser", "MyPassword" );
  spdlog::debug( fmt::runtime( "tmp = {}, '{:s}'" ), tmp.first, tmp.second );
  EXPECT_TRUE( tmp.first ) << tmp.second;

  server.printDebugInfo();

  tmp = server.loginUser( "TestUser", "MyPassword" );
  spdlog::debug( fmt::runtime( "tmp = {}, '{:s}'" ), tmp.first, tmp.second );
  EXPECT_TRUE( tmp.first ) << tmp.second;
  userSessionToken = tmp.second;

  server.printDebugInfo();

  std::this_thread::sleep_for( std::chrono::seconds( config.get< uint32_t >( "Database", "SessionTokenValidTime" ) + 1 ) );

  tmp = server.checkUserSession( userSessionToken );
  spdlog::debug( fmt::runtime( "tmp = {}, '{:s}'" ), tmp.first, tmp.second );
  EXPECT_FALSE( tmp.first ) << "Session valid despite fact it shouldn't be.";

  server.printDebugInfo();

  tmp = server.deleteUser( "TestUser", "MyPassword" );
  spdlog::debug( fmt::runtime( "tmp = {}, '{:s}'" ), tmp.first, tmp.second );
  EXPECT_TRUE( tmp.first ) << tmp.second;

  server.printDebugInfo();

  // // todo
  // // NETWORK TEST
  // spdlog::info( fmt::runtime( "!!! - NETWORK TEST - !!!" ) );
  // spdlog::info( fmt::runtime( "!!! - NETWORK TEST - !!!" ) );
  // spdlog::info( fmt::runtime( "!!! - NETWORK TEST - !!!" ) );
  // // NETWORK TEST
  //
  // bool done = false;
  //
  // SFG::SystemSimulator::LoginServer::NetConnector netConnector;
  // netConnector->subscribe( new SSP::RegisterRequest(), [&]( google::protobuf::Message const& req ) {
  //   auto tmp = server.registerUser( dynamic_cast< SSP::RegisterRequest const& >( req ).username(),
  //                                        dynamic_cast< SSP::RegisterRequest const& >( req ).password_hash() );
  //   auto ret = new SSP::RegisterResponse();
  //   ret->set_success( tmp.first );
  //   ret->set_reason_for_fail( tmp.second );
  //   netConnector->sendMessage( ret );
  //
  //   server.printDebugInfo();
  // } );
  // netConnector->subscribe( new SSP::LoginRequest(), [&]( google::protobuf::Message const& req ) {
  //   auto tmp
  //       = server.loginUser( dynamic_cast< SSP::LoginRequest const& >( req ).username(), dynamic_cast< SSP::LoginRequest const& >( req ).password_hash()
  //       );
  //   auto ret = new SSP::LoginResponse();
  //   ret->set_success( tmp.first );
  //   if( tmp.first )
  //     ret->set_session_token( tmp.second );
  //   else
  //     ret->set_reason_for_fail( tmp.second );
  //   netConnector->sendMessage( ret );
  //
  //   server.printDebugInfo();
  // } );
  // netConnector->subscribe( new SSP::CheckSessionRequest(), [&]( google::protobuf::Message const& req ) {
  //   auto tmp = server.checkUserSession( dynamic_cast< SSP::CheckSessionRequest const& >( req ).session_token() );
  //   auto ret = new SSP::CheckSessionResponse();
  //   ret->set_is_valid( tmp.first );
  //   netConnector->sendMessage( ret );
  //
  //   server.printDebugInfo();
  // } );
  // netConnector->subscribe( new SSP::LogoutRequest(), [&]( google::protobuf::Message const& req ) {
  //   auto tmp = server.logoutUserSession( dynamic_cast< SSP::LogoutRequest const& >( req ).session_token() );
  //   auto ret = new SSP::LogoutResponse();
  //   ret->set_success( tmp.first );
  //   ret->set_reason_for_fail( tmp.second );
  //   netConnector->sendMessage( ret );
  //
  //   server.printDebugInfo();
  // } );
  // netConnector->subscribe( new SSP::DeleteUserRequest(), [&]( google::protobuf::Message const& req ) {
  //   auto tmp = server.deleteUser( dynamic_cast< SSP::DeleteUserRequest const& >( req ).username(),
  //                                      dynamic_cast< SSP::DeleteUserRequest const& >( req ).password_hash() );
  //   auto ret = new SSP::DeleteUserResponse();
  //   ret->set_success( tmp.first );
  //   ret->set_reason_for_fail( tmp.second );
  //   netConnector->sendMessage( ret );
  //
  //   server.printDebugInfo();
  // } );
  //
  // std::thread serverThread( serverThreadFunc, &done, &server, &netConnector );
  // std::thread clientThread( clientThreadFunc, &done );
  //
  // clientThread.join();
  // serverThread.join();

  // MASSIVE DATA TEST
  spdlog::info( fmt::runtime( "!!! - MASSIVE DATA TEST - !!!" ) );
  spdlog::info( fmt::runtime( "!!! - MASSIVE DATA TEST - !!!" ) );
  spdlog::info( fmt::runtime( "!!! - MASSIVE DATA TEST - !!!" ) );
  // MASSIVE DATA TEST

  std::stringstream usernameStream;
  std::stringstream passwordHashStream;

  for( int i = 1; i <= 200; i++ ) {
    spdlog::trace( fmt::runtime( "Loop {:d}" ), i );

    usernameStream << "A";
    passwordHashStream << "0";

    tmp = server.registerUser( usernameStream.str(), passwordHashStream.str() );
    spdlog::debug( fmt::runtime( "tmp = {}, '{:s}'" ), tmp.first, tmp.second );
    if( ( i <= 128 ) )
      EXPECT_TRUE( tmp.first ) << tmp.second;
    if( ( i > 128 ) && ( tmp.first ) )
      EXPECT_FALSE( tmp.first ) << "User shouldn't have been created";
  }
  server.printDebugInfo();
}

TEST( LoginServer, NetworkTest ) {
  // content
}

TEST( LoginServer, MassiveDataTest ) {
  // content
}
