#include "SFG/SystemSimulator/NetworkMessages/Database.h"

namespace SFG {
namespace SystemSimulator {
namespace NetworkMessages {

bool MsgContent::operator==( MsgContent const& b ) const {
  bool ret = true;
  ret = ret && ( this->username == b.username );
  ret = ret && ( this->msgText == b.msgText );
  return ret;
}

}  // namespace NetworkMessages
}  // namespace SystemSimulator
}  // namespace SFG
