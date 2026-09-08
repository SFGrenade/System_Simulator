// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/AudioNode.h"

namespace SFG::SystemSimulator::AudioInterface {

PushAudioSignal& Pusher::pushAudioSignal() {
  return pushAudio_;
}

PushFormatSignal& Pusher::pushFormatSignal() {
  return pushFormat_;
}

void Pusher::emitAudio( AudioChunk const& samples ) {
  pushAudio_( samples );
}

void Pusher::emitFormat( AudioFormat const& format ) {
  pushFormat_( format );
}

PullAudioSignal& Puller::pullAudioSignal() {
  return pullAudio_;
}

PullFormatSignal& Puller::pullFormatSignal() {
  return pullFormat_;
}

std::optional< AudioChunk > Puller::requestAudio( size_t frames ) {
  return pullAudio_( frames );
}

std::optional< AudioFormat > Puller::requestFormat() {
  return pullFormat_();
}

void DownStream::onPushAudio( AudioChunk const& /*samples*/ ) {}

void DownStream::onPushFormat( AudioFormat const& /*format*/ ) {}

AudioChunk UpStream::onPullAudio( size_t frames ) {
  AudioChunk ret( frames, 0.0f );
  return ret;
}

AudioFormat UpStream::onPullFormat() {
  AudioFormat ret;
  return ret;
}

}  // namespace SFG::SystemSimulator::AudioInterface
