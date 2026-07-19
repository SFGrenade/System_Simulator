#pragma once

// Project includes
#include <SFG/SystemSimulator/LuigiInterface/Models/ModLinksXmlModel.h>
#include <SFG/SystemSimulator/LuigiInterface/Types/PlatformLinks.h>
#include <SFG/SystemSimulator/LuigiInterface/Types/Version.h>

// C++ includes
#include <string>
#include <vector>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace Types {

struct ModManifest {
  std::string name = "";
  std::string displayName = "";
  std::string description = "";
  Version version{};
  PlatformLinks links{};
  std::vector< std::string > dependencies{};
  std::string repository = "";  // URL
  std::string readme = "";      // URL
  std::string issues = "";      // URL
  std::vector< std::string > integrations{};
  std::vector< mm::TagEnum > tags{};
  std::vector< std::string > authors{};

  friend bool operator==( ModManifest const& a, ModManifest const& b );
  friend bool operator!=( ModManifest const& a, ModManifest const& b );
  friend bool operator<( ModManifest const& a, ModManifest const& b );
  friend bool operator>( ModManifest const& a, ModManifest const& b );
  friend bool operator<=( ModManifest const& a, ModManifest const& b );
  friend bool operator>=( ModManifest const& a, ModManifest const& b );
};

}  // namespace Types
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
