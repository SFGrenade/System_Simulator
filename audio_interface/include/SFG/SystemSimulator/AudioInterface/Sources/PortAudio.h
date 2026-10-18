#pragma once

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/Types/Node.h"
#include "SFG/SystemSimulator/AudioInterface/_portaudio.h"

// Project Includes
#include <SFG/SystemSimulator/Logger/_spdlog.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

// Library Includes
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
    "sourceName" = "",
    "apiName" = "",
    "channels" = 1,
    "sampleRate" = 44100.0
  }
*/
class PortAudio : public Types::AudioSourceNode {
  public:
  virtual ~PortAudio() = default;
  virtual void init( std::map< std::string, std::any > const& config ) override;
  virtual void updateConfig( std::string const& option, std::any const& newValue ) override;
  virtual bool update() override;
  virtual void deinit() override;

  private:
  // generic
  Logger::spdlogger logger_ = Logger::LoggerFactory::get_logger( "Sources::PortAudio" );
  // portaudio
  std::shared_ptr< PaStream > stream_ = nullptr;
  PaStreamParameters parameters_{};
  std::string sourceName_ = "";
  std::string apiName_ = "";
  size_t channels_ = 1;
  double sampleRate_ = 0.0;
  std::vector< std::shared_ptr< soxr > > soxrs_;  // resampling
  soxr_io_spec_t soxrIoSpec_;                     // resampling
};

}  // namespace SFG::SystemSimulator::AudioInterface::Sources
