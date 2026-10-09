// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/Transforms/Buffer.h"

namespace SFG::SystemSimulator::AudioInterface::Transforms {

void Buffer::onPushAudio( AudioChunk const& samples ) {
  buffer_->insert( buffer_->end(), samples.begin(), samples.end() );
}

AudioChunk Buffer::onPullAudio( size_t frames ) {
  size_t framesToCopy = std::min( frames, buffer_->size() );
  AudioChunk ret( framesToCopy );
  std::move( buffer_->begin(), buffer_->begin() + framesToCopy, ret.data() );
  buffer_->erase_begin( framesToCopy );
  return ret;
}

}  // namespace SFG::SystemSimulator::AudioInterface::Transforms
