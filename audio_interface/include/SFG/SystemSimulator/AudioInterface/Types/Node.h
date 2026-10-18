#pragma once

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/Types/AudioMessage.h"
#include "SFG/SystemSimulator/AudioInterface/Types/InputPort.h"
#include "SFG/SystemSimulator/AudioInterface/Types/OutputPort.h"

// C++ Includes
#include <any>
#include <map>
#include <string>

namespace SFG::SystemSimulator::AudioInterface::Types {

class Node {
  public:
  virtual ~Node() = default;
  virtual void init( std::map< std::string, std::any > const& config ) = 0;
  virtual void updateConfig( std::string const& option, std::any const& newValue ) = 0;
  virtual bool update() = 0;
  virtual void deinit() = 0;
};

class AudioSourceNode : public Node {
  public:
  virtual ~AudioSourceNode() = default;

  public:
  std::map< std::string, std::vector< Types::OutputPort< Types::AudioMessage > > > outPorts;
};

class AudioTransformNode : public Node {
  public:
  virtual ~AudioTransformNode() = default;

  public:
  std::map< std::string, std::vector< Types::InputPort< Types::AudioMessage > > > inPorts;
  std::map< std::string, std::vector< Types::OutputPort< Types::AudioMessage > > > outPorts;
};

class AudioSinkNode : public Node {
  public:
  virtual ~AudioSinkNode() = default;

  public:
  std::map< std::string, std::vector< Types::InputPort< Types::AudioMessage > > > inPorts;
};

}  // namespace SFG::SystemSimulator::AudioInterface::Types
