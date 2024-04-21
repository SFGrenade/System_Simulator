#ifndef NETWORK_MESSAGES_AUDIO_H_
#define NETWORK_MESSAGES_AUDIO_H_

#include <networkingHelper/networkMessage.hpp>
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
  friend class bitsery::Access;
  template < typename S >
  void serialize( S& s ) {
    s.text1b( audio_generator_id, 1024 );
    s.value4b( channels );
    s.value4b( sample_rate );
    s.value4b( bits_per_sample );
  }
  template < typename S >
  void deserialize( S& s ) {
    s.text1b( audio_generator_id, 1024 );
    s.value4b( channels );
    s.value4b( sample_rate );
    s.value4b( bits_per_sample );
  }
};

class AudioFrame {
  public:
  std::string audio_generator_id = "";
  std::vector< uint8_t > audio_data = std::vector< uint8_t >();

  bool operator==( AudioFrame const& b ) const;

  private:
  friend class bitsery::Access;
  template < typename S >
  void serialize( S& s ) {
    s.text1b( audio_generator_id, 1024 );
    s.container1b( audio_data, 10240 );  // some sane default? like at most 10KiB per frame?
  }
  template < typename S >
  void deserialize( S& s ) {
    s.text1b( audio_generator_id, 1024 );
    s.container1b( audio_data, 10240 );  // some sane default? like at most 10KiB per frame?
  }
};

}  // namespace NetworkMessages
}  // namespace SystemSimulator
}  // namespace SFG

#endif  // NETWORK_MESSAGES_AUDIO_H_
