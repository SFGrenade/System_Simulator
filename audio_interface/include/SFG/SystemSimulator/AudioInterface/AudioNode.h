#pragma once

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/AudioFormat.h"
#include "SFG/SystemSimulator/AudioInterface/LastOrNoneCombiner.h"

// Library Includes
#include <boost/signals2.hpp>

namespace bs2 = boost::signals2;

namespace SFG::SystemSimulator::AudioInterface {

using PushAudioSignal = bs2::signal< void( AudioChunk const& ) >;
using PushAudioSlot = PushAudioSignal::slot_type;
using PullAudioSignal = bs2::signal< AudioChunk( size_t ), LastOrNone< AudioChunk > >;
using PullAudioSlot = PullAudioSignal::slot_type;

template < class Push, class Down >
bs2::connection conPush2Down( PushAudioSignal& pushSignal, std::shared_ptr< Down > downStream, void ( Down::*downStreamFunc )( AudioChunk const& ) ) {
  return pushSignal.connect( PushAudioSignal::slot_type( std::bind( downStreamFunc, downStream.get(), std::placeholders::_1 ) ).track_foreign( downStream ) );
}

template < class Pull, class Up >
bs2::connection conPull2Up( PullAudioSignal& pullSignal, std::shared_ptr< Up > upStream, AudioChunk ( Up::*upStreamFunc )( size_t ) ) {
  return pullSignal.connect( PullAudioSignal::slot_type( std::bind( upStreamFunc, upStream.get(), std::placeholders::_1 ) ).track_foreign( upStream ) );
}

}  // namespace SFG::SystemSimulator::AudioInterface
