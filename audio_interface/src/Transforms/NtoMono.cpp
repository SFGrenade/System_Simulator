// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/Transforms/NtoMono.h"

namespace SFG::SystemSimulator::AudioInterface::Transforms {

void NtoMono::init( std::map< std::string, std::any > const& config ) {
  amount_ = std::any_cast< size_t >( config.at( "amount" ) );
  logger_->trace( fmt::runtime( "init( {:d} )" ), amount_ );

  inPorts = { { "main", {} } };
  inPorts["main"].resize( amount_ );
  outPorts = { { "main", {} } };
  outPorts["main"].resize( 1 );
}

void NtoMono::updateConfig( std::string const& option, std::any const& newValue ) {
  logger_->trace( fmt::runtime( "updateConfig( option={:?}, newValue={} )" ), option, newValue.type().name() );
}

void NtoMono::update() {
  auto& inPort = inPorts["main"];
  while( true ) {
    float averagedInput = 0.0f;
    bool sampleGotten = false;
    for( size_t i = 0; i < amount_; i++ ) {
      auto& inPortChannel = inPort[i];
      if( !inPortChannel ) {
        continue;
      }
      float tmp = 0.0f;
      sampleGotten = inPortChannel->pop( tmp ) || sampleGotten;
      averagedInput += tmp;
    }

    if( sampleGotten ) {
      averagedInput = averagedInput / float( amount_ );
      outPorts["main"][0]->push( averagedInput );
    } else {
      break;
    }
  }
}

void NtoMono::deinit() {
  logger_->trace( fmt::runtime( "deinit()" ) );

  inPorts["main"] = {};
  outPorts["main"] = {};
}

}  // namespace SFG::SystemSimulator::AudioInterface::Transforms
