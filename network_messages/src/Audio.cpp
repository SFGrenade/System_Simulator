#include "SFG/SystemSimulator/NetworkMessages/Audio.h"

namespace SFG {
namespace SystemSimulator {
namespace NetworkMessages {

bool AudioFormatInformation::operator==( AudioFormatInformation const& b ) const {
  bool ret = true;
  ret = ret && ( this->audio_generator_id == b.audio_generator_id );
  ret = ret && ( this->channels == b.channels );
  ret = ret && ( this->sample_rate == b.sample_rate );
  ret = ret && ( this->bits_per_sample == b.bits_per_sample );
  return ret;
}

bool AudioFrame::operator==( AudioFrame const& b ) const {
  bool ret = true;
  ret = ret && ( this->audio_generator_id == b.audio_generator_id );
  ret = ret && ( this->audio_data == b.audio_data );
  return ret;
}

}  // namespace NetworkMessages
}  // namespace SystemSimulator
}  // namespace SFG
