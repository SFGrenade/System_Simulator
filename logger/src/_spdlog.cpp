#include "SFG/SystemSimulator/Logger/_spdlog.h"

namespace SFG {
namespace SystemSimulator {
namespace Logger {

ScopedLog::ScopedLog( spdlogger logger, std::string const& startMessage, std::string const& stopMessage )
    : logger_( logger ), startMessage_( startMessage ), stopMessage_( stopMessage ) {
  this->logger_->trace( this->startMessage_ );
}

ScopedLog::~ScopedLog() {
  this->logger_->trace( this->stopMessage_ );
}

}  // namespace Logger
}  // namespace SystemSimulator
}  // namespace SFG
