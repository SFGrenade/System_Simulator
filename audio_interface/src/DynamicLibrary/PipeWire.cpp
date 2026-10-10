// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/DynamicLibrary/PipeWire.h"

namespace SFG::SystemSimulator::AudioInterface::DynamicLibrary {

PipeWire::PipeWire() {
  library_ = loadLibrary( "libpipewire-0.3.so.0" );

  // loading of library functions here
}

bool PipeWire::isAvailable() const {
  return true
      && library_
      // checking for valid library functions here
  ;
}

// pass-through methods here

}  // namespace SFG::SystemSimulator::AudioInterface::DynamicLibrary
