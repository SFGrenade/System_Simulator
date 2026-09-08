#include "SFG/SystemSimulator/AudioInterface/AudioFormat.h"

#include <tuple>

namespace SFG::SystemSimulator::AudioInterface {

bool operator<( AudioFormat const& lhs, AudioFormat const& rhs ) noexcept {
  return std::tie( lhs.sampleRate, lhs.channels ) < std::tie( rhs.sampleRate, rhs.channels );
}
bool operator==( AudioFormat const& lhs, AudioFormat const& rhs ) noexcept {
  return std::tie( lhs.sampleRate, lhs.channels ) == std::tie( rhs.sampleRate, rhs.channels );
}

inline bool operator>( AudioFormat const& lhs, AudioFormat const& rhs ) noexcept {
  return rhs < lhs;
}

inline bool operator<=( AudioFormat const& lhs, AudioFormat const& rhs ) noexcept {
  return !( lhs > rhs );
}

inline bool operator>=( AudioFormat const& lhs, AudioFormat const& rhs ) noexcept {
  return !( lhs < rhs );
}

inline bool operator!=( AudioFormat const& lhs, AudioFormat const& rhs ) noexcept {
  return !( lhs == rhs );
}

}  // namespace SFG::SystemSimulator::AudioInterface
