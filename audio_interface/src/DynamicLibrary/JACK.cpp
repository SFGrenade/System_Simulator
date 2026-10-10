// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/DynamicLibrary/JACK.h"

namespace SFG::SystemSimulator::AudioInterface::DynamicLibrary {

JACK::JACK() {
  library_ = loadLibrary( "libjack.so.0" );

  // loading of library functions here
}

bool JACK::isAvailable() const {
  return true
      && library_
      // checking for valid library functions here
  ;
}

// pass-through methods here

}  // namespace SFG::SystemSimulator::AudioInterface::DynamicLibrary
