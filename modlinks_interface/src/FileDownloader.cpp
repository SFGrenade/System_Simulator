#include "SFG/SystemSimulator/LuigiInterface/FileDownloader.h"

// Project includes
#include <SFG/SystemSimulator/Logger/scopedLogger.h>

// Library includes
#include <httplib.h>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {

std::optional< std::ifstream > FileDownloader::downloadFile( std::string const& address, std::string const& path, std::filesystem::path const& filename ) {
  SFG::SystemSimulator::Logger::spdlogger logger = SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "FileDownloader" );
  Logger::ScopedLogger _( logger,
                          fmt::format( fmt::runtime( "downloadFile( address: {:?}, path: {:?}, filename: {:?} )" ), address, path, filename.string() ),
                          fmt::format( fmt::runtime( "downloadFile()~" ) ) );

  try {
    httplib::Client client( address );
    client.set_follow_location( true );

    if( httplib::stream::Result result = httplib::stream::Get( client, path ) ) {
      {
        std::ofstream fout( filename, std::ios::out | std::ios::binary );
        while( result.next() ) {
          fout.write( result.data(), result.size() );
        }
      }

      return std::ifstream( filename );
    }
  } catch( std::exception& e ) {
    logger->error( fmt::runtime( "downloadFile - Exception: {:s}" ), e.what() );
  }
  return {};
}

}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
