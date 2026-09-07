#pragma once

#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

#include "SFG/SystemSimulator/AudioInterface/_portaudio.h"
#include "SFG/SystemSimulator/AudioInterface/netConnector.h"

namespace SFG {
namespace SystemSimulator {
namespace AudioInterface {

class AudioIO {
  public:
  struct MySettingsStruct {
    float outputMultiplier;

    PaStream* portAudioStream;
    PaStreamParameters inputSettings;
    PaStreamParameters outputSettings;
    double sampleRate;
    unsigned long framesPerBuffer;
    PaStreamFlags flags;
    SFG::SystemSimulator::AudioInterface::NetConnector* netConnector;
  };

  public:
  AudioIO();
  ~AudioIO();

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  SFG::SystemSimulator::Configuration::Configuration config_;
};

}  // namespace AudioInterface
}  // namespace SystemSimulator
}  // namespace SFG
