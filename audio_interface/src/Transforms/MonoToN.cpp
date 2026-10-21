// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/Transforms/MonoToN.h"

namespace SFG::SystemSimulator::AudioInterface::Transforms {

void MonoToN::init( std::map< std::string, std::any > const& config ) {
  amount_ = std::any_cast< int64_t >( config.at( "amount" ) );
  logger_->trace( fmt::runtime( "init( {:d} )" ), amount_ );

  inPorts = { { "main", {} } };
  inPorts["main"].resize( 1 );
  outPorts = { { "main", {} } };
  outPorts["main"].resize( amount_ );
}

void MonoToN::updateConfig( std::string const& option, std::any const& newValue ) {
  logger_->trace( fmt::runtime( "updateConfig( option={:?}, newValue={} )" ), option, newValue.type().name() );
}

void MonoToN::update() {
  float input;
  while( inPorts["main"][0] && inPorts["main"][0]->pop( input ) ) {
    for( size_t i = 0; i < amount_; i++ ) {
      outPorts["main"][i]->push( input );
    }
  }
}

void MonoToN::deinit() {
  logger_->trace( fmt::runtime( "deinit()" ) );

  inPorts["main"] = {};
  outPorts["main"] = {};
}

}  // namespace SFG::SystemSimulator::AudioInterface::Transforms
