// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/DynamicLibrary/PulseAudio.h"

namespace SFG::SystemSimulator::AudioInterface::DynamicLibrary {

PulseAudio::PulseAudio() {
  library_ = loadLibrary( "libpulse.so.0" );

  // loading of library functions here
}

bool PulseAudio::isAvailable() const {
  return true
      && library_
      // checking for valid library functions here
  ;
}

// pass-through methods here

}  // namespace SFG::SystemSimulator::AudioInterface::DynamicLibrary
