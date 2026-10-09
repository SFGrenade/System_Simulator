#include "SFG/SystemSimulator/AudioInterface/AudioFormat.h"

namespace SFG::SystemSimulator::AudioInterface {

std::unique_ptr< AudioQueue > makeAudioQueue() {
  return std::unique_ptr< AudioQueue >( new AudioQueue( BUFFER_DEFAULT_SIZE, 0.0 ) );
}

}  // namespace SFG::SystemSimulator::AudioInterface
