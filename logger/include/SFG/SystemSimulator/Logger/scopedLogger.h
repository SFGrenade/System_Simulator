#ifndef LOGGER_LOGGERFACTORY_H_
#define LOGGER_LOGGERFACTORY_H_

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "SFG/SystemSimulator/Logger/_spdlog.h"

namespace SFG {
namespace SystemSimulator {
namespace Logger {

class ScopedLog {
  public:
  ScopedLog( spdlogger logger, std::string const& startMessage, std::string const& stopMessage );
  ~ScopedLog();

  private:
  spdlogger logger_;
  std::string startMessage_;
  std::string stopMessage_;
};

}  // namespace Logger
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* LOGGER_LOGGERFACTORY_H_ */
