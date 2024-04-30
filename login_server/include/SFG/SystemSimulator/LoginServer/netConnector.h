#ifndef LOGIN_SERVER_NETCONNECTOR_H_
#define LOGIN_SERVER_NETCONNECTOR_H_

#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <networkingHelper/reqRep.hpp>

namespace SFG {
namespace SystemSimulator {
namespace LoginServer {

class NetConnector {
  public:
  NetConnector();
  ~NetConnector();

  NetworkingHelper::ReqRep* operator->() const;

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  SFG::SystemSimulator::Configuration::Configuration config_;
  NetworkingHelper::ReqRep reqRepServer_;
};

}  // namespace LoginServer
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* LOGIN_SERVER_NETCONNECTOR_H_ */
