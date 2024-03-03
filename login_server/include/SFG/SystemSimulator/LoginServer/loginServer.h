#ifndef LOGIN_SERVER_LOGINSERVER_H_
#define LOGIN_SERVER_LOGINSERVER_H_

#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <users.pb.h>
#include <zmqPb/reqRep.hpp>

namespace SFG {
namespace SystemSimulator {
namespace LoginServer {

class LoginServer {
  public:
  LoginServer();
  ~LoginServer();

  void run();

  private:
  void onLogin( SFG::SystemSimulator::ProtoMessages::LoginRequest const& req );
  void onCheckSession( SFG::SystemSimulator::ProtoMessages::CheckSessionRequest const& req );
  void onLogout( SFG::SystemSimulator::ProtoMessages::LogoutRequest const& req );

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  SFG::SystemSimulator::Configuration::Configuration config_;
  ZmqPb::ReqRep reqRepServer_;
};

}  // namespace LoginServer
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* LOGIN_SERVER_LOGINSERVER_H_ */
