#pragma once

// Library Includes
#include <boost/lockfree/spsc_queue.hpp>

// C++ Includes
#include <memory>
#include <vector>

namespace SFG::SystemSimulator::AudioInterface {

constexpr inline double const INTERNAL_SAMPLERATE = 44100.0;

using AudioChunk = std::vector< float >;

constexpr inline size_t const AudioQueueDefaultCapacity = 1 << 12;
using AudioQueue = boost::lockfree::spsc_queue< float, boost::lockfree::fixed_sized< true > >;
std::unique_ptr< AudioQueue > makeQueue( size_t capacity = AudioQueueDefaultCapacity );

}  // namespace SFG::SystemSimulator::AudioInterface
