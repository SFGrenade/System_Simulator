#ifndef NETWORK_MESSAGES_DATABASE_H_
#define NETWORK_MESSAGES_DATABASE_H_

#include <boost/archive/text_iarchive.hpp>
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
  friend class boost::serialization::access;
  template < class Archive >
  void serialize( Archive& ar, unsigned int const /*version*/ ) {
    ar& username;
    ar& msgText;
  }
};

}  // namespace NetworkMessages
}  // namespace SystemSimulator
}  // namespace SFG

#endif  // NETWORK_MESSAGES_DATABASE_H_
