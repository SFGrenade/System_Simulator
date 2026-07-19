#pragma once

// C++ includes
#include <string>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace Types {

struct SingleLink {
  std::string sha = "";   // sha256
  std::string link = "";  // url

  friend bool operator==( SingleLink const& a, SingleLink const& b );
  friend bool operator!=( SingleLink const& a, SingleLink const& b );
  friend bool operator<( SingleLink const& a, SingleLink const& b );
  friend bool operator>( SingleLink const& a, SingleLink const& b );
  friend bool operator<=( SingleLink const& a, SingleLink const& b );
  friend bool operator>=( SingleLink const& a, SingleLink const& b );
};

}  // namespace Types
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
