#pragma once

// Library Includes
#include <boost/lockfree/spsc_queue.hpp>

namespace SFG::SystemSimulator::AudioInterface::Types {

constexpr inline size_t const AUDIO_MESSAGE_CAPACITY = 1 << 12;
using AudioMessage = boost::lockfree::spsc_queue< float, boost::lockfree::fixed_sized< true >, boost::lockfree::capacity< AUDIO_MESSAGE_CAPACITY > >;

}  // namespace SFG::SystemSimulator::AudioInterface::Types
