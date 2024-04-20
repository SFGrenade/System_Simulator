#include <SFG/SystemSimulator/NetworkMessages/Audio.h>
#include <SFG/SystemSimulator/NetworkMessages/Database.h>
#include <SFG/SystemSimulator/NetworkMessages/Users.h>
#include <boostNng/networkMessage.hpp>
#include <gtest/gtest.h>

TEST( NetworkMessages, AudioFormatInformation ) {
  SFG::SystemSimulator::NetworkMessages::AudioFormatInformation message;
  EXPECT_EQ( message, BoostNng::NetworkMessage::from< decltype( message ) >( message ).to< decltype( message ) >() );
}

TEST( NetworkMessages, AudioFrame ) {
  SFG::SystemSimulator::NetworkMessages::AudioFrame message;
  EXPECT_EQ( message, BoostNng::NetworkMessage::from< decltype( message ) >( message ).to< decltype( message ) >() );
}

TEST( NetworkMessages, MsgContent ) {
  SFG::SystemSimulator::NetworkMessages::MsgContent message;
  EXPECT_EQ( message, BoostNng::NetworkMessage::from< decltype( message ) >( message ).to< decltype( message ) >() );
}

TEST( NetworkMessages, RegisterRequest ) {
  SFG::SystemSimulator::NetworkMessages::RegisterRequest message;
  EXPECT_EQ( message, BoostNng::NetworkMessage::from< decltype( message ) >( message ).to< decltype( message ) >() );
}

TEST( NetworkMessages, RegisterResponse ) {
  SFG::SystemSimulator::NetworkMessages::RegisterResponse message;
  EXPECT_EQ( message, BoostNng::NetworkMessage::from< decltype( message ) >( message ).to< decltype( message ) >() );
}

TEST( NetworkMessages, LoginRequest ) {
  SFG::SystemSimulator::NetworkMessages::LoginRequest message;
  EXPECT_EQ( message, BoostNng::NetworkMessage::from< decltype( message ) >( message ).to< decltype( message ) >() );
}

TEST( NetworkMessages, LoginResponse ) {
  SFG::SystemSimulator::NetworkMessages::LoginResponse message;
  EXPECT_EQ( message, BoostNng::NetworkMessage::from< decltype( message ) >( message ).to< decltype( message ) >() );
}

TEST( NetworkMessages, CheckSessionRequest ) {
  SFG::SystemSimulator::NetworkMessages::CheckSessionRequest message;
  EXPECT_EQ( message, BoostNng::NetworkMessage::from< decltype( message ) >( message ).to< decltype( message ) >() );
}

TEST( NetworkMessages, CheckSessionResponse ) {
  SFG::SystemSimulator::NetworkMessages::CheckSessionResponse message;
  EXPECT_EQ( message, BoostNng::NetworkMessage::from< decltype( message ) >( message ).to< decltype( message ) >() );
}

TEST( NetworkMessages, LogoutRequest ) {
  SFG::SystemSimulator::NetworkMessages::LogoutRequest message;
  EXPECT_EQ( message, BoostNng::NetworkMessage::from< decltype( message ) >( message ).to< decltype( message ) >() );
}

TEST( NetworkMessages, LogoutResponse ) {
  SFG::SystemSimulator::NetworkMessages::LogoutResponse message;
  EXPECT_EQ( message, BoostNng::NetworkMessage::from< decltype( message ) >( message ).to< decltype( message ) >() );
}

TEST( NetworkMessages, DeleteUserRequest ) {
  SFG::SystemSimulator::NetworkMessages::DeleteUserRequest message;
  EXPECT_EQ( message, BoostNng::NetworkMessage::from< decltype( message ) >( message ).to< decltype( message ) >() );
}

TEST( NetworkMessages, DeleteUserResponse ) {
  SFG::SystemSimulator::NetworkMessages::DeleteUserResponse message;
  EXPECT_EQ( message, BoostNng::NetworkMessage::from< decltype( message ) >( message ).to< decltype( message ) >() );
}
