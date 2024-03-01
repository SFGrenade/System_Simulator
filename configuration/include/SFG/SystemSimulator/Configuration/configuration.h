#ifndef CONFIGURATION_CONFIGURATION_H_
#define CONFIGURATION_CONFIGURATION_H_

#include <SimpleIni.h>

namespace SFG {
namespace SystemSimulator {
namespace SettingsInterface {

class Configuration {
  public:
  Configuration();

  private:
  CSimpleIniA iniFile_;
};

}  // namespace SettingsInterface
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* CONFIGURATION_CONFIGURATION_H_ */
