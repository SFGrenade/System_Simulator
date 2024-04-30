#ifndef AUDIO_INTERFACE_NETCONNECTOR_H_
#define AUDIO_INTERFACE_NETCONNECTOR_H_

#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <networkingHelper/pushPull.hpp>

namespace SFG {
namespace SystemSimulator {
namespace AudioInterface {

class NetConnector {
  public:
  NetConnector();
  ~NetConnector();

  NetworkingHelper::PushPull* operator->() const;

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  SFG::SystemSimulator::Configuration::Configuration config_;
  NetworkingHelper::PushPull pushPullSender_;
};

}  // namespace AudioInterface
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* AUDIO_INTERFACE_NETCONNECTOR_H_ */
