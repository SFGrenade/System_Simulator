#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <audio.pb.h>
#include <string>
#include <vector>

#include "SFG/SystemSimulator/RecordingServer/netConnector.h"
#include "SFG/SystemSimulator/RecordingServer/recordingServer.h"

namespace SSP = SFG::SystemSimulator::ProtoMessages;

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "RecordingServerLog.log" );
  std::vector< std::string > args;
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  int retCode = 0;
  SFG::SystemSimulator::RecordingServer::RecordingServer recordingServer;
  SFG::SystemSimulator::RecordingServer::NetConnector netConnector;

  netConnector->subscribe( new SSP::AudioFormatInformation(), [&]( google::protobuf::Message const& req ) {
    SSP::AudioFormatInformation const& actualReq = dynamic_cast< SSP::AudioFormatInformation const& >( req );

    SFG::SystemSimulator::RecordingServer::AudioFormatType actualType;
    switch( actualReq.type() ) {
      case SSP::AudioFormatType::PCM:
        actualType = SFG::SystemSimulator::RecordingServer::AudioFormatType::PCM;
        break;
      default:
        break;
    }

    recordingServer.setupAudioGenerator( actualReq.audio_generator_id(),
                                         actualType,
                                         static_cast< uint16_t >( actualReq.channels() ),
                                         static_cast< uint32_t >( actualReq.sample_rate() ),
                                         static_cast< uint16_t >( actualReq.bits_per_sample() ) );
  } );
  netConnector->subscribe( new SSP::AudioFrame(), [&]( google::protobuf::Message const& req ) {
    SSP::AudioFrame const& actualReq = dynamic_cast< SSP::AudioFrame const& >( req );

    std::list< uint8_t > actualData;
    for( char byte : actualReq.audio_data() ) {
      actualData.push_back( byte );
    }

    recordingServer.streamAudioFrame( actualReq.audio_generator_id(), actualData );
  } );

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return retCode;
}
