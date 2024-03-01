#include "SFG/SystemSimulator/LoginServer/loginServer.h"

namespace SFG {
namespace SystemSimulator {
namespace LoginServer {

LoginServer::LoginServer()
    : logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "LoginServer" ) ), reqRepServer_( "tcp://localhost:13337", true ) {
  reqRepServer_.subscribe( new SFG::SystemSimulator::ProtoMessages::LoginRequest(), [this]( google::protobuf::Message const& req ) {
    this->onLogin( static_cast< SFG::SystemSimulator::ProtoMessages::LoginRequest const& >( req ) );
  } );
  reqRepServer_.subscribe( new SFG::SystemSimulator::ProtoMessages::CheckSessionRequest(), [this]( google::protobuf::Message const& req ) {
    this->onCheckSession( static_cast< SFG::SystemSimulator::ProtoMessages::CheckSessionRequest const& >( req ) );
  } );
  reqRepServer_.subscribe( new SFG::SystemSimulator::ProtoMessages::LogoutRequest(), [this]( google::protobuf::Message const& req ) {
    this->onLogout( static_cast< SFG::SystemSimulator::ProtoMessages::LogoutRequest const& >( req ) );
  } );
}

LoginServer::~LoginServer() {}

void LoginServer::run() {
  reqRepServer_.run();
}

void LoginServer::onLogin( SFG::SystemSimulator::ProtoMessages::LoginRequest const& req ) {
  SFG::SystemSimulator::ProtoMessages::LoginResponse* rep = new SFG::SystemSimulator::ProtoMessages::LoginResponse();
  this->reqRepServer_.sendMessage( rep );
}

void LoginServer::onCheckSession( SFG::SystemSimulator::ProtoMessages::CheckSessionRequest const& req ) {
  SFG::SystemSimulator::ProtoMessages::CheckSessionResponse* rep = new SFG::SystemSimulator::ProtoMessages::CheckSessionResponse();
  this->reqRepServer_.sendMessage( rep );
}

void LoginServer::onLogout( SFG::SystemSimulator::ProtoMessages::LogoutRequest const& req ) {
  SFG::SystemSimulator::ProtoMessages::LogoutResponse* rep = new SFG::SystemSimulator::ProtoMessages::LogoutResponse();
  this->reqRepServer_.sendMessage( rep );
}

}  // namespace LoginServer
}  // namespace SystemSimulator
}  // namespace SFG
