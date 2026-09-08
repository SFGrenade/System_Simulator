// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/BufferTransform.h"

namespace SFG::SystemSimulator::AudioInterface {

void BufferTransform::onPushAudio( AudioChunk const& samples ) {
  buffer_.push( samples.data(), samples.size() );
}

void BufferTransform::onPushFormat( AudioFormat const& format ) {
  lastFormat_ = format;
}

AudioChunk BufferTransform::onPullAudio( size_t frames ) {
  size_t framesToCopy = std::min( frames, buffer_.read_available() );
  AudioChunk ret( framesToCopy );
  buffer_.pop( ret.data(), framesToCopy );
  return ret;
}

AudioFormat BufferTransform::onPullFormat() {
  return lastFormat_;
}

}  // namespace SFG::SystemSimulator::AudioInterface
