#ifndef NETWORK_MESSAGES_DATABASE_H_
#define NETWORK_MESSAGES_DATABASE_H_

#include <networkingHelper/networkMessage.hpp>
#include <string>

namespace SFG {
namespace SystemSimulator {
namespace NetworkMessages {

class MsgContent {
  public:
  std::string username = "";
  std::string msgText = "";

  bool operator==( MsgContent const& b ) const;

  private:
  friend class bitsery::Access;
  template < typename S >
  void serialize( S& s ) {
    s.text1b( username, 1024 );
    s.text1b( msgText, 1024 );
  }
  template < typename S >
  void deserialize( S& s ) {
    s.text1b( username, 1024 );
    s.text1b( msgText, 1024 );
  }
};

}  // namespace NetworkMessages
}  // namespace SystemSimulator
}  // namespace SFG

#endif  // NETWORK_MESSAGES_DATABASE_H_
