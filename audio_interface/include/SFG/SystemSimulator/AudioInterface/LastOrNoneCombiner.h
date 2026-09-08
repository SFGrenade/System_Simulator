#pragma once

// Library Includes
#include <boost/signals2.hpp>

// C++ Includes
#include <optional>

namespace bs2 = boost::signals2;

namespace SFG::SystemSimulator::AudioInterface {

template < class T >
struct LastOrNone {
  using result_type = std::optional< T >;
  template < class It >
  result_type operator()( It first, It last ) const {
    if( first == last )
      return {};
    result_type ret{};
    while( first != last ) {
      ret = *first;
      ++first;
    }
    return ret;
  }
};

}  // namespace SFG::SystemSimulator::AudioInterface
