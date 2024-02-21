#include "loggerFactory.h"

namespace SFG {
namespace SystemSimulator {
namespace SettingsInterface {

std::shared_ptr< spdlog::sinks::stdout_color_sink_mt > LoggerFactory::consoleSink_ = nullptr;
std::shared_ptr< spdlog::sinks::basic_file_sink_mt > LoggerFactory::fileSink_ = nullptr;
std::string LoggerFactory::loggerPattern_ = "[%Y-%m-%d %H:%M:%S.%e] [thread %t] [%n] [%l] %v";
std::map< std::string, spdlogger > LoggerFactory::loggers_ = std::map< std::string, spdlogger >();
std::mutex LoggerFactory::loggersMutex_ = std::mutex();

void LoggerFactory::init() {
  LoggerFactory::loggersMutex_.lock();
  LoggerFactory::loggers_.clear();

  LoggerFactory::consoleSink_ = std::make_shared< spdlog::sinks::stdout_color_sink_mt >();
  LoggerFactory::consoleSink_->set_level( spdlog::level::trace );
  LoggerFactory::fileSink_ = std::make_shared< spdlog::sinks::basic_file_sink_mt >( "log.log", true );
  LoggerFactory::fileSink_->set_level( spdlog::level::trace );

  spdlog::sinks_init_list truncatedSinkList = { LoggerFactory::fileSink_, LoggerFactory::consoleSink_ };
  spdlogger mainLogger = std::make_shared< spdlog::logger >( "main", truncatedSinkList.begin(), truncatedSinkList.end() );
  mainLogger->set_level( spdlog::level::trace );
  mainLogger->flush_on( spdlog::level::trace );
  mainLogger->set_pattern( LoggerFactory::loggerPattern_ );
  spdlog::register_logger( mainLogger );
  spdlog::set_default_logger( mainLogger );

  LoggerFactory::loggers_.insert_or_assign( "main", mainLogger );

  LoggerFactory::loggersMutex_.unlock();
}

void LoggerFactory::deinit() {
  LoggerFactory::loggersMutex_.lock();
  LoggerFactory::loggers_.clear();
  LoggerFactory::loggersMutex_.unlock();
  spdlog::shutdown();
}

spdlogger LoggerFactory::get_logger( std::string const& name ) {
  spdlogger ret = nullptr;

  LoggerFactory::loggersMutex_.lock();

  if( LoggerFactory::loggers_.find( name ) != LoggerFactory::loggers_.end() ) {
    ret = LoggerFactory::loggers_.at( name );
  } else {
    spdlog::sinks_init_list truncatedSinkList = { LoggerFactory::fileSink_, LoggerFactory::consoleSink_ };
    ret = std::make_shared< spdlog::logger >( name, truncatedSinkList.begin(), truncatedSinkList.end() );
    ret->set_level( spdlog::level::trace );
    ret->flush_on( spdlog::level::trace );
    ret->set_pattern( LoggerFactory::loggerPattern_ );
    spdlog::register_logger( ret );

    LoggerFactory::loggers_.insert_or_assign( name, ret );
  }

  LoggerFactory::loggersMutex_.unlock();
  return ret;
}

}  // namespace SettingsInterface
}  // namespace SystemSimulator
}  // namespace SFG
