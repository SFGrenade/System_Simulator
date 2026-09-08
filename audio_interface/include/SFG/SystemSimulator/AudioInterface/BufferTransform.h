#pragma once

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/AudioNode.h"
#include "SFG/SystemSimulator/AudioInterface/_portaudio.h"

// Project Includes
#include <SFG/SystemSimulator/Logger/_spdlog.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

// Library Includes
#include <boost/lockfree/spsc_queue.hpp>

namespace SFG::SystemSimulator::AudioInterface {

class BufferTransform : public DownStream, public UpStream {
  public:
  virtual void onPushAudio( AudioChunk const& samples ) override;
  virtual void onPushFormat( AudioFormat const& format ) override;
  virtual AudioChunk onPullAudio( size_t frames ) override;
  virtual AudioFormat onPullFormat() override;

  private:
  Logger::spdlogger logger_ = Logger::LoggerFactory::get_logger( "BufferTransform" );
  boost::lockfree::spsc_queue< float, boost::lockfree::fixed_sized< true > > buffer_{ size_t( 1u ) << size_t( 14u ) };
  AudioFormat lastFormat_;
};

}  // namespace SFG::SystemSimulator::AudioInterface
