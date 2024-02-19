#include <networkMessages.pb.h>
#include <string>

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Proto::MsgContent myMessage;
  myMessage.set_username( "set_username" );
  myMessage.set_msgtext( "set_msgtext" );
  std::string serialized = myMessage.SerializeAsString();
  return 0;
}
