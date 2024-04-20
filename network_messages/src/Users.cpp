#include "SFG/SystemSimulator/NetworkMessages/Users.h"

namespace SFG {
namespace SystemSimulator {
namespace NetworkMessages {

bool RegisterRequest::operator==( RegisterRequest const& b ) const {
  bool ret = true;
  ret = ret && ( this->username == b.username );
  ret = ret && ( this->password_hash == b.password_hash );
  return ret;
}

bool RegisterResponse::operator==( RegisterResponse const& b ) const {
  bool ret = true;
  ret = ret && ( this->success == b.success );
  ret = ret && ( this->reason_for_fail == b.reason_for_fail );
  return ret;
}

bool LoginRequest::operator==( LoginRequest const& b ) const {
  bool ret = true;
  ret = ret && ( this->username == b.username );
  ret = ret && ( this->password_hash == b.password_hash );
  return ret;
}

bool LoginResponse::operator==( LoginResponse const& b ) const {
  bool ret = true;
  ret = ret && ( this->success == b.success );
  ret = ret && ( this->reason_for_fail == b.reason_for_fail );
  ret = ret && ( this->session_token == b.session_token );
  return ret;
}

bool CheckSessionRequest::operator==( CheckSessionRequest const& b ) const {
  bool ret = true;
  ret = ret && ( this->session_token == b.session_token );
  return ret;
}

bool CheckSessionResponse::operator==( CheckSessionResponse const& b ) const {
  bool ret = true;
  ret = ret && ( this->is_valid == b.is_valid );
  return ret;
}

bool LogoutRequest::operator==( LogoutRequest const& b ) const {
  bool ret = true;
  ret = ret && ( this->session_token == b.session_token );
  return ret;
}

bool LogoutResponse::operator==( LogoutResponse const& b ) const {
  bool ret = true;
  ret = ret && ( this->success == b.success );
  ret = ret && ( this->reason_for_fail == b.reason_for_fail );
  return ret;
}

bool DeleteUserRequest::operator==( DeleteUserRequest const& b ) const {
  bool ret = true;
  ret = ret && ( this->username == b.username );
  ret = ret && ( this->password_hash == b.password_hash );
  return ret;
}

bool DeleteUserResponse::operator==( DeleteUserResponse const& b ) const {
  bool ret = true;
  ret = ret && ( this->success == b.success );
  ret = ret && ( this->reason_for_fail == b.reason_for_fail );
  return ret;
}

}  // namespace NetworkMessages
}  // namespace SystemSimulator
}  // namespace SFG
