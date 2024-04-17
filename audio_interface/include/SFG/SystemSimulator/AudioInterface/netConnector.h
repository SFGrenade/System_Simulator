#ifndef AUDIO_INTERFACE_NETCONNECTOR_H_
#define AUDIO_INTERFACE_NETCONNECTOR_H_

#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
// #include <zmqPb/pushPull.hpp>  // todo

namespace SFG {
namespace SystemSimulator {
namespace AudioInterface {

class NetConnector {
  public:
  NetConnector();
  ~NetConnector();

  // ZmqPb::PushPull* operator->() const;  // todo

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  SFG::SystemSimulator::Configuration::Configuration config_;
  // ZmqPb::PushPull pushPullSender_;  // todo
};

}  // namespace AudioInterface
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* AUDIO_INTERFACE_NETCONNECTOR_H_ */
