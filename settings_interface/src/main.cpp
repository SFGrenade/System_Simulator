#include <QApplication>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <string>
#include <vector>

#include "SFG/SystemSimulator/SettingsInterface/mainWindow.h"

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "SettingsInterfaceLog.log" );
  std::vector< std::string > args;
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  QApplication a( argc, argv );
  SFG::SystemSimulator::SettingsInterface::MainWindow w;
  w.show();
  int retCode = a.exec();

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return retCode;
}
