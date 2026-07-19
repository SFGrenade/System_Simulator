#pragma once

// Project includes
#include <SFG/SystemSimulator/LuigiInterface/Types/SingleLink.h>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace Types {

struct PlatformLinks {
  SingleLink linux{};
  SingleLink mac{};
  SingleLink windows{};

  friend bool operator==( PlatformLinks const& a, PlatformLinks const& b );
  friend bool operator!=( PlatformLinks const& a, PlatformLinks const& b );
  friend bool operator<( PlatformLinks const& a, PlatformLinks const& b );
  friend bool operator>( PlatformLinks const& a, PlatformLinks const& b );
  friend bool operator<=( PlatformLinks const& a, PlatformLinks const& b );
  friend bool operator>=( PlatformLinks const& a, PlatformLinks const& b );
};

}  // namespace Types
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
