#pragma once

// Library Includes
#include <boost/circular_buffer.hpp>
#include <boost/lockfree/spsc_queue.hpp>

// C++ Includes
#include <memory>
#include <vector>

namespace SFG::SystemSimulator::AudioInterface {

constexpr inline double const INTERNAL_SAMPLERATE = 44100.0;

using AudioChunk = std::vector< float >;

constexpr inline size_t const BUFFER_DEFAULT_SIZE = 1 << 12;
using AudioQueue = boost::circular_buffer< float >;

std::unique_ptr< AudioQueue > makeAudioQueue();

}  // namespace SFG::SystemSimulator::AudioInterface
