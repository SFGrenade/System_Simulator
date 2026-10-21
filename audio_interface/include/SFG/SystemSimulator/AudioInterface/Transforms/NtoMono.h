#pragma once

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/Types/Node.h"

// Project Includes
#include <SFG/SystemSimulator/Logger/_spdlog.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

// C++ Includes
#include <memory>
#include <string>
#include <vector>

namespace SFG::SystemSimulator::AudioInterface::Transforms {

/*
  config is:
  {
    "amount": 2
  }
*/
class NtoMono : public Types::AudioTransformNode {
  public:
  virtual ~NtoMono() = default;
  virtual void init( std::map< std::string, std::any > const& config ) override;
  virtual void updateConfig( std::string const& option, std::any const& newValue ) override;
  virtual void update() override;
  virtual void deinit() override;

  private:
  // generic
  Logger::spdlogger logger_ = Logger::LoggerFactory::get_logger( "Transforms::NtoMono" );
  int64_t amount_ = 2;
};

}  // namespace SFG::SystemSimulator::AudioInterface::Transforms
