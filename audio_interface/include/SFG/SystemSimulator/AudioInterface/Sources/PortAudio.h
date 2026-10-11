#pragma once

// Project Includes
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

struct PortAudioConfig {
  std::string sourceName = "";
  std::string apiName = "";
  int channels = 1;
  double sampleRate = 44100.0;
  bool pulling = false;
  size_t framesPerBuffer = 512;
};

class PortAudio : public AudioNode< PortAudioConfig >, public ThreadNode {
  public:
  virtual void init( PortAudioConfig const& config ) override;
  virtual void start() override;
  virtual void stop() override;
  virtual void deinit() override;

  std::vector< PushAudioSignal >& pushSignals();
  AudioChunk onPullAudio( size_t channel, size_t frames );

  protected:
  virtual void threadRun() override;

  PaStreamCallbackResult callback( void const* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, PaStreamCallbackTimeInfo const* timeInfo, PaStreamCallbackFlags statusFlags );
  static int s_callback( void const* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, PaStreamCallbackTimeInfo const* timeInfo, PaStreamCallbackFlags statusFlags, void* userData );

  private:
  // generic
  Logger::spdlogger logger_ = Logger::LoggerFactory::get_logger( "Sources::PortAudio" );
  // portaudio
  std::shared_ptr< PaStream > stream_ = nullptr;
  PaStreamParameters parameters_{};
  PortAudioConfig config_;
  // thread
  std::atomic< bool > pulling_ = false;                       // wether or not
  std::vector< std::shared_ptr< soxr > > soxrs_;              // resampling
  std::vector< std::unique_ptr< AudioQueue > > audioQueues_;  // decoupling
  std::vector< PushAudioSignal > pushSignals_;                // connections
};

}  // namespace SFG::SystemSimulator::AudioInterface::Sources
