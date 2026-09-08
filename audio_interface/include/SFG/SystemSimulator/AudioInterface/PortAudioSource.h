#pragma once

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/AudioNode.h"
#include "SFG/SystemSimulator/AudioInterface/_portaudio.h"

// Project Includes
#include <SFG/SystemSimulator/Logger/_spdlog.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

// C++ Includes
#include <atomic>
#include <memory>
#include <string>
#include <thread>

namespace SFG::SystemSimulator::AudioInterface {

class PortAudioSource : public AudioNode {
  public:
  void start( std::string const& sourceName, std::string const& apiName, bool pulling = false, size_t framesPerBuffer = -1 );
  void stop();

  virtual AudioChunk onPullAudio( size_t frames ) override;
  virtual AudioFormat onPullFormat() override;

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
  Logger::spdlogger logger_ = Logger::LoggerFactory::get_logger( "PortAudioSource" );
  std::atomic< bool > running_ = false;
  std::shared_ptr< PaStream > stream_ = nullptr;
  std::thread thread_;
  std::atomic< bool > pulling_ = false;
  PaStreamParameters parameters_{};
  double samplerate_ = 0.0;
  size_t framesPerBuffer_ = 0;
  PaStreamFlags flags_ = PA::noFlag;
};

}  // namespace SFG::SystemSimulator::AudioInterface
