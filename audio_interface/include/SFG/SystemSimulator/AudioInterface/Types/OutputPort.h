#pragma once

// C++ Includes
#include <memory>

namespace SFG::SystemSimulator::AudioInterface::Types {

template < class T >
class InputPort;

template < class T >
class OutputPort {
  public:
  virtual ~OutputPort() = default;
  OutputPort() = default;
  OutputPort( OutputPort< T > const& ) = default;
  OutputPort( OutputPort< T >&& ) = default;
  OutputPort& operator=( OutputPort< T > const& ) = default;
  OutputPort& operator=( OutputPort< T >&& ) = default;

  T& operator*() const noexcept { return *data.get(); }
  T* operator->() const noexcept { return data.get(); }

  private:
  std::shared_ptr< T > data = std::make_shared< T >();

  friend class InputPort< T >;
};

}  // namespace SFG::SystemSimulator::AudioInterface::Types
