#pragma once

// Project Includes
// #include "SFG/SystemSimulator/AudioInterface/DynamicLibrary/PulseAudio.detail.h"
#include "SFG/SystemSimulator/AudioInterface/DynamicLibrary/_lookup.h"

// Project Includes
#include <SFG/SystemSimulator/Logger/_spdlog.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

// C++ Includes
#include <atomic>
#include <memory>
#include <string>

namespace SFG::SystemSimulator::AudioInterface::DynamicLibrary {

class PulseAudio {
  public:
  PulseAudio();
  virtual ~PulseAudio() = default;

  bool isAvailable() const;

  public:
  // library methods here

  private:
  // generic
  Logger::spdlogger logger_ = Logger::LoggerFactory::get_logger( "DynamicLibrary::PulseAudio" );
  LibraryHandle library_ = nullptr;

  private:
  // library function pointers here
};

}  // namespace SFG::SystemSimulator::AudioInterface::DynamicLibrary
