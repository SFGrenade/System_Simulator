#include <QApplication>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <string>
#include <vector>

#include "SFG/SystemSimulator/SettingsInterface/mainWindow.h"

void MyQtMessageHandler( QtMsgType type, QMessageLogContext const& context, QString const& msg ) {
  SFG::SystemSimulator::Logger::spdlogger qtLogger = SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "Qt" );

  QByteArray localMsg = msg.toLocal8Bit();
  const char* contextFile = context.file ? context.file : "";
  const char* contextFunction = context.function ? context.function : "";

  std::string debugFileInfo = fmt::format( fmt::runtime( "{:s}:{:d}, {:s}" ), contextFile, context.line, contextFunction );
  switch( type ) {
    case QtDebugMsg:
      qtLogger->debug( fmt::runtime( "{:s} ({:s})" ), localMsg.constData(), debugFileInfo );
      break;
    case QtInfoMsg:
      qtLogger->info( fmt::runtime( "{:s} ({:s})" ), localMsg.constData(), debugFileInfo );
      break;
    case QtWarningMsg:
      qtLogger->warn( fmt::runtime( "{:s} ({:s})" ), localMsg.constData(), debugFileInfo );
      break;
    case QtCriticalMsg:
      qtLogger->critical( fmt::runtime( "{:s} ({:s})" ), localMsg.constData(), debugFileInfo );
      break;
    case QtFatalMsg:
      qtLogger->critical( fmt::runtime( "{:s} ({:s})" ), localMsg.constData(), debugFileInfo );
      break;
  }
}

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "SettingsInterfaceLog.log" );
  std::vector< std::string > args;
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  qInstallMessageHandler( MyQtMessageHandler );

  QApplication a( argc, argv );
  SFG::SystemSimulator::SettingsInterface::MainWindow w;
  w.show();
  int retCode = a.exec();

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return retCode;
}
