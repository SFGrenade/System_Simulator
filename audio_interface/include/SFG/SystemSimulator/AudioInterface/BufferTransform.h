#pragma once

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/AudioNode.h"

// Project Includes
#include <SFG/SystemSimulator/Logger/_spdlog.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

namespace SFG::SystemSimulator::AudioInterface {

class BufferTransform {
  public:
  void onPushAudio( AudioChunk const& samples );
  AudioChunk onPullAudio( size_t frames );

  private:
  Logger::spdlogger logger_ = Logger::LoggerFactory::get_logger( "BufferTransform" );
  AudioQueue buffer_{ AudioQueueDefaultCapacity };
};

}  // namespace SFG::SystemSimulator::AudioInterface
