#include "SFG/SystemSimulator/RecordingServer/netConnector.h"

namespace SFG {
namespace SystemSimulator {
namespace RecordingServer {

NetConnector::NetConnector()
    : logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "NetConnector" ) ),
      config_( "config/recording_server.ini" ),
      pushPullReceiver_( config_.get< std::string >( "Network", "ServerEndpoint" ), false ) {
  this->logger_->trace( fmt::runtime( "NetConnector" ) );

  this->logger_->trace( fmt::runtime( "NetConnector~" ) );
}

NetConnector::~NetConnector() {
  this->logger_->trace( fmt::runtime( "~NetConnector" ) );

  this->logger_->trace( fmt::runtime( "~NetConnector~" ) );
}

ZmqPb::PushPull* NetConnector::operator->() const {
  return const_cast< ZmqPb::PushPull* >( &( this->pushPullReceiver_ ) );
}

}  // namespace RecordingServer
}  // namespace SystemSimulator
}  // namespace SFG
