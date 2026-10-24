#pragma once

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/Types/Node.h"

// Project Includes
#include <SFG/SystemSimulator/Logger/_spdlog.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

// Library Includes
#include <dr_mp3.h>
#include <soxr.h>

// C++ Includes
#include <any>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace SFG::SystemSimulator::AudioInterface::Sources {

/*
  config is:
  {
    "fileName": "",
    "framesPerBuffer": 0
  }
*/
class Mp3File : public Types::AudioSourceNode {
  public:
  virtual ~Mp3File() = default;
  virtual void init( std::map< std::string, std::any > const& config ) override;
  virtual void updateConfig( std::string const& option, std::any const& newValue ) override;
  virtual void update() override;
  virtual void deinit() override;

  private:
  // generic
  Logger::spdlogger logger_ = Logger::LoggerFactory::get_logger( "Sources::Mp3File" );
  // Mp3File
  drmp3 mp3_;
  std::string fileName_ = "";
  int64_t framesPerBuffer_ = 0;
  std::unique_ptr< soxr, decltype( &soxr_delete ) > resampler_{ nullptr, soxr_delete };

  // now for performance
  private:
  size_t rawFrames_ = 0;
  size_t internalFrames_ = 0;
  std::vector< float > rawBuffer_{};
  std::vector< float > internalBuffer_{};
};

}  // namespace SFG::SystemSimulator::AudioInterface::Sources
