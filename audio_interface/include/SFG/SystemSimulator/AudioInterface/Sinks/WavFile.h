#pragma once

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/Types/Node.h"

// Project Includes
#include <SFG/SystemSimulator/Logger/_spdlog.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

// Library Includes
#include <dr_wav.h>

// C++ Includes
#include <any>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace SFG::SystemSimulator::AudioInterface::Sinks {

/*
  config is:
  {
    "fileName": "",
    "channels": 1,
    "framesPerBuffer": 0
  }
*/
class WavFile : public Types::AudioSinkNode {
  public:
  virtual ~WavFile() = default;
  virtual void init( std::map< std::string, std::any > const& config ) override;
  virtual void updateConfig( std::string const& option, std::any const& newValue ) override;
  virtual void update() override;
  virtual void deinit() override;

  private:
  // generic
  Logger::spdlogger logger_ = Logger::LoggerFactory::get_logger( "Sinks::WavFile" );
  // WavFile
  drwav wav_;
  drwav_data_format format_;
  std::string fileName_ = "";
  int64_t channels_ = 1;
  int64_t framesPerBuffer_ = 0;

  // now for performance
  private:
  size_t internalFrames_ = 0;
  std::vector< float > internalBuffer_{};
};

}  // namespace SFG::SystemSimulator::AudioInterface::Sinks
