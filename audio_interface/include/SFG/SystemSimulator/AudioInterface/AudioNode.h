#pragma once

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/AudioFormat.h"
#include "SFG/SystemSimulator/AudioInterface/LastOrNoneCombiner.h"

// Library Includes
#include <boost/signals2.hpp>

namespace bs2 = boost::signals2;

namespace SFG::SystemSimulator::AudioInterface {

class AudioNode {
  public:
  using PushAudioSignal = bs2::signal< void( AudioChunk const& ) >;
  using PushFormatSignal = bs2::signal< void( AudioFormat const& ) >;
  using PullAudioSignal = bs2::signal< AudioChunk( size_t ), LastOrNone< AudioChunk > >;
  using PullFormatSignal = bs2::signal< AudioFormat(), LastOrNone< AudioFormat > >;

  public:
  virtual ~AudioNode() = default;

  PushAudioSignal& pushAudioSignal();    // connect downstream consumers here
  PushFormatSignal& pushFormatSignal();  // connect downstream consumers here
  PullAudioSignal& pullAudioSignal();    // connect upstream producers here
  PullFormatSignal& pullFormatSignal();  // connect upstream producers here

  virtual void onPushAudio( AudioChunk const& samples );   // override in push mode
  virtual void onPushFormat( AudioFormat const& format );  // override in push mode
  virtual AudioChunk onPullAudio( size_t frames );         // override in pull mode
  virtual AudioFormat onPullFormat();                      // override in pull mode

  protected:
  void emitAudio( AudioChunk const& samples );                // fire downstream
  void emitFormat( AudioFormat const& format );               // fire downstream
  std::optional< AudioChunk > requestAudio( size_t frames );  // fetch from upstream
  std::optional< AudioFormat > requestFormat();               // fetch from upstream

  protected:
  PushAudioSignal pushAudio_;
  PushFormatSignal pushFormat_;
  PullAudioSignal pullAudio_;
  PullFormatSignal pullFormat_;
};

}  // namespace SFG::SystemSimulator::AudioInterface
