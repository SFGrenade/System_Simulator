#pragma once

// Project Includes
#include <SFG/SystemSimulator/AudioInterface/RingBuffer.h>

// C++ Includes
#include <memory>
#include <vector>

namespace SFG::SystemSimulator::AudioInterface {

constexpr inline double const INTERNAL_SAMPLERATE = 44100.0;

using AudioChunk = std::vector< float >;

constexpr inline size_t const BUFFER_DEFAULT_SIZE = 1 << 12;
using AudioQueue = RingBuffer< float, BUFFER_DEFAULT_SIZE >;

}  // namespace SFG::SystemSimulator::AudioInterface
