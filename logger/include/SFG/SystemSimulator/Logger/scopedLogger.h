#ifndef LOGGER_SCOPEDLOGGER_H_
#define LOGGER_SCOPEDLOGGER_H_

#include <string>

#include "SFG/SystemSimulator/Logger/_spdlog.h"

namespace SFG {
namespace SystemSimulator {
namespace Logger {

class ScopedLogger {
  public:
  ScopedLogger( spdlogger logger, std::string const& startMessage, std::string const& stopMessage );
  ~ScopedLogger();

  private:
  spdlogger logger_;
  std::string startMessage_;
  std::string stopMessage_;
};

}  // namespace Logger
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* LOGGER_SCOPEDLOGGER_H_ */
