#ifndef RECORDING_SERVER_NETCONNECTOR_H_
#define RECORDING_SERVER_NETCONNECTOR_H_

#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <networkingHelper/pushPull.hpp>

namespace SFG {
namespace SystemSimulator {
namespace RecordingServer {

class NetConnector {
  public:
  NetConnector();
  ~NetConnector();

  NetworkingHelper::PushPull* operator->() const;

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  SFG::SystemSimulator::Configuration::Configuration config_;
  NetworkingHelper::PushPull pushPullReceiver_;
};

}  // namespace RecordingServer
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* RECORDING_SERVER_NETCONNECTOR_H_ */
