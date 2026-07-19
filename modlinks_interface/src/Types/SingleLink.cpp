#include "SFG/SystemSimulator/LuigiInterface/Types/SingleLink.h"

// C++ includes
#include <tuple>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace Types {

bool operator==( SingleLink const& a, SingleLink const& b ) {
  return ( a.link == b.link ) && ( a.sha == b.sha );
}
bool operator!=( SingleLink const& a, SingleLink const& b ) {
  return !( a == b );
}
bool operator<( SingleLink const& a, SingleLink const& b ) {
  return std::tie( a.link, a.sha ) < std::tie( b.link, b.sha );
}
bool operator>( SingleLink const& a, SingleLink const& b ) {
  return b < a;
}
bool operator<=( SingleLink const& a, SingleLink const& b ) {
  return !( a > b );
}
bool operator>=( SingleLink const& a, SingleLink const& b ) {
  return !( b < a );
}

}  // namespace Types
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
