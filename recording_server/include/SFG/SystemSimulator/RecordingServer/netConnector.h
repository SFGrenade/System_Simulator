#ifndef RECORDING_SERVER_NETCONNECTOR_H_
#define RECORDING_SERVER_NETCONNECTOR_H_

#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
// #include <zmqPb/pushPull.hpp>  // todo

namespace SFG {
namespace SystemSimulator {
namespace RecordingServer {

class NetConnector {
  public:
  NetConnector();
  ~NetConnector();

  // ZmqPb::PushPull* operator->() const;  // todo

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  SFG::SystemSimulator::Configuration::Configuration config_;
  // ZmqPb::PushPull pushPullReceiver_;  // todo
};

}  // namespace RecordingServer
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* RECORDING_SERVER_NETCONNECTOR_H_ */
