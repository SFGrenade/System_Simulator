#ifndef AUDIO_INTERFACE_AUDIOIO_H_
#define AUDIO_INTERFACE_AUDIOIO_H_

#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

#include "SFG/SystemSimulator/AudioInterface/NetConnector.h"
#include "SFG/SystemSimulator/AudioInterface/_portaudio.h"

namespace SFG {
namespace SystemSimulator {
namespace AudioInterface {

class AudioIO {
  public:
  struct MySettingsStruct {
    float outputMultiplier;

    PortAudio::PaStream *portAudioStream;
    PortAudio::PaStreamParameters inputSettings;
    PortAudio::PaStreamParameters outputSettings;
    double sampleRate;
    unsigned long framesPerBuffer;
    PortAudio::PaStreamFlags flags;
    SFG::SystemSimulator::AudioInterface::NetConnector *netConnector;
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

#endif /* AUDIO_INTERFACE_AUDIOIO_H_ */
