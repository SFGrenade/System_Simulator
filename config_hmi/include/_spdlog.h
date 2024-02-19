#ifndef CONFIG_HMI_SPDLOG_H_
#define CONFIG_HMI_SPDLOG_H_

#include <memory>
#include <string>

// Including FMT headers
#include <fmt/chrono.h>
#include <fmt/core.h>

// Including SPDLOG headers
#ifndef SPDLOG_FMT_EXTERNAL
#define SPDLOG_FMT_EXTERNAL
#endif
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

typedef std::shared_ptr< spdlog::logger > spdlogger;

class ScopedLog {
  public:
  ScopedLog( spdlogger logger, std::string const& startMessage, std::string const& stopMessage );
  ~ScopedLog();

  private:
  spdlogger logger_;
  std::string startMessage_;
  std::string stopMessage_;
};

#endif /* CONFIG_HMI_SPDLOG_H_ */
