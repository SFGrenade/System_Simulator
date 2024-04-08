#include <QAbstractItemModelTester>
#include <SFG/SystemSimulator/Logger-Qt/qtFormatter.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/SettingsInterface/models/userModel.h>
#include <string>
#include <vector>

void MyQtMessageHandler( QtMsgType type, QMessageLogContext const& context, QString const& msg ) {
  SFG::SystemSimulator::Logger::spdlogger qtLogger = SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "Qt" );

  const char* contextFile = context.file ? context.file : "";
  const char* contextFunction = context.function ? context.function : "";

  std::string debugFileInfo = fmt::format( fmt::runtime( "{:s}:{:d}, {:s}" ), contextFile, context.line, contextFunction );
  switch( type ) {
    case QtDebugMsg:
      qtLogger->debug( fmt::runtime( "{:qs} ({:s})" ), msg, debugFileInfo );
      break;
    case QtInfoMsg:
      qtLogger->info( fmt::runtime( "{:qs} ({:s})" ), msg, debugFileInfo );
      break;
    case QtWarningMsg:
      qtLogger->warn( fmt::runtime( "{:qs} ({:s})" ), msg, debugFileInfo );
      break;
    case QtCriticalMsg:
      qtLogger->critical( fmt::runtime( "{:qs} ({:s})" ), msg, debugFileInfo );
      break;
    case QtFatalMsg:
      qtLogger->critical( fmt::runtime( "{:qs} ({:s})" ), msg, debugFileInfo );
      break;
  }
}

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "testLogs/settingsInterfaceTest.log", false );
  std::vector< std::string > args;
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  qInstallMessageHandler( MyQtMessageHandler );

  spdlog::trace( fmt::runtime( "Running QAbstractItemModelTester on UserModel" ) );
  SFG::SystemSimulator::SettingsInterface::UserModel* userModel = new SFG::SystemSimulator::SettingsInterface::UserModel();
  QAbstractItemModelTester* modelTester_UserModel = new QAbstractItemModelTester( userModel, QAbstractItemModelTester::FailureReportingMode::Fatal );

  userModel->insertRow( 0 );
  userModel->setData( userModel->index( 0 ), 1ULL, static_cast< int >( SFG::SystemSimulator::SettingsInterface::UserModel::Roles::UserId ) );
  userModel->setData( userModel->index( 0 ), QString( "Username" ), static_cast< int >( SFG::SystemSimulator::SettingsInterface::UserModel::Roles::UserName ) );
  userModel->setData( userModel->index( 0 ),
                      QString( "Password" ),
                      static_cast< int >( SFG::SystemSimulator::SettingsInterface::UserModel::Roles::UserPasswordHash ) );

  delete modelTester_UserModel;
  delete userModel;

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return 0;
}
