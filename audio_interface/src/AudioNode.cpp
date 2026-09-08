// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/AudioNode.h"

namespace SFG::SystemSimulator::AudioInterface {

AudioNode::PushAudioSignal& AudioNode::pushAudioSignal() {
  return pushAudio_;
}

AudioNode::PushFormatSignal& AudioNode::pushFormatSignal() {
  return pushFormat_;
}

AudioNode::PullAudioSignal& AudioNode::pullAudioSignal() {
  return pullAudio_;
}

AudioNode::PullFormatSignal& AudioNode::pullFormatSignal() {
  return pullFormat_;
}

void AudioNode::onPushAudio( AudioChunk const& /*samples*/ ) {}

void AudioNode::onPushFormat( AudioFormat const& /*format*/ ) {}

AudioChunk AudioNode::onPullAudio( size_t frames ) {
  AudioChunk ret( frames, 0.0f );
  return ret;
}

AudioFormat AudioNode::onPullFormat() {
  AudioFormat ret;
  return ret;
}

void AudioNode::emitAudio( AudioChunk const& samples ) {
  pushAudio_( samples );
}

void AudioNode::emitFormat( AudioFormat const& format ) {
  pushFormat_( format );
}

std::optional< AudioChunk > AudioNode::requestAudio( size_t frames ) {
  return pullAudio_( frames );
}

std::optional< AudioFormat > AudioNode::requestFormat() {
  return pullFormat_();
}

}  // namespace SFG::SystemSimulator::AudioInterface
