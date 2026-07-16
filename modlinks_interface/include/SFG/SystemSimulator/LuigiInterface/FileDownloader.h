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
  FileDownloader() = delete;
  FileDownloader( FileDownloader const& ) = delete;
  FileDownloader( FileDownloader&& ) = delete;
  FileDownloader& operator=( FileDownloader const& ) = delete;
  FileDownloader& operator=( FileDownloader&& ) = delete;

  static std::optional< std::ifstream > downloadFile( std::string const& address, std::string const& path, std::filesystem::path const& filename );
};

}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
