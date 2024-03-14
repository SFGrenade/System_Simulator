#include "SFG/SystemSimulator/LoginServer/loginServer.h"

namespace SFG {
namespace SystemSimulator {
namespace LoginServer {

LoginServer::LoginServer()
    : logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "LoginServer" ) ),
      config_( "config/login_server.ini" ),
      userMap_(),
      userIdCounter_( 1 ),
      sessionMap_(),
      sessionIdCounter_( 1 ),
      randomDevice_(),
      randomGenerator_( this->randomDevice_() ) {
  this->logger_->trace( fmt::runtime( "LoginServer" ) );

  this->randomDistribution_ = std::uniform_int_distribution< int >( 0, static_cast< int >( this->sessionTokenAlphabet_.length() ) - 1 );

  this->logger_->trace( fmt::runtime( "LoginServer~" ) );
}

LoginServer::~LoginServer() {
  this->logger_->trace( fmt::runtime( "~LoginServer" ) );

  this->logger_->trace( fmt::runtime( "~LoginServer~" ) );
}

std::pair< bool, std::string > LoginServer::registerUser( std::string const& username, std::string const& passwordHash ) {
  this->logger_->trace( fmt::runtime( "registerUser( username = '{:s}', passwordHash = '{:s}' )" ), username, passwordHash );

  std::pair< bool, std::string > ret;

  if( this->checkUsernameExists( username ) ) {
    ret.first = false;
    ret.second = "User already exists";
  } else {
    if( !this->checkPasswordHashValid( passwordHash ) ) {
      ret.first = false;
      ret.second = "Password hash not valid";
    } else {
      this->userMap_[this->userIdCounter_] = User{ .username = username, .passwordHash = passwordHash };
      this->userIdCounter_++;
      ret.first = true;
    }
  }

  this->logger_->trace( fmt::runtime( "registerUser~" ) );
  return ret;
}

std::pair< bool, std::string > LoginServer::loginUser( std::string const& username, std::string const& passwordHash ) {
  this->logger_->trace( fmt::runtime( "loginUser( username = '{:s}', passwordHash = '{:s}' )" ), username, passwordHash );

  std::pair< bool, std::string > ret;

  if( !this->checkUsernameExists( username ) ) {
    ret.first = false;
    ret.second = "User doesn't exists";
  } else {
    if( !this->checkPasswordHashValid( passwordHash ) ) {
      ret.first = false;
      ret.second = "Password hash not valid";
    } else {
      for( auto const& userStruct : this->userMap_ ) {
        if( userStruct.second.username == username && userStruct.second.passwordHash == passwordHash ) {
          std::string sessionToken = this->generateSessionToken();  // random session token?
          this->sessionMap_[this->sessionIdCounter_]
              = Session{ .user_id = this->getUserIdFromUsername( username ),
                         .sessionToken = sessionToken,
                         .expirationTimepoint
                         = std::chrono::system_clock::now() + std::chrono::seconds( this->config_.get< uint32_t >( "Database", "SessionTokenValidTime" ) ) };
          this->sessionIdCounter_++;
          ret.first = true;
          ret.second = sessionToken;
          break;
        }
      }
    }
  }

  this->logger_->trace( fmt::runtime( "loginUser~" ) );
  return ret;
}

std::pair< bool, std::string > LoginServer::checkUserSession( std::string const& sessionToken ) {
  this->logger_->trace( fmt::runtime( "checkUserSession( sessionToken = '{:s}' )" ), sessionToken );

  std::pair< bool, std::string > ret;

  if( this->checkSessionValid( sessionToken ) ) {
    ret.first = true;
  } else {
    ret.first = false;
    this->logoutSession( sessionToken, true );
  }

  this->logger_->trace( fmt::runtime( "checkUserSession~" ) );
  return ret;
}

std::pair< bool, std::string > LoginServer::logoutUserSession( std::string const& sessionToken ) {
  this->logger_->trace( fmt::runtime( "logoutUserSession( sessionToken = '{:s}' )" ), sessionToken );

  std::pair< bool, std::string > ret;

  if( !this->checkSessionValid( sessionToken ) ) {
    ret.first = false;
    ret.second = "Session isn't valid";
  } else {
    if( this->logoutSession( sessionToken, false ) ) {
      ret.first = true;
    } else {
      ret.first = false;
      ret.second = "Session couldn't be logged out";
    }
  }

  this->logger_->trace( fmt::runtime( "logoutUserSession~" ) );
  return ret;
}

std::pair< bool, std::string > LoginServer::deleteUser( std::string const& username, std::string const& passwordHash ) {
  this->logger_->trace( fmt::runtime( "deleteUser( username = '{:s}', passwordHash = '{:s}' )" ), username, passwordHash );

  std::pair< bool, std::string > ret;

  if( !this->checkUsernameExists( username ) ) {
    ret.first = false;
    ret.second = "User doesn't exists";
  } else {
    if( !this->checkPasswordHashValid( passwordHash ) ) {
      ret.first = false;
      ret.second = "Password hash not valid";
    } else {
      ret.first = false;
      ret.second = "Username/Password is wrong";
      for( auto const& userStruct : this->userMap_ ) {
        if( userStruct.second.username == username && userStruct.second.passwordHash == passwordHash ) {
          this->userMap_.erase( userStruct.first );
          ret.first = true;
          ret.second = "";
          break;
        }
      }
    }
  }

  this->logger_->trace( fmt::runtime( "deleteUser~" ) );
  return ret;
}

uint64_t LoginServer::getUserIdFromUsername( std::string const& username ) {
  this->logger_->trace( fmt::runtime( "getUserIdFromUsername( username = '{:s}' )" ), username );

  for( auto const& userStruct : this->userMap_ ) {
    if( userStruct.second.username == username ) {
      this->logger_->trace( fmt::runtime( "getUserIdFromUsername~" ) );
      return userStruct.first;
    }
  }

  this->logger_->trace( fmt::runtime( "getUserIdFromUsername~" ) );
  return 0;
}

bool LoginServer::checkUsernameExists( std::string const& username ) {
  this->logger_->trace( fmt::runtime( "checkUsernameExists( username = '{:s}' )" ), username );

  this->logger_->trace( fmt::runtime( "checkUsernameExists~" ) );
  return getUserIdFromUsername( username ) != 0;
}

bool LoginServer::checkPasswordHashValid( std::string const& passwordHash ) {
  this->logger_->trace( fmt::runtime( "checkPasswordHashValid( passwordHash = '{:s}' )" ), passwordHash );

  // todo: actually check, once decided which hash to use

  this->logger_->trace( fmt::runtime( "checkPasswordHashValid~" ) );
  return true;
}

bool LoginServer::checkSessionValid( std::string const& sessionToken ) {
  this->logger_->trace( fmt::runtime( "checkSessionValid( sessionToken = '{:s}' )" ), sessionToken );

  for( auto const& sessionStruct : this->sessionMap_ ) {
    if( sessionStruct.second.sessionToken == sessionToken ) {
      this->logger_->trace( fmt::runtime( "checkSessionValid~" ) );
      return std::chrono::system_clock::now() < sessionStruct.second.expirationTimepoint;
    }
  }

  this->logger_->trace( fmt::runtime( "checkSessionValid~" ) );
  return false;
}

bool LoginServer::logoutSession( std::string const& sessionToken, bool skipValidCheck ) {
  this->logger_->trace( fmt::runtime( "logoutSession( sessionToken = '{:s}', skipValidCheck = {} )" ), sessionToken, skipValidCheck );

  for( auto const& sessionStruct : this->sessionMap_ ) {
    if( sessionStruct.second.sessionToken == sessionToken ) {
      if( !skipValidCheck && ( sessionStruct.second.expirationTimepoint < std::chrono::system_clock::now() ) ) {
        this->logger_->trace( fmt::runtime( "logoutSession~" ) );
        return false;
      } else if( skipValidCheck || ( std::chrono::system_clock::now() < sessionStruct.second.expirationTimepoint ) ) {
        this->sessionMap_.erase( sessionStruct.first );
        this->logger_->trace( fmt::runtime( "logoutSession~" ) );
        return true;
      }
    }
  }

  this->logger_->trace( fmt::runtime( "logoutSession~" ) );
  return false;
}

std::string LoginServer::generateSessionToken() {
  this->logger_->trace( fmt::runtime( "generateSessionToken" ) );

  std::stringstream ret;
  for( int i = 0; i < 16; i++ ) {
    int randomIndex = this->randomDistribution_( this->randomGenerator_ );
    ret << this->sessionTokenAlphabet_.at( randomIndex );
  }

  this->logger_->trace( fmt::runtime( "generateSessionToken~" ) );
  return ret.str();
}

}  // namespace LoginServer
}  // namespace SystemSimulator
}  // namespace SFG
