#include "SFG/SystemSimulator/LuigiInterface/Types/Version.h"

// Project includes
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

// C++ includes
#include <sstream>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace Types {

Version Version::fromString( std::string const& str ) {
  Version ret;

  char dot;
  std::istringstream iss( str );
  if( !( iss >> ret.major >> dot >> ret.minor >> dot >> ret.patch >> dot >> ret.build ) ) {
    // todo: some error happened
  }

  return ret;
}

std::string Version::toString() const {
  return fmt::format( fmt::runtime( "{:d}.{:d}.{:d}.{:d}" ), major, minor, patch, build );
}

}  // namespace Types
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
