#include "SFG/SystemSimulator/LoginServer/netConnector.h"

namespace SFG {
namespace SystemSimulator {
namespace LoginServer {

NetConnector::NetConnector()
    : logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "NetConnector" ) ),
      config_( "config/login_server.ini" ),
      reqRepServer_( config_.get< std::string >( "Network", "ServerEndpoint" ), true ) {
  this->logger_->trace( fmt::runtime( "NetConnector" ) );

  this->logger_->trace( fmt::runtime( "NetConnector~" ) );
}

NetConnector::~NetConnector() {
  this->logger_->trace( fmt::runtime( "~NetConnector" ) );

  this->logger_->trace( fmt::runtime( "~NetConnector~" ) );
}

NetworkingHelper::ReqRep* NetConnector::operator->() const {
  return const_cast< NetworkingHelper::ReqRep* >( &( this->reqRepServer_ ) );
}

}  // namespace LoginServer
}  // namespace SystemSimulator
}  // namespace SFG
