#include "SFG/SystemSimulator/LuigiInterface/Types/ModManifest.h"

// C++ includes
#include <tuple>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace Types {

bool operator==( ModManifest const& a, ModManifest const& b ) {
  return ( a.name == b.name ) && ( a.displayName == b.displayName ) && ( a.description == b.description ) && ( a.version == b.version )
         && ( a.links == b.links ) && ( a.dependencies == b.dependencies ) && ( a.repository == b.repository ) && ( a.readme == b.readme )
         && ( a.issues == b.issues ) && ( a.integrations == b.integrations ) && ( a.tags == b.tags ) && ( a.authors == b.authors );
}
bool operator!=( ModManifest const& a, ModManifest const& b ) {
  return !( a == b );
}
bool operator<( ModManifest const& a, ModManifest const& b ) {
  return std::tie( a.name,
                   a.displayName,
                   a.description,
                   a.version,
                   a.links,
                   a.dependencies,
                   a.repository,
                   a.readme,
                   a.issues,
                   a.integrations,
                   a.tags,
                   a.authors )
         < std::tie( b.name,
                     b.displayName,
                     b.description,
                     b.version,
                     b.links,
                     b.dependencies,
                     b.repository,
                     b.readme,
                     b.issues,
                     b.integrations,
                     b.tags,
                     b.authors );
}
bool operator>( ModManifest const& a, ModManifest const& b ) {
  return b < a;
}
bool operator<=( ModManifest const& a, ModManifest const& b ) {
  return !( a > b );
}
bool operator>=( ModManifest const& a, ModManifest const& b ) {
  return !( b < a );
}

}  // namespace Types
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
