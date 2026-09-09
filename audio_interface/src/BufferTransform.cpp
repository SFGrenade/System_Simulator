// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/BufferTransform.h"

namespace SFG::SystemSimulator::AudioInterface {

void BufferTransform::onPushAudio( AudioChunk const& samples ) {
  buffer_.push( samples.data(), samples.size() );
}

AudioChunk BufferTransform::onPullAudio( size_t frames ) {
  size_t framesToCopy = std::min( frames, buffer_.read_available() );
  AudioChunk ret( framesToCopy );
  buffer_.pop( ret.data(), framesToCopy );
  return ret;
}

}  // namespace SFG::SystemSimulator::AudioInterface
