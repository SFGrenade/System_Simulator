#ifndef NETWORK_MESSAGES_USERS_H_
#define NETWORK_MESSAGES_USERS_H_

#include <boost/archive/text_iarchive.hpp>
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
  friend class boost::serialization::access;
  template < class Archive >
  void serialize( Archive& ar, unsigned int const /*version*/ ) {
    ar& username;
    ar& password_hash;
  }
};

class RegisterResponse {
  public:
  bool success = false;
  std::string reason_for_fail = "";

  bool operator==( RegisterResponse const& b ) const;

  private:
  friend class boost::serialization::access;
  template < class Archive >
  void serialize( Archive& ar, unsigned int const /*version*/ ) {
    ar& success;
    ar& reason_for_fail;
  }
};

class LoginRequest {
  public:
  std::string username = "";
  std::string password_hash = "";

  bool operator==( LoginRequest const& b ) const;

  private:
  friend class boost::serialization::access;
  template < class Archive >
  void serialize( Archive& ar, unsigned int const /*version*/ ) {
    ar& username;
    ar& password_hash;
  }
};

class LoginResponse {
  public:
  bool success = false;
  std::string reason_for_fail = "";
  std::string session_token = "";

  bool operator==( LoginResponse const& b ) const;

  private:
  friend class boost::serialization::access;
  template < class Archive >
  void serialize( Archive& ar, unsigned int const /*version*/ ) {
    ar& success;
    ar& reason_for_fail;
    ar& session_token;
  }
};

class CheckSessionRequest {
  public:
  std::string session_token = "";

  bool operator==( CheckSessionRequest const& b ) const;

  private:
  friend class boost::serialization::access;
  template < class Archive >
  void serialize( Archive& ar, unsigned int const /*version*/ ) {
    ar& session_token;
  }
};

class CheckSessionResponse {
  public:
  bool is_valid = false;

  bool operator==( CheckSessionResponse const& b ) const;

  private:
  friend class boost::serialization::access;
  template < class Archive >
  void serialize( Archive& ar, unsigned int const /*version*/ ) {
    ar& is_valid;
  }
};

class LogoutRequest {
  public:
  std::string session_token = "";

  bool operator==( LogoutRequest const& b ) const;

  private:
  friend class boost::serialization::access;
  template < class Archive >
  void serialize( Archive& ar, unsigned int const /*version*/ ) {
    ar& session_token;
  }
};

class LogoutResponse {
  public:
  bool success = false;
  std::string reason_for_fail = "";

  bool operator==( LogoutResponse const& b ) const;

  private:
  friend class boost::serialization::access;
  template < class Archive >
  void serialize( Archive& ar, unsigned int const /*version*/ ) {
    ar& success;
    ar& reason_for_fail;
  }
};

class DeleteUserRequest {
  public:
  std::string username = "";
  std::string password_hash = "";

  bool operator==( DeleteUserRequest const& b ) const;

  private:
  friend class boost::serialization::access;
  template < class Archive >
  void serialize( Archive& ar, unsigned int const /*version*/ ) {
    ar& username;
    ar& password_hash;
  }
};

class DeleteUserResponse {
  public:
  bool success = false;
  std::string reason_for_fail = "";

  bool operator==( DeleteUserResponse const& b ) const;

  private:
  friend class boost::serialization::access;
  template < class Archive >
  void serialize( Archive& ar, unsigned int const /*version*/ ) {
    ar& success;
    ar& reason_for_fail;
  }
};

}  // namespace NetworkMessages
}  // namespace SystemSimulator
}  // namespace SFG

#endif  // NETWORK_MESSAGES_USERS_H_
