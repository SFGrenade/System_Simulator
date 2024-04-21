#ifndef NETWORK_MESSAGES_USERS_H_
#define NETWORK_MESSAGES_USERS_H_

#include <networkingHelper/networkMessage.hpp>
#include <string>

namespace SFG {
namespace SystemSimulator {
namespace NetworkMessages {

class RegisterRequest {
  public:
  std::string username = "";
  std::string password_hash = "";

  bool operator==( RegisterRequest const& b ) const;

  private:
  friend class bitsery::Access;
  template < typename S >
  void serialize( S& s ) {
    s.text1b( username, 1024 );
    s.text1b( password_hash, 1024 );
  }
  template < typename S >
  void deserialize( S& s ) {
    s.text1b( username, 1024 );
    s.text1b( password_hash, 1024 );
  }
};

class RegisterResponse {
  public:
  bool success = false;
  std::string reason_for_fail = "";

  bool operator==( RegisterResponse const& b ) const;

  private:
  friend class bitsery::Access;
  template < typename S >
  void serialize( S& s ) {
    s.boolValue( success );
    s.text1b( reason_for_fail, 1024 );
  }
  template < typename S >
  void deserialize( S& s ) {
    s.boolValue( success );
    s.text1b( reason_for_fail, 1024 );
  }
};

class LoginRequest {
  public:
  std::string username = "";
  std::string password_hash = "";

  bool operator==( LoginRequest const& b ) const;

  private:
  friend class bitsery::Access;
  template < typename S >
  void serialize( S& s ) {
    s.text1b( username, 1024 );
    s.text1b( password_hash, 1024 );
  }
  template < typename S >
  void deserialize( S& s ) {
    s.text1b( username, 1024 );
    s.text1b( password_hash, 1024 );
  }
};

class LoginResponse {
  public:
  bool success = false;
  std::string reason_for_fail = "";
  std::string session_token = "";

  bool operator==( LoginResponse const& b ) const;

  private:
  friend class bitsery::Access;
  template < typename S >
  void serialize( S& s ) {
    s.boolValue( success );
    s.text1b( reason_for_fail, 1024 );
    s.text1b( session_token, 1024 );
  }
  template < typename S >
  void deserialize( S& s ) {
    s.boolValue( success );
    s.text1b( reason_for_fail, 1024 );
    s.text1b( session_token, 1024 );
  }
};

class CheckSessionRequest {
  public:
  std::string session_token = "";

  bool operator==( CheckSessionRequest const& b ) const;

  private:
  friend class bitsery::Access;
  template < typename S >
  void serialize( S& s ) {
    s.text1b( session_token, 1024 );
  }
  template < typename S >
  void deserialize( S& s ) {
    s.text1b( session_token, 1024 );
  }
};

class CheckSessionResponse {
  public:
  bool is_valid = false;

  bool operator==( CheckSessionResponse const& b ) const;

  private:
  friend class bitsery::Access;
  template < typename S >
  void serialize( S& s ) {
    s.boolValue( is_valid );
  }
  template < typename S >
  void deserialize( S& s ) {
    s.boolValue( is_valid );
  }
};

class LogoutRequest {
  public:
  std::string session_token = "";

  bool operator==( LogoutRequest const& b ) const;

  private:
  friend class bitsery::Access;
  template < typename S >
  void serialize( S& s ) {
    s.text1b( session_token, 1024 );
  }
  template < typename S >
  void deserialize( S& s ) {
    s.text1b( session_token, 1024 );
  }
};

class LogoutResponse {
  public:
  bool success = false;
  std::string reason_for_fail = "";

  bool operator==( LogoutResponse const& b ) const;

  private:
  friend class bitsery::Access;
  template < typename S >
  void serialize( S& s ) {
    s.boolValue( success );
    s.text1b( reason_for_fail, 1024 );
  }
  template < typename S >
  void deserialize( S& s ) {
    s.boolValue( success );
    s.text1b( reason_for_fail, 1024 );
  }
};

class DeleteUserRequest {
  public:
  std::string username = "";
  std::string password_hash = "";

  bool operator==( DeleteUserRequest const& b ) const;

  private:
  friend class bitsery::Access;
  template < typename S >
  void serialize( S& s ) {
    s.text1b( username, 1024 );
    s.text1b( password_hash, 1024 );
  }
  template < typename S >
  void deserialize( S& s ) {
    s.text1b( username, 1024 );
    s.text1b( password_hash, 1024 );
  }
};

class DeleteUserResponse {
  public:
  bool success = false;
  std::string reason_for_fail = "";

  bool operator==( DeleteUserResponse const& b ) const;

  private:
  friend class bitsery::Access;
  template < typename S >
  void serialize( S& s ) {
    s.boolValue( success );
    s.text1b( reason_for_fail, 1024 );
  }
  template < typename S >
  void deserialize( S& s ) {
    s.boolValue( success );
    s.text1b( reason_for_fail, 1024 );
  }
};

}  // namespace NetworkMessages
}  // namespace SystemSimulator
}  // namespace SFG

#endif  // NETWORK_MESSAGES_USERS_H_
