#include "SFG/SystemSimulator/Logger/ScopedLogger.h"

namespace SFG {
namespace SystemSimulator {
namespace Logger {

ScopedLogger::ScopedLogger( spdlogger logger, std::string const& startMessage, std::string const& stopMessage )
    : logger_( logger ), startMessage_( startMessage ), stopMessage_( stopMessage ) {
  this->logger_->trace( fmt::runtime( this->startMessage_ ) );
}

ScopedLogger::~ScopedLogger() {
  this->logger_->trace( fmt::runtime( this->stopMessage_ ) );
}

}  // namespace Logger
}  // namespace SystemSimulator
}  // namespace SFG
