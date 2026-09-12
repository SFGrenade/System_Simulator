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

namespace SFG::SystemSimulator::AudioInterface {

class PortAudioSource {
  public:
  void init( std::string const& sourceName, std::string const& apiName, bool pulling = false, size_t framesPerBuffer = -1 );
  void start();
  void stop();

  std::vector< PushAudioSignal >& pushSignals();
  AudioChunk onPullAudio( size_t channel, size_t frames );

  private:
  void threadRun();
  PaStreamCallbackResult callback( void const* inputBuffer,
                                   void* outputBuffer,
                                   unsigned long framesPerBuffer,
                                   PaStreamCallbackTimeInfo const* timeInfo,
                                   PaStreamCallbackFlags statusFlags );
  static int s_callback( void const* inputBuffer,
                         void* outputBuffer,
                         unsigned long framesPerBuffer,
                         PaStreamCallbackTimeInfo const* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void* userData );

  private:
  // generic
  Logger::spdlogger logger_ = Logger::LoggerFactory::get_logger( "PortAudioSource" );
  std::atomic< bool > running_ = false;
  // portaudio
  std::shared_ptr< PaStream > stream_ = nullptr;
  PaStreamParameters parameters_{};
  double samplerate_ = 0.0;
  size_t framesPerBuffer_ = 0;
  PaStreamFlags flags_ = PA::noFlag;
  // thread
  std::atomic< bool > pulling_ = false;
  std::thread thread_;
  std::vector< std::shared_ptr< soxr > > soxrs_;  // resampling
  std::vector< std::unique_ptr< AudioQueue > > audioQueues_;
  std::vector< PushAudioSignal > pushSignals_;
};

}  // namespace SFG::SystemSimulator::AudioInterface
