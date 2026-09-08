#pragma once

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/AudioFormat.h"
#include "SFG/SystemSimulator/AudioInterface/LastOrNoneCombiner.h"

// Library Includes
#include <boost/signals2.hpp>

namespace bs2 = boost::signals2;

namespace SFG::SystemSimulator::AudioInterface {

using PushAudioSignal = bs2::signal< void( AudioChunk const& ) >;
using PushFormatSignal = bs2::signal< void( AudioFormat const& ) >;
using PullAudioSignal = bs2::signal< AudioChunk( size_t ), LastOrNone< AudioChunk > >;
using PullFormatSignal = bs2::signal< AudioFormat(), LastOrNone< AudioFormat > >;

class Pusher {
  public:
  virtual ~Pusher() = default;

  PushAudioSignal& pushAudioSignal();    // connect downstream consumers here
  PushFormatSignal& pushFormatSignal();  // connect downstream consumers here

  protected:
  void emitAudio( AudioChunk const& samples );   // fire downstream
  void emitFormat( AudioFormat const& format );  // fire downstream

  protected:
  PushAudioSignal pushAudio_;
  PushFormatSignal pushFormat_;
};

class Puller {
  public:
  virtual ~Puller() = default;

  PullAudioSignal& pullAudioSignal();    // connect upstream producers here
  PullFormatSignal& pullFormatSignal();  // connect upstream producers here

  protected:
  std::optional< AudioChunk > requestAudio( size_t frames );  // fetch from upstream
  std::optional< AudioFormat > requestFormat();               // fetch from upstream

  protected:
  PullAudioSignal pullAudio_;
  PullFormatSignal pullFormat_;
};

class DownStream {
  public:
  virtual void onPushAudio( AudioChunk const& samples );   // override in push mode
  virtual void onPushFormat( AudioFormat const& format );  // override in push mode
};

class UpStream {
  public:
  virtual AudioChunk onPullAudio( size_t frames );  // override in pull mode
  virtual AudioFormat onPullFormat();               // override in pull mode
};

template < class Push, class Down >
std::vector< bs2::connection > conPush2Down( std::shared_ptr< Push > pusher, std::shared_ptr< Down > downStream ) {
  return { pusher->pushAudioSignal().connect(
               PushAudioSignal::slot_type( std::bind( &Down::onPushAudio, downStream.get(), std::placeholders::_1 ) ).track_foreign( downStream ) ),
           pusher->pushFormatSignal().connect(
               PushFormatSignal::slot_type( std::bind( &Down::onPushFormat, downStream.get(), std::placeholders::_1 ) ).track_foreign( downStream ) ) };
}

template < class Pull, class Up >
std::vector< bs2::connection > conPull2Up( std::shared_ptr< Pull > puller, std::shared_ptr< Up > upStream ) {
  return { puller->pullAudioSignal().connect(
               PullAudioSignal::slot_type( std::bind( &Up::onPullAudio, upStream.get(), std::placeholders::_1 ) ).track_foreign( upStream ) ),
           puller->pullFormatSignal().connect( PullFormatSignal::slot_type( std::bind( &Up::onPullFormat, upStream.get() ) ).track_foreign( upStream ) ) };
}

}  // namespace SFG::SystemSimulator::AudioInterface
