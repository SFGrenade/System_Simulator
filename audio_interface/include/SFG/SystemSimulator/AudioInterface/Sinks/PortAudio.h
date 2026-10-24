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

namespace SFG::SystemSimulator::AudioInterface::Sinks {

/*
  config is:
  {
    "sourceName": "",
    "apiName": "",
    "channels": 1,
    "sampleRate": 0.0,
    "framesPerBuffer": 0
  }
*/
class PortAudio : public Types::AudioSinkNode {
  public:
  virtual ~PortAudio() = default;
  virtual void init( std::map< std::string, std::any > const& config ) override;
  virtual void updateConfig( std::string const& option, std::any const& newValue ) override;
  virtual void update() override;
  virtual void deinit() override;

  private:
  // generic
  Logger::spdlogger logger_ = Logger::LoggerFactory::get_logger( "Sinks::PortAudio" );
  // portaudio
  std::unique_ptr< PaStream, decltype( &Pa_CloseStream ) > stream_{ nullptr, Pa_CloseStream };
  PaStreamParameters parameters_{};
  std::string sourceName_ = "";
  std::string apiName_ = "";
  int64_t channels_ = 1;
  double sampleRate_ = 0.0;
  int64_t framesPerBuffer_ = 0;
  std::unique_ptr< soxr, decltype( &soxr_delete ) > resampler_{ nullptr, soxr_delete };

  // now for performance
  private:
  size_t rawFrames_ = 0;
  size_t internalFrames_ = 0;
  std::vector< float > rawBuffer_{};
  std::vector< float > internalBuffer_{};
};

}  // namespace SFG::SystemSimulator::AudioInterface::Sinks
