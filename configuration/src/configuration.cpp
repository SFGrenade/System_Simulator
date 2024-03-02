#include "SFG/SystemSimulator/Configuration/configuration.h"

namespace SFG {
namespace SystemSimulator {
namespace Configuration {

Configuration::Configuration( std::string const& configFilepath ) : iniFile_() {
  iniFile_.load( configFilepath.c_str() );
}

}  // namespace Configuration
}  // namespace SystemSimulator
}  // namespace SFG
