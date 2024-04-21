#include <SFG/SystemSimulator/NetworkMessages/Audio.h>
#include <SFG/SystemSimulator/NetworkMessages/Database.h>
#include <SFG/SystemSimulator/NetworkMessages/Users.h>
#include <gtest/gtest.h>
#include <networkingHelper/networkMessage.hpp>

TEST( NetworkMessages, AudioFormatInformation ) {
  SFG::SystemSimulator::NetworkMessages::AudioFormatInformation message;
  EXPECT_EQ( message,
             NetworkingHelper::NetworkMessage::from< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::AudioFormatInformation", message )
                 .to< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::AudioFormatInformation" ) );
}

TEST( NetworkMessages, AudioFrame ) {
  SFG::SystemSimulator::NetworkMessages::AudioFrame message;
  EXPECT_EQ( message,
             NetworkingHelper::NetworkMessage::from< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::AudioFrame", message )
                 .to< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::AudioFrame" ) );
}

TEST( NetworkMessages, MsgContent ) {
  SFG::SystemSimulator::NetworkMessages::MsgContent message;
  EXPECT_EQ( message,
             NetworkingHelper::NetworkMessage::from< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::MsgContent", message )
                 .to< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::MsgContent" ) );
}

TEST( NetworkMessages, RegisterRequest ) {
  SFG::SystemSimulator::NetworkMessages::RegisterRequest message;
  EXPECT_EQ( message,
             NetworkingHelper::NetworkMessage::from< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::RegisterRequest", message )
                 .to< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::RegisterRequest" ) );
}

TEST( NetworkMessages, RegisterResponse ) {
  SFG::SystemSimulator::NetworkMessages::RegisterResponse message;
  EXPECT_EQ( message,
             NetworkingHelper::NetworkMessage::from< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::RegisterResponse", message )
                 .to< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::RegisterResponse" ) );
}

TEST( NetworkMessages, LoginRequest ) {
  SFG::SystemSimulator::NetworkMessages::LoginRequest message;
  EXPECT_EQ( message,
             NetworkingHelper::NetworkMessage::from< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::LoginRequest", message )
                 .to< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::LoginRequest" ) );
}

TEST( NetworkMessages, LoginResponse ) {
  SFG::SystemSimulator::NetworkMessages::LoginResponse message;
  EXPECT_EQ( message,
             NetworkingHelper::NetworkMessage::from< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::LoginResponse", message )
                 .to< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::LoginResponse" ) );
}

TEST( NetworkMessages, CheckSessionRequest ) {
  SFG::SystemSimulator::NetworkMessages::CheckSessionRequest message;
  EXPECT_EQ( message,
             NetworkingHelper::NetworkMessage::from< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::CheckSessionRequest", message )
                 .to< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::CheckSessionRequest" ) );
}

TEST( NetworkMessages, CheckSessionResponse ) {
  SFG::SystemSimulator::NetworkMessages::CheckSessionResponse message;
  EXPECT_EQ( message,
             NetworkingHelper::NetworkMessage::from< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::CheckSessionResponse", message )
                 .to< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::CheckSessionResponse" ) );
}

TEST( NetworkMessages, LogoutRequest ) {
  SFG::SystemSimulator::NetworkMessages::LogoutRequest message;
  EXPECT_EQ( message,
             NetworkingHelper::NetworkMessage::from< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::LogoutRequest", message )
                 .to< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::LogoutRequest" ) );
}

TEST( NetworkMessages, LogoutResponse ) {
  SFG::SystemSimulator::NetworkMessages::LogoutResponse message;
  EXPECT_EQ( message,
             NetworkingHelper::NetworkMessage::from< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::LogoutResponse", message )
                 .to< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::LogoutResponse" ) );
}

TEST( NetworkMessages, DeleteUserRequest ) {
  SFG::SystemSimulator::NetworkMessages::DeleteUserRequest message;
  EXPECT_EQ( message,
             NetworkingHelper::NetworkMessage::from< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::DeleteUserRequest", message )
                 .to< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::DeleteUserRequest" ) );
}

TEST( NetworkMessages, DeleteUserResponse ) {
  SFG::SystemSimulator::NetworkMessages::DeleteUserResponse message;
  EXPECT_EQ( message,
             NetworkingHelper::NetworkMessage::from< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::DeleteUserResponse", message )
                 .to< decltype( message ) >( "SFG::SystemSimulator::NetworkMessages::DeleteUserResponse" ) );
}
