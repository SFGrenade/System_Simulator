#ifndef LOGGER_SPDLOG_H_
#define LOGGER_SPDLOG_H_

#include <memory>
#include <string>

// Including FMT headers
#include <fmt/base.h>
#include <fmt/chrono.h>
#include <fmt/format.h>
#include <fmt/ranges.h>

// Including SPDLOG headers
#ifndef SPDLOG_FMT_EXTERNAL
#define SPDLOG_FMT_EXTERNAL
#endif
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace SFG {
namespace SystemSimulator {
namespace Logger {

typedef std::shared_ptr< spdlog::logger > spdlogger;

}  // namespace Logger
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* LOGGER_SPDLOG_H_ */
