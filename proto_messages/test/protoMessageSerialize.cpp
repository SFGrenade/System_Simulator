#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <database.pb.h>
#include <string>

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "testLogs/protoMessageSerialize.log", false );
  std::vector< std::string > args;
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  int retVal = 0;
  SFG::SystemSimulator::ProtoMessages::MsgContent myMessage;
  myMessage.set_username( "set_username" );
  myMessage.set_msgtext( "set_msgtext" );
  std::string serialized = myMessage.SerializeAsString();
  spdlog::trace( fmt::runtime( "serialized = {:s}" ), serialized );

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return retVal;
}
