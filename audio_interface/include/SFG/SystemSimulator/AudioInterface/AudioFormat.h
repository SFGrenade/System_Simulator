#pragma once

#include <cstdint>
#include <vector>

namespace SFG::SystemSimulator::AudioInterface {

using AudioChunk = std::vector< float >;

struct AudioFormat {
  float sampleRate = 44100.0f;
  uint16_t channels = 1;

  friend bool operator<( AudioFormat const& lhs, AudioFormat const& rhs ) noexcept;
  friend bool operator==( AudioFormat const& lhs, AudioFormat const& rhs ) noexcept;
};

inline bool operator>( AudioFormat const& lhs, AudioFormat const& rhs ) noexcept;
inline bool operator<=( AudioFormat const& lhs, AudioFormat const& rhs ) noexcept;
inline bool operator>=( AudioFormat const& lhs, AudioFormat const& rhs ) noexcept;
inline bool operator!=( AudioFormat const& lhs, AudioFormat const& rhs ) noexcept;

}  // namespace SFG::SystemSimulator::AudioInterface
