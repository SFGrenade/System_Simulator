// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/Transforms/MonoToN.h"

namespace SFG::SystemSimulator::AudioInterface::Transforms {

void MonoToN::init( std::map< std::string, std::any > const& config ) {
  amount_ = std::any_cast< size_t >( config.at( "amount" ) );
  logger_->trace( fmt::runtime( "init( {:d} )" ), amount_ );

  inPorts = { { "main", {} } };
  inPorts["main"].resize( 1 );
  outPorts = { { "main", {} } };
  outPorts["main"].resize( amount_ );
}

void MonoToN::updateConfig( std::string const& option, std::any const& newValue ) {
  logger_->trace( fmt::runtime( "deinit( option={:?}, newValue={} )" ), option, newValue.type().name() );
}

bool MonoToN::update() {
  if( inPorts["main"][0] ) {
    std::vector< float > tmp( inPorts["main"][0]->read_available() );
    size_t popped = inPorts["main"][0]->pop( tmp.data(), tmp.size() );
    logger_->trace( fmt::runtime( "pulled {:d} (act: {:d}) samples" ), tmp.size(), popped );
    for( size_t i = 0; i < amount_; i++ ) {
      size_t pushed = outPorts["main"][i]->push( tmp.data(), tmp.size() );
      logger_->trace( fmt::runtime( "pushed {:d} (act: {:d}) samples" ), tmp.size(), pushed );
    }
  }

  return true;
}

void MonoToN::deinit() {
  logger_->trace( fmt::runtime( "deinit()" ) );

  std::vector< Types::InputPort< Types::AudioMessage > >( 0 ).swap( inPorts["main"] );
  std::vector< Types::OutputPort< Types::AudioMessage > >( 0 ).swap( outPorts["main"] );
}

}  // namespace SFG::SystemSimulator::AudioInterface::Transforms
