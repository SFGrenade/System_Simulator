#pragma once

// C++ includes
#include <string>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace Types {

struct Version {
  size_t major = 0;
  size_t minor = 0;
  size_t patch = 0;
  size_t build = 0;

  static Version fromString( std::string const& str );
  std::string toString() const;
};

}  // namespace Types
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
