#pragma once

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/DynamicLibrary/ALSA.h"
#include "SFG/SystemSimulator/AudioInterface/AudioNode.h"
#include "SFG/SystemSimulator/AudioInterface/_portaudio.h"

// Project Includes
#include <SFG/SystemSimulator/Logger/_spdlog.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

// Library Includes
#include <soxr.h>

// C++ Includes
#include <atomic>
#include <memory>
#include <string>
#include <thread>

namespace SFG::SystemSimulator::AudioInterface::Sources {

class ALSA {
  public:
  void init();
  void start();
  void stop();

  std::vector< PushAudioSignal >& pushSignals();
  AudioChunk onPullAudio( size_t channel, size_t frames );

  private:
  void threadRun();

  private:
  // generic
  Logger::spdlogger logger_ = Logger::LoggerFactory::get_logger( "Sources::ALSA" );
  std::atomic< bool > running_ = false;
  // ALSA
  DynamicLibrary::ALSA alsa_;
  PaStreamParameters parameters_{};
  double samplerate_ = 0.0;
  size_t framesPerBuffer_ = 0;
  // thread
  std::thread thread_;
  std::vector< std::shared_ptr< soxr > > soxrs_;  // resampling
  std::vector< std::unique_ptr< AudioQueue > > audioQueues_;
  std::vector< PushAudioSignal > pushSignals_;
};

}  // namespace SFG::SystemSimulator::AudioInterface::Sources
