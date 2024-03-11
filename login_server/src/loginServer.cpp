#include "SFG/SystemSimulator/LoginServer/loginServer.h"

namespace SFG {
namespace SystemSimulator {
namespace LoginServer {

LoginServer::LoginServer()
    : logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "LoginServer" ) ),
      config_( "config/login_server.ini" ),
      reqRepServer_( config_.get< std::string >( "Network", "ServerEndpoint" ), true ),
      userMap_(),
      userIdCounter_( 1 ),
      sessionMap_(),
      sessionIdCounter_( 1 ),
      randomDevice_(),
      randomGenerator_( this->randomDevice_() ) {
  this->logger_->trace( fmt::runtime( "LoginServer" ) );

  this->randomDistribution_ = std::uniform_int_distribution< int >( 0, static_cast< int >( this->sessionTokenAlphabet_.length() ) - 1 );
  this->reqRepServer_.subscribe( new SSP::RegisterRequest(), [this]( google::protobuf::Message const& req ) {
    this->reqRepServer_.sendMessage( this->onRegister( static_cast< SSP::RegisterRequest const& >( req ) ) );
  } );
  this->reqRepServer_.subscribe( new SSP::LoginRequest(), [this]( google::protobuf::Message const& req ) {
    this->reqRepServer_.sendMessage( this->onLogin( static_cast< SSP::LoginRequest const& >( req ) ) );
  } );
  this->reqRepServer_.subscribe( new SSP::CheckSessionRequest(), [this]( google::protobuf::Message const& req ) {
    this->reqRepServer_.sendMessage( this->onCheckSession( static_cast< SSP::CheckSessionRequest const& >( req ) ) );
  } );
  this->reqRepServer_.subscribe( new SSP::LogoutRequest(), [this]( google::protobuf::Message const& req ) {
    this->reqRepServer_.sendMessage( this->onLogout( static_cast< SSP::LogoutRequest const& >( req ) ) );
  } );
  this->reqRepServer_.subscribe( new SSP::DeleteUserRequest(), [this]( google::protobuf::Message const& req ) {
    this->reqRepServer_.sendMessage( this->onDeleteUser( static_cast< SSP::DeleteUserRequest const& >( req ) ) );
  } );

  this->logger_->trace( fmt::runtime( "LoginServer~" ) );
}

LoginServer::~LoginServer() {
  this->logger_->trace( fmt::runtime( "~LoginServer" ) );

  this->logger_->trace( fmt::runtime( "~LoginServer~" ) );
}

void LoginServer::run() {
  // this->logger_->trace( fmt::runtime( "run" ) );

  this->reqRepServer_.run();

  // this->logger_->trace( fmt::runtime( "run~" ) );
}

SSP::RegisterResponse* LoginServer::onRegister( SSP::RegisterRequest const& req ) {
  this->logger_->trace( fmt::runtime( "onRegister( req = '{:s}' )" ), req.DebugString() );

  SSP::RegisterResponse* rep = new SSP::RegisterResponse();

  if( this->checkUsernameExists( req.username() ) ) {
    rep->set_success( false );
    rep->set_reason_for_fail( "User already exists" );
  } else {
    if( !this->checkPasswordHashValid( req.password_hash() ) ) {
      rep->set_success( false );
      rep->set_reason_for_fail( "Password hash not valid" );
    } else {
      this->userMap_[this->userIdCounter_] = User{ .username = req.username(), .passwordHash = req.password_hash() };
      this->userIdCounter_++;
      rep->set_success( true );
    }
  }

  this->logger_->trace( fmt::runtime( "onRegister~" ) );
  return rep;
}

SSP::LoginResponse* LoginServer::onLogin( SSP::LoginRequest const& req ) {
  this->logger_->trace( fmt::runtime( "onLogin( req = '{:s}' )" ), req.DebugString() );

  SSP::LoginResponse* rep = new SSP::LoginResponse();

  if( !this->checkUsernameExists( req.username() ) ) {
    rep->set_success( false );
    rep->set_reason_for_fail( "User doesn't exists" );
  } else {
    if( !this->checkPasswordHashValid( req.password_hash() ) ) {
      rep->set_success( false );
      rep->set_reason_for_fail( "Password hash not valid" );
    } else {
      std::string sessionToken = this->generateSessionToken();  // random session token?
      this->sessionMap_[this->sessionIdCounter_]
          = Session{ .user_id = this->getUserIdFromUsername( req.username() ),
                     .sessionToken = sessionToken,
                     .expirationTimepoint
                     = std::chrono::system_clock::now() + std::chrono::seconds( this->config_.get< uint32_t >( "Database", "SessionTokenValidTime" ) ) };
      this->sessionIdCounter_++;
      rep->set_success( true );
      rep->set_session_token( sessionToken );
    }
  }

  this->logger_->trace( fmt::runtime( "onLogin~" ) );
  return rep;
}

SSP::CheckSessionResponse* LoginServer::onCheckSession( SSP::CheckSessionRequest const& req ) {
  this->logger_->trace( fmt::runtime( "onCheckSession( req = '{:s}' )" ), req.DebugString() );

  SSP::CheckSessionResponse* rep = new SSP::CheckSessionResponse();

  if( this->checkSessionValid( req.session_token() ) ) {
    rep->set_is_valid( true );
  } else {
    rep->set_is_valid( false );
    this->logoutSession( req.session_token(), true );
  }

  this->logger_->trace( fmt::runtime( "onCheckSession~" ) );
  return rep;
}

SSP::LogoutResponse* LoginServer::onLogout( SSP::LogoutRequest const& req ) {
  this->logger_->trace( fmt::runtime( "onLogout( req = '{:s}' )" ), req.DebugString() );

  SSP::LogoutResponse* rep = new SSP::LogoutResponse();

  if( !this->checkSessionValid( req.session_token() ) ) {
    rep->set_success( false );
    rep->set_reason_for_fail( "Session isn't valid" );
  } else {
    if( this->logoutSession( req.session_token(), false ) ) {
      rep->set_success( true );
    } else {
      rep->set_success( false );
      rep->set_reason_for_fail( "Session couldn't be logged out" );
    }
  }

  this->logger_->trace( fmt::runtime( "onLogout~" ) );
  return rep;
}

SSP::DeleteUserResponse* LoginServer::onDeleteUser( SSP::DeleteUserRequest const& req ) {
  this->logger_->trace( fmt::runtime( "onDeleteUser( req = '{:s}' )" ), req.DebugString() );

  SSP::DeleteUserResponse* rep = new SSP::DeleteUserResponse();

  if( !this->checkUsernameExists( req.username() ) ) {
    rep->set_success( false );
    rep->set_reason_for_fail( "User doesn't exists" );
  } else {
    if( !this->checkPasswordHashValid( req.password_hash() ) ) {
      rep->set_success( false );
      rep->set_reason_for_fail( "Password hash not valid" );
    } else {
      rep->set_success( false );
      rep->set_reason_for_fail( "Username/Password is wrong" );
      for( auto const& userStruct : this->userMap_ ) {
        if( userStruct.second.username == req.username() && userStruct.second.passwordHash == req.password_hash() ) {
          this->userMap_.erase( userStruct.first );
          rep->set_success( true );
          rep->set_reason_for_fail( "" );
          break;
        }
      }
    }
  }

  this->logger_->trace( fmt::runtime( "onDeleteUser~" ) );
  return rep;
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
        this->logger_->trace( fmt::runtime( "checkSessionValid~" ) );
        return false;
      } else if( skipValidCheck || ( std::chrono::system_clock::now() < sessionStruct.second.expirationTimepoint ) ) {
        this->sessionMap_.erase( sessionStruct.first );
        this->logger_->trace( fmt::runtime( "checkSessionValid~" ) );
        return true;
      }
    }
  }

  this->logger_->trace( fmt::runtime( "checkSessionValid~" ) );
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
