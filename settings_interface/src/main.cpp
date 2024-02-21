#include <QApplication>
#include <string>
#include <vector>

#include "loggerFactory.h"
#include "mainWindow.h"

int main( int argc, char** argv ) {
  SFG::SystemSimulator::ConfigHmi::LoggerFactory::init();
  std::vector< std::string > args;
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  QApplication a( argc, argv );
  SFG::SystemSimulator::ConfigHmi::MainWindow w;
  w.show();
  int retCode = a.exec();

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::ConfigHmi::LoggerFactory::deinit();
  return retCode;
}
