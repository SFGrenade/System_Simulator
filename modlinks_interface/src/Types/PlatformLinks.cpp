#include "SFG/SystemSimulator/LuigiInterface/Types/PlatformLinks.h"

// C++ includes
#include <tuple>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace Types {

bool operator==( PlatformLinks const& a, PlatformLinks const& b ) {
  return ( a.linux == b.linux ) && ( a.mac == b.mac ) && ( a.windows == b.windows );
}
bool operator!=( PlatformLinks const& a, PlatformLinks const& b ) {
  return !( a == b );
}
bool operator<( PlatformLinks const& a, PlatformLinks const& b ) {
  return std::tie( a.linux, a.mac, a.windows ) < std::tie( b.linux, b.mac, b.windows );
}
bool operator>( PlatformLinks const& a, PlatformLinks const& b ) {
  return b < a;
}
bool operator<=( PlatformLinks const& a, PlatformLinks const& b ) {
  return !( a > b );
}
bool operator>=( PlatformLinks const& a, PlatformLinks const& b ) {
  return !( b < a );
}

}  // namespace Types
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
