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
  logger_->trace( fmt::runtime( "LoginServer" ) );

  randomDistribution_ = std::uniform_int_distribution< int >( 0, static_cast< int >( this->sessionTokenAlphabet_.length() ) - 1 );
  reqRepServer_.subscribe( new SSP::RegisterRequest(), [this]( google::protobuf::Message const& req ) {
    this->reqRepServer_.sendMessage( this->onRegister( static_cast< SSP::RegisterRequest const& >( req ) ) );
  } );
  reqRepServer_.subscribe( new SSP::LoginRequest(), [this]( google::protobuf::Message const& req ) {
    this->reqRepServer_.sendMessage( this->onLogin( static_cast< SSP::LoginRequest const& >( req ) ) );
  } );
  reqRepServer_.subscribe( new SSP::CheckSessionRequest(), [this]( google::protobuf::Message const& req ) {
    this->reqRepServer_.sendMessage( this->onCheckSession( static_cast< SSP::CheckSessionRequest const& >( req ) ) );
  } );
  reqRepServer_.subscribe( new SSP::LogoutRequest(), [this]( google::protobuf::Message const& req ) {
    this->reqRepServer_.sendMessage( this->onLogout( static_cast< SSP::LogoutRequest const& >( req ) ) );
  } );
  reqRepServer_.subscribe( new SSP::DeleteUserRequest(), [this]( google::protobuf::Message const& req ) {
    this->reqRepServer_.sendMessage( this->onDeleteUser( static_cast< SSP::DeleteUserRequest const& >( req ) ) );
  } );

  logger_->trace( fmt::runtime( "LoginServer~" ) );
}

LoginServer::~LoginServer() {
  logger_->trace( fmt::runtime( "~LoginServer" ) );

  logger_->trace( fmt::runtime( "~LoginServer~" ) );
}

void LoginServer::run() {
  // logger_->trace( fmt::runtime( "run" ) );

  reqRepServer_.run();

  // logger_->trace( fmt::runtime( "run~" ) );
}

SSP::RegisterResponse* LoginServer::onRegister( SSP::RegisterRequest const& req ) {
  logger_->trace( fmt::runtime( "onRegister" ) );
  SSP::RegisterResponse* rep = new SSP::RegisterResponse();

  if( checkUsernameExists( req.username() ) ) {
    rep->set_success( false );
    rep->set_reason_for_fail( "User already exists" );
  } else {
    if( checkPasswordHashValid( req.password_hash() ) ) {
      rep->set_success( false );
      rep->set_reason_for_fail( "Password hash not valid" );
    } else {
      this->userMap_[this->userIdCounter_] = User{ .username = req.username(), .passwordHash = req.password_hash() };
      this->userIdCounter_++;
      rep->set_success( true );
    }
  }

  logger_->trace( fmt::runtime( "onRegister~" ) );
  return rep;
}

SSP::LoginResponse* LoginServer::onLogin( SSP::LoginRequest const& req ) {
  logger_->trace( fmt::runtime( "onLogin" ) );

  SSP::LoginResponse* rep = new SSP::LoginResponse();

  if( !checkUsernameExists( req.username() ) ) {
    rep->set_success( false );
    rep->set_reason_for_fail( "User doesn't exists" );
  } else {
    if( checkPasswordHashValid( req.password_hash() ) ) {
      rep->set_success( false );
      rep->set_reason_for_fail( "Password hash not valid" );
    } else {
      std::string sessionToken = "";  // random session token?
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

  logger_->trace( fmt::runtime( "onLogin~" ) );
  return rep;
}

SSP::CheckSessionResponse* LoginServer::onCheckSession( SSP::CheckSessionRequest const& req ) {
  logger_->trace( fmt::runtime( "onCheckSession" ) );

  SSP::CheckSessionResponse* rep = new SSP::CheckSessionResponse();

  rep->set_is_valid( this->checkSessionValid( req.session_token() ) );

  logger_->trace( fmt::runtime( "onCheckSession~" ) );
  return rep;
}

SSP::LogoutResponse* LoginServer::onLogout( SSP::LogoutRequest const& req ) {
  logger_->trace( fmt::runtime( "onLogout" ) );

  SSP::LogoutResponse* rep = new SSP::LogoutResponse();

  logger_->trace( fmt::runtime( "onLogout~" ) );
  return rep;
}

SSP::DeleteUserResponse* LoginServer::onDeleteUser( SSP::DeleteUserRequest const& req ) {
  logger_->trace( fmt::runtime( "onDeleteUser" ) );

  SSP::DeleteUserResponse* rep = new SSP::DeleteUserResponse();

  logger_->trace( fmt::runtime( "onDeleteUser~" ) );
  return rep;
}

uint64_t LoginServer::getUserIdFromUsername( std::string const& username ) {
  logger_->trace( fmt::runtime( "getUserIdFromUsername" ) );

  for( auto const& userStruct : this->userMap_ ) {
    if( userStruct.second.username == username ) {
      logger_->trace( fmt::runtime( "getUserIdFromUsername~" ) );
      return userStruct.first;
    }
  }

  logger_->trace( fmt::runtime( "getUserIdFromUsername~" ) );
  return 0;
}

bool LoginServer::checkUsernameExists( std::string const& username ) {
  logger_->trace( fmt::runtime( "checkUsernameExists" ) );

  logger_->trace( fmt::runtime( "checkUsernameExists~" ) );
  return getUserIdFromUsername( username ) != 0;
}

bool LoginServer::checkPasswordHashValid( std::string const& passwordHash ) {
  logger_->trace( fmt::runtime( "checkPasswordHashValid" ) );

  // todo: actually check, once decided which hash to use

  logger_->trace( fmt::runtime( "checkPasswordHashValid~" ) );
  return true;
}

bool LoginServer::checkSessionValid( std::string const& sessionToken ) {
  logger_->trace( fmt::runtime( "checkSessionValid" ) );

  for( auto const& sessionStruct : this->sessionMap_ ) {
    if( sessionStruct.second.sessionToken == sessionToken ) {
      logger_->trace( fmt::runtime( "checkSessionValid~" ) );
      return sessionStruct.second.expirationTimepoint < std::chrono::system_clock::now();
    }
  }

  logger_->trace( fmt::runtime( "checkSessionValid~" ) );
  return false;
}

std::string LoginServer::generateSessionToken() {
  logger_->trace( fmt::runtime( "generateSessionToken" ) );

  std::stringstream ret;
  for( int i = 0; i < 16; i++ ) {
    int randomIndex = this->randomDistribution_( this->randomGenerator_ );
    ret << this->sessionTokenAlphabet_.at( randomIndex );
  }

  logger_->trace( fmt::runtime( "generateSessionToken~" ) );
  return ret.str();
}

}  // namespace LoginServer
}  // namespace SystemSimulator
}  // namespace SFG
