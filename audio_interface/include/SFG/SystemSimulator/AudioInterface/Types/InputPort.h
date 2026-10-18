#pragma once

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/Types/OutputPort.h"

// C++ Includes
#include <memory>

namespace SFG::SystemSimulator::AudioInterface::Types {

template < class T >
class InputPort {
  public:
  virtual ~InputPort() = default;
  InputPort() = default;
  InputPort( InputPort< T > const& ) = default;
  InputPort( InputPort< T >&& ) = default;
  InputPort& operator=( InputPort< T > const& ) = default;
  InputPort& operator=( InputPort< T >&& ) = default;

  explicit InputPort( OutputPort< T > const& previous ) : data( previous.data ) {}
  InputPort& operator=( OutputPort< T > const& previous ) { data = previous.data; return *this; }

  operator bool() const noexcept { return !!data; }
  T& operator*() const noexcept { return *data.get(); }
  T* operator->() const noexcept { return data.get(); }

  private:
  std::shared_ptr< T > data = nullptr;
};

}  // namespace SFG::SystemSimulator::AudioInterface::Types
