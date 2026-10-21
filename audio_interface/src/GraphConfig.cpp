// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/GraphConfig.h"

// Project Includes
#include "SFG/SystemSimulator/AudioInterface/Sinks/PortAudio.h"
#include "SFG/SystemSimulator/AudioInterface/Sources/PortAudio.h"
#include "SFG/SystemSimulator/AudioInterface/Transforms/MonoToN.h"
#include "SFG/SystemSimulator/AudioInterface/Transforms/NtoMono.h"

// Library Includes
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;

namespace SFG::SystemSimulator::AudioInterface {

GraphConfig::GraphConfig( std::string const& filepath ) {
  logger_->trace( fmt::runtime( "GraphConfig( filepath={:?} )" ), filepath );

  pt::ptree tree;
  pt::read_json( filepath, tree );

  pt::ptree nodesTree = tree.get_child( "nodes" );
  pt::ptree connectionsTree = tree.get_child( "connections" );

  for( auto& item : nodesTree ) {
    std::string nodeName = item.first;
    std::string nodeType = item.second.get< std::string >( "type" );
    pt::ptree nodeConfig = item.second.get_child( "config" );
    std::map< std::string, std::any > nodeConfigMap;
    logger_->trace( fmt::runtime( "GraphConfig - Node {:?}: {:?} with config:" ), nodeName, nodeType );
    for( auto& item : nodeConfig ) {
      std::string optionName = item.first;

      try {
        int64_t optionValueInt = item.second.get_value< int64_t >();
        logger_->trace( fmt::runtime( "              - {:?}: {:d}" ), item.first, optionValueInt );
        nodeConfigMap[optionName] = optionValueInt;
      } catch( pt::ptree_bad_data& e ) {
        try {
          double optionValueFloat = item.second.get_value< double >();
          logger_->trace( fmt::runtime( "              - {:?}: {:f}" ), item.first, optionValueFloat );
          nodeConfigMap[optionName] = optionValueFloat;
        } catch( pt::ptree_bad_data& e ) {
          try {
            std::string optionValueString = item.second.get_value< std::string >();
            logger_->trace( fmt::runtime( "              - {:?}: {:?}" ), item.first, optionValueString );
            nodeConfigMap[optionName] = optionValueString;
          } catch( pt::ptree_bad_data& e ) {
            logger_->error( fmt::runtime( "              - {:?}: ERROR: {:?}" ), item.first, e.what() );
          }
        }
      }
    }

    if( nodeType == "Sources::PortAudio" ) {
      std::shared_ptr< Types::Node > node = std::make_shared< Sources::PortAudio >();
      node->init( nodeConfigMap );
      sources_.push_back( node );
      nodeMap_[nodeName] = node;
    } else if( nodeType == "Transforms::MonoToN" ) {
      std::shared_ptr< Types::Node > node = std::make_shared< Transforms::MonoToN >();
      node->init( nodeConfigMap );
      transforms_.push_back( node );
      nodeMap_[nodeName] = node;
    } else if( nodeType == "Transforms::NtoMono" ) {
      std::shared_ptr< Types::Node > node = std::make_shared< Transforms::NtoMono >();
      node->init( nodeConfigMap );
      transforms_.push_back( node );
      nodeMap_[nodeName] = node;
    } else if( nodeType == "Sinks::PortAudio" ) {
      std::shared_ptr< Types::Node > node = std::make_shared< Sinks::PortAudio >();
      node->init( nodeConfigMap );
      sinks_.push_back( node );
      nodeMap_[nodeName] = node;
    }
  }

  for( auto& item : connectionsTree ) {
    std::string fromNode = item.second.get< std::string >( "from-node" );
    std::string fromPort = item.second.get< std::string >( "from-port" );
    int64_t fromChannel = item.second.get< int64_t >( "from-channel" );
    std::string toNode = item.second.get< std::string >( "to-node" );
    std::string toPort = item.second.get< std::string >( "to-port" );
    int64_t toChannel = item.second.get< int64_t >( "to-channel" );
    logger_->trace( fmt::runtime( "GraphConfig - {:?}/{:?}/{:d} => {:?}/{:?}/{:d}" ), fromNode, fromPort, fromChannel, toNode, toPort, toChannel );

    std::shared_ptr< Types::Node > fn = nodeMap_[fromNode];
    std::shared_ptr< Types::Node > tn = nodeMap_[toNode];

    std::shared_ptr< Types::AudioSourceNode > from_audioSourceNode = std::dynamic_pointer_cast< Types::AudioSourceNode >( fn );
    std::shared_ptr< Types::AudioTransformNode > from_audioTransformNode = std::dynamic_pointer_cast< Types::AudioTransformNode >( fn );
    std::shared_ptr< Types::AudioTransformNode > to_audioTransformNode = std::dynamic_pointer_cast< Types::AudioTransformNode >( tn );
    std::shared_ptr< Types::AudioSinkNode > to_audioSinkNode = std::dynamic_pointer_cast< Types::AudioSinkNode >( tn );

    if( from_audioSourceNode && to_audioTransformNode ) {
      to_audioTransformNode->inPorts[toPort][toChannel] = from_audioSourceNode->outPorts[fromPort][fromChannel];
    } else if( from_audioSourceNode && to_audioSinkNode ) {
      to_audioSinkNode->inPorts[toPort][toChannel] = from_audioSourceNode->outPorts[fromPort][fromChannel];
    } else if( from_audioTransformNode && to_audioTransformNode ) {
      to_audioTransformNode->inPorts[toPort][toChannel] = from_audioTransformNode->outPorts[fromPort][fromChannel];
    } else if( from_audioTransformNode && to_audioSinkNode ) {
      to_audioSinkNode->inPorts[toPort][toChannel] = from_audioTransformNode->outPorts[fromPort][fromChannel];
    }
  }
}

std::vector< std::shared_ptr< Types::Node > > GraphConfig::Sources() const {
  return sources_;
}

std::vector< std::shared_ptr< Types::Node > > GraphConfig::Transforms() const {
  return transforms_;
}

std::vector< std::shared_ptr< Types::Node > > GraphConfig::Sinks() const {
  return sinks_;
}

void GraphConfig::Clear() {
  for( auto& item : sources_ ) {
    item->deinit();
  }
  for( auto& item : transforms_ ) {
    item->deinit();
  }
  for( auto& item : sinks_ ) {
    item->deinit();
  }
  sources_.clear();
  transforms_.clear();
  sinks_.clear();
  nodeMap_.clear();
}

}  // namespace SFG::SystemSimulator::AudioInterface
