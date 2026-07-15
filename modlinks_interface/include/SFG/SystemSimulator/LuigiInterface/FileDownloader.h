#pragma once

// Project includes
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

// C++ includes
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {

class FileDownloader {
  public:
  explicit FileDownloader();
  ~FileDownloader();

  std::optional< std::ifstream > downloadFile( std::string const& address, std::string const& path, std::filesystem::path const& filename );

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
};

}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
