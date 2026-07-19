#include "SFG/SystemSimulator/LuigiInterface/Types/Version.h"

// Project includes
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

// C++ includes
#include <sstream>
#include <tuple>

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

bool operator==( Version const& a, Version const& b ) {
  return ( a.major == b.major ) && ( a.minor == b.minor ) && ( a.patch == b.patch ) && ( a.build == b.build );
}
bool operator!=( Version const& a, Version const& b ) {
  return !( a == b );
}
bool operator<( Version const& a, Version const& b ) {
  return std::tie( a.major, a.minor, a.patch, a.build ) < std::tie( b.major, b.minor, b.patch, b.build );
}
bool operator>( Version const& a, Version const& b ) {
  return b < a;
}
bool operator<=( Version const& a, Version const& b ) {
  return !( a > b );
}
bool operator>=( Version const& a, Version const& b ) {
  return !( b < a );
}

}  // namespace Types
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
