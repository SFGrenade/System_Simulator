#include "SFG/SystemSimulator/AudioInterface/AudioFormat.h"

namespace SFG::SystemSimulator::AudioInterface {

std::unique_ptr< AudioQueue > makeQueue( size_t capacity ) {
  return std::make_unique< AudioQueue >( capacity );
}

}  // namespace SFG::SystemSimulator::AudioInterface
