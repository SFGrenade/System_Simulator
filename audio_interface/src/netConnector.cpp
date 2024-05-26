#include "SFG/SystemSimulator/AudioInterface/netConnector.h"

namespace SFG {
namespace SystemSimulator {
namespace AudioInterface {

NetConnector::NetConnector()
    : logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "NetConnector" ) ),
      config_( "config/recording_server.ini" ),
      pushPullSender_( config_.get< std::string >( "Network", "ServerEndpoint" ), true ) {
  this->logger_->trace( fmt::runtime( "NetConnector" ) );

  this->logger_->trace( fmt::runtime( "NetConnector~" ) );
}

NetConnector::~NetConnector() {
  this->logger_->trace( fmt::runtime( "~NetConnector" ) );

  this->logger_->trace( fmt::runtime( "~NetConnector~" ) );
}

ZmqPb::PushPull* NetConnector::operator->() const {
  return const_cast< ZmqPb::PushPull* >( &( this->pushPullSender_ ) );
}

}  // namespace AudioInterface
}  // namespace SystemSimulator
}  // namespace SFG
