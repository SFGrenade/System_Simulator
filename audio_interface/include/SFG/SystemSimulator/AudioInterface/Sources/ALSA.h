#pragma once

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/AudioNode.h"
#include "SFG/SystemSimulator/AudioInterface/DynamicLibrary/ALSA.detail.h"
#include "SFG/SystemSimulator/AudioInterface/DynamicLibrary/ALSA.h"

// Project Includes
#include <SFG/SystemSimulator/Logger/_spdlog.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

// Library Includes
#include <soxr.h>

// C++ Includes
#include <atomic>
#include <string>
#include <thread>

namespace SFG::SystemSimulator::AudioInterface::Sources {

namespace DynAlsa = SFG::SystemSimulator::AudioInterface::DynamicLibrary::ALSA_detail;

struct ALSAConfig {
  std::string sourceName = "";
  int openMode = 0;

  unsigned int hwResample = 1;
  DynAlsa::snd_pcm_access_t access = DynAlsa::snd_pcm_access_t::SND_PCM_ACCESS_RW_INTERLEAVED;
  DynAlsa::snd_pcm_format_t format = DynAlsa::snd_pcm_format_t::SND_PCM_FORMAT_FLOAT;
  unsigned int channels = 1;
  unsigned int sampleRate = 44100;
  DynAlsa::snd_pcm_uframes_t framesPerBuffer = 512;
  DynAlsa::snd_pcm_uframes_t alsaBufferSize = 1024;
};

class ALSA : public AudioNode< ALSAConfig >, public ThreadNode {
  public:
  virtual void init( ALSAConfig const& config ) override;
  virtual void start() override;
  virtual void stop() override;
  virtual void deinit() override;

  std::vector< PushAudioSignal >& pushSignals();
  AudioChunk onPullAudio( size_t channel, size_t frames );

  protected:
  virtual void threadRun() override;

  private:
  // generic
  Logger::spdlogger logger_ = Logger::LoggerFactory::get_logger( "Sources::ALSA" );
  // ALSA
  DynamicLibrary::ALSA alsa_;
  DynamicLibrary::ALSA_detail::snd_pcm_t* alsaPcm_ = nullptr;
  DynamicLibrary::ALSA_detail::snd_pcm_hw_params_t* alsaHwParams_ = nullptr;
  ALSAConfig config_;
  // audio
  std::vector< std::shared_ptr< soxr > > soxrs_;              // resampling
  std::vector< std::unique_ptr< AudioQueue > > audioQueues_;  // decoupling
  std::vector< PushAudioSignal > pushSignals_;                // connections
};

}  // namespace SFG::SystemSimulator::AudioInterface::Sources
