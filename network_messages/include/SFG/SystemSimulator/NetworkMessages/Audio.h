#ifndef NETWORK_MESSAGES_AUDIO_H_
#define NETWORK_MESSAGES_AUDIO_H_

#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <string>
#include <vector>

namespace SFG {
namespace SystemSimulator {
namespace NetworkMessages {

class AudioFormatInformation {
  public:
  std::string audio_generator_id = "";
  uint32_t channels = 0;
  uint32_t sample_rate = 0;
  uint32_t bits_per_sample = 0;

  bool operator==( AudioFormatInformation const& b ) const;

  private:
  friend class boost::serialization::access;
  template < class Archive >
  void serialize( Archive& ar, unsigned int const /*version*/ ) {
    ar& audio_generator_id;
    ar& channels;
    ar& sample_rate;
    ar& bits_per_sample;
  }
};

class AudioFrame {
  public:
  std::string audio_generator_id = "";
  std::vector< uint8_t > audio_data = std::vector< uint8_t >();

  bool operator==( AudioFrame const& b ) const;

  private:
  friend class boost::serialization::access;
  template < class Archive >
  void serialize( Archive& ar, unsigned int const /*version*/ ) {
    ar& audio_generator_id;
    ar& audio_data;
  }
};

}  // namespace NetworkMessages
}  // namespace SystemSimulator
}  // namespace SFG

#endif  // NETWORK_MESSAGES_AUDIO_H_
