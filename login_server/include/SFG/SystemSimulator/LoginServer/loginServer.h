#ifndef LOGIN_SERVER_LOGINSERVER_H_
#define LOGIN_SERVER_LOGINSERVER_H_

#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <chrono>
#include <map>
#include <random>
#include <string>
#include <users.pb.h>
#include <zmqPb/reqRep.hpp>

namespace SFG {
namespace SystemSimulator {
namespace LoginServer {
namespace SSP = SFG::SystemSimulator::ProtoMessages;

struct User {
  std::string username;
  std::string passwordHash;
};

struct Session {
  uint64_t user_id;
  std::string sessionToken;
  std::chrono::time_point< std::chrono::system_clock > expirationTimepoint;
};

class LoginServer {
  public:
  LoginServer();
  ~LoginServer();

  void run();

  private:
  SSP::RegisterResponse* onRegister( SSP::RegisterRequest const& req );
  SSP::LoginResponse* onLogin( SSP::LoginRequest const& req );
  SSP::CheckSessionResponse* onCheckSession( SSP::CheckSessionRequest const& req );
  SSP::LogoutResponse* onLogout( SSP::LogoutRequest const& req );
  SSP::DeleteUserResponse* onDeleteUser( SSP::DeleteUserRequest const& req );

  private:
  uint64_t getUserIdFromUsername( std::string const& username );
  bool checkUsernameExists( std::string const& username );
  bool checkPasswordHashValid( std::string const& passwordHash );
  bool checkSessionValid( std::string const& sessionToken );

  public:
  std::string generateSessionToken();

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  SFG::SystemSimulator::Configuration::Configuration config_;
  ZmqPb::ReqRep reqRepServer_;
  std::map< uint64_t, User > userMap_;
  uint64_t userIdCounter_;
  std::map< uint64_t, Session > sessionMap_;
  uint64_t sessionIdCounter_;

  std::random_device randomDevice_;
  std::default_random_engine randomGenerator_;
  std::uniform_int_distribution< int > randomDistribution_;
  std::string sessionTokenAlphabet_ = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
};

}  // namespace LoginServer
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* LOGIN_SERVER_LOGINSERVER_H_ */
