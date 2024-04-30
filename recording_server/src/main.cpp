#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/NetworkMessages/Audio.h>
#include <string>
#include <vector>

#include "SFG/SystemSimulator/RecordingServer/netConnector.h"
#include "SFG/SystemSimulator/RecordingServer/recordingServer.h"

namespace SSSNM = SFG::SystemSimulator::NetworkMessages;

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

  netConnector->subscribe( NetworkingHelper::NetworkMessage::from( "SFG.SystemSimulator.NetworkMessages.AudioFormatInformation",
                                                                   SSSNM::AudioFormatInformation() ),
                           [&]( NetworkingHelper::NetworkMessage const& req ) {
                             SSSNM::AudioFormatInformation const& actualReq
                                 = req.to< SSSNM::AudioFormatInformation >( "SFG.SystemSimulator.NetworkMessages.AudioFormatInformation" );

                             recordingServer.setupAudioGenerator( actualReq.audio_generator_id,
                                                                  static_cast< uint16_t >( actualReq.channels ),
                                                                  static_cast< uint32_t >( actualReq.sample_rate ),
                                                                  static_cast< uint16_t >( actualReq.bits_per_sample ) );
                           } );
  netConnector->subscribe( NetworkingHelper::NetworkMessage::from( "SFG.SystemSimulator.NetworkMessages.AudioFrame", SSSNM::AudioFrame() ),
                           [&]( NetworkingHelper::NetworkMessage const& req ) {
                             SSSNM::AudioFrame const& actualReq = req.to< SSSNM::AudioFrame >( "SFG.SystemSimulator.NetworkMessages.AudioFrame" );

                             std::list< char > actualData;
                             for( char byte : actualReq.audio_data ) {
                               actualData.push_back( byte );
                             }

                             recordingServer.streamAudioFrame( actualReq.audio_generator_id, actualData );
                           } );

  while( 1 ) {
    try {
      netConnector->run();
    } catch( std::exception const& e ) {
      spdlog::error( fmt::runtime( "error calling netConnector.run: {:s}" ), e.what() );
    }
  }

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return retCode;
}
