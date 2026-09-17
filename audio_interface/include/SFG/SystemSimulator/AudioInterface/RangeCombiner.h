#pragma once

// Library Includes
#include <boost/signals2.hpp>

namespace bs2 = boost::signals2;

namespace SFG::SystemSimulator::AudioInterface {

template < class T >
struct RangeCombiner {
  using result_type = T;
  template < class It >
  result_type operator()( It first, It last ) const {
    result_type ret( 0 );
    if( first == last )
      return ret;
    while( first != last ) {
      ret.insert( ret.end(), first->begin(), first->end() );
      ++first;
    }
    return ret;
  }
};

}  // namespace SFG::SystemSimulator::AudioInterface
