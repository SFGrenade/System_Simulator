#pragma once

// Library Includes
#include <boost/lockfree/spsc_queue.hpp>

// C++ Includes
#include <memory>
#include <vector>

namespace SFG::SystemSimulator::AudioInterface::Types {

constexpr inline size_t const RTP_MESSAGE_CAPACITY = 1 << 12;
using RtpMessage = boost::lockfree::spsc_queue< float, boost::lockfree::fixed_sized< true >, boost::lockfree::capacity< RTP_MESSAGE_CAPACITY > >;

}  // namespace SFG::SystemSimulator::AudioInterface::Types
