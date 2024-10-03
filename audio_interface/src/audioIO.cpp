#include "SFG/SystemSimulator/AudioInterface/audioIO.h"

namespace SFG {
namespace SystemSimulator {
namespace AudioInterface {

AudioIO::AudioIO() : logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "AudioIO" ) ), config_( "config/recording_server.ini" ) {
  this->logger_->trace( fmt::runtime( "AudioIO" ) );

  this->logger_->trace( fmt::runtime( "AudioIO~" ) );
}

AudioIO::~AudioIO() {
  this->logger_->trace( fmt::runtime( "~AudioIO" ) );

  this->logger_->trace( fmt::runtime( "~AudioIO~" ) );
}

}  // namespace AudioInterface
}  // namespace SystemSimulator
}  // namespace SFG
