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

  std::pair< bool, std::string > registerUser( std::string const& username, std::string const& passwordHash );
  std::pair< bool, std::string > loginUser( std::string const& username, std::string const& passwordHash );
  std::pair< bool, std::string > checkUserSession( std::string const& sessionToken );
  std::pair< bool, std::string > logoutUserSession( std::string const& sessionToken );
  std::pair< bool, std::string > deleteUser( std::string const& username, std::string const& passwordHash );

  private:
  uint64_t getUserIdFromUsername( std::string const& username );
  bool checkUsernameExists( std::string const& username );
  bool checkPasswordHashValid( std::string const& passwordHash );
  bool checkSessionValid( std::string const& sessionToken );
  bool logoutSession( std::string const& sessionToken, bool skipValidCheck );

  public:
  std::string generateSessionToken();

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  SFG::SystemSimulator::Configuration::Configuration config_;
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
