#pragma once

// C++ Includes
#include <array>
#include <cstdint>
#include <thread>

namespace SFG::SystemSimulator::AudioInterface {

template < typename T, size_t N >
class RingBuffer {
  public:
  bool push( T const& value ) noexcept;
  size_t push( T const* a, size_t n ) noexcept;
  template < typename Iter >
  size_t push( Iter begin, Iter end ) noexcept;
  bool pop( T& value ) noexcept;
  size_t pop( T* a, size_t n ) noexcept;
  template < typename Iter >
  size_t pop( Iter begin, Iter end ) noexcept;

  size_t read_available() noexcept;

  private:
  std::array< T, N > buffer_;
  alignas( std::hardware_destructive_interference_size ) size_t head_{ 0 };
  alignas( std::hardware_destructive_interference_size ) size_t tail_{ 0 };
};

template < typename T, size_t N >
bool RingBuffer< T, N >::push( T const& value ) noexcept {
  size_t const head = head_;
  size_t next_head = head + 1;
  if( next_head == buffer_.size() ) [[unlikely]] {
    next_head = 0;
  }
  if( next_head == tail_ ) [[unlikely]] {
    tail_++;
  }
  buffer_[head] = value;
  head_ = next_head;
  return true;
}

template < typename T, size_t N >
size_t RingBuffer< T, N >::push( T const* a, size_t n ) noexcept {
  size_t ret = 0;
  for( size_t i = 0; i < n; i++ ) {
    if( push( a[i] ) ) [[likely]] {
      ret++;
    }
  }
  return ret;
}

template < typename T, size_t N >
template < typename Iter >
size_t RingBuffer< T, N >::push( Iter begin, Iter end ) noexcept {
  size_t ret = 0;
  for( ; begin != end; begin++ ) {
    if( push( *begin ) ) [[likely]] {
      ret++;
    }
  }
  return ret;
}

template < typename T, size_t N >
bool RingBuffer< T, N >::pop( T& value ) noexcept {
  size_t const tail = tail_;
  if( tail == head_ ) [[unlikely]] {
    return false;
  }
  value = buffer_[tail];
  size_t next_tail = tail + 1;
  if( next_tail == buffer_.size() ) [[unlikely]] {
    next_tail = 0;
  }
  tail_ = next_tail;
  return true;
}

template < typename T, size_t N >
size_t RingBuffer< T, N >::pop( T* a, size_t n ) noexcept {
  size_t ret = 0;
  for( size_t i = 0; i < n; i++ ) {
    if( pop( a[i] ) ) [[likely]] {
      ret++;
    }
  }
  return ret;
}

template < typename T, size_t N >
template < typename Iter >
size_t RingBuffer< T, N >::pop( Iter begin, Iter end ) noexcept {
  size_t ret = 0;
  for( ; begin != end; begin++ ) {
    if( pop( *begin ) ) [[likely]] {
      ret++;
    }
  }
  return ret;
}

template < typename T, size_t N >
size_t RingBuffer< T, N >::read_available() noexcept {
  size_t ret = 0;
  size_t i = tail_;
  while( i != head_ ) {
    ret++;
    i++;
    if( i >= N ) [[unlikely]] {
      i = 0;
    }
  }
  return ret;
}

}  // namespace SFG::SystemSimulator::AudioInterface
