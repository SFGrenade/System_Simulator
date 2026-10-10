#pragma once

// Project Includes
// #include "SFG/SystemSimulator/AudioInterface/DynamicLibrary/PipeWire.detail.h"
#include "SFG/SystemSimulator/AudioInterface/DynamicLibrary/_lookup.h"

// Project Includes
#include <SFG/SystemSimulator/Logger/_spdlog.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

// C++ Includes
#include <atomic>
#include <memory>
#include <string>

namespace SFG::SystemSimulator::AudioInterface::DynamicLibrary {

class PipeWire {
  public:
  PipeWire();
  virtual ~PipeWire() = default;

  bool isAvailable() const;

  public:
  // library methods here

  private:
  // generic
  Logger::spdlogger logger_ = Logger::LoggerFactory::get_logger( "DynamicLibrary::PipeWire" );
  LibraryHandle library_ = nullptr;

  private:
  // library function pointers here
};

}  // namespace SFG::SystemSimulator::AudioInterface::DynamicLibrary
