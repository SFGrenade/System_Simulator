#pragma once

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/Types/Node.h"

// Project Includes
#include <SFG/SystemSimulator/Logger/_spdlog.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

// C++ Includes
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace SFG::SystemSimulator::AudioInterface {

class GraphConfig {
  public:
  explicit GraphConfig( std::string const& filepath );

  std::vector< std::shared_ptr< Types::Node > > Sources() const;
  std::vector< std::shared_ptr< Types::Node > > Transforms() const;
  std::vector< std::shared_ptr< Types::Node > > Sinks() const;

  void Clear();

  private:
  // generic
  Logger::spdlogger logger_ = Logger::LoggerFactory::get_logger( "GraphConfig" );
  std::vector< std::shared_ptr< Types::Node > > sources_;
  std::vector< std::shared_ptr< Types::Node > > transforms_;
  std::vector< std::shared_ptr< Types::Node > > sinks_;
  std::map< std::string, std::shared_ptr< Types::Node > > nodeMap_;
};

}  // namespace SFG::SystemSimulator::AudioInterface
