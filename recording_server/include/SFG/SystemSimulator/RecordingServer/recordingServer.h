#ifndef RECORDING_SERVER_RECORDINGSERVER_H_
#define RECORDING_SERVER_RECORDINGSERVER_H_

#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <list>
#include <map>

namespace SFG {
namespace SystemSimulator {
namespace RecordingServer {

class RecordingServer {
  public:
  RecordingServer();
  ~RecordingServer();

  void setupAudioGenerator( std::string const& generatorId, uint16_t channels, uint32_t sampleRate, uint16_t bitsPerSample );
  void streamAudioFrame( std::string const& generatorId, std::list< char > data );

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  SFG::SystemSimulator::Configuration::Configuration config_;
  std::string exportPath_;
};

}  // namespace RecordingServer
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* RECORDING_SERVER_RECORDINGSERVER_H_ */
