// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/Transforms/Buffer.h"

namespace SFG::SystemSimulator::AudioInterface::Transforms {

void Buffer::onPushAudio( AudioChunk const& samples ) {
  buffer_.push( samples.data(), samples.size() );
}

AudioChunk Buffer::onPullAudio( size_t frames ) {
  size_t framesToCopy = std::min( frames, buffer_.read_available() );
  AudioChunk ret( framesToCopy );
  buffer_.pop( ret.data(), framesToCopy );
  return ret;
}

}  // namespace SFG::SystemSimulator::AudioInterface::Transforms
