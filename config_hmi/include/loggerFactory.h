#ifndef CONFIG_HMI_LOGGERFACTORY_H_
#define CONFIG_HMI_LOGGERFACTORY_H_

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "_spdlog.h"

namespace SFG {
namespace SystemSimulator {
namespace ConfigHmi {

class LoggerFactory {
  public:
  static void init();
  static void deinit();

  static spdlogger get_logger( std::string const& name );

  private:
  static std::shared_ptr< spdlog::sinks::stdout_color_sink_mt > consoleSink_;
  static std::shared_ptr< spdlog::sinks::basic_file_sink_mt > fileSink_;
  static std::string loggerPattern_;
  static std::map< std::string, spdlogger > loggers_;
  static std::mutex loggersMutex_;
};

}  // namespace ConfigHmi
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* CONFIG_HMI_LOGGERFACTORY_H_ */
