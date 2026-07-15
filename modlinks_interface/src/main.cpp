
// Project includes
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/LuigiInterface/MainWindow.h>
#include <SFG/SystemSimulator/LuigiInterface/libui_all.h>

// C++ includes
#include <string>
#include <vector>

int onCloseMainWindow( uiWindow* /*w*/, void* /*data*/ ) {
  uiQuit();
  return 1;
}

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "LuigiInterfaceLog.log" );
  std::vector< std::string > args;
  args.reserve( argc );
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  int retCode = 0;

  if( !retCode ) {
    uiInitOptions initOptions{ .Size = 0 };

    if( char const* tmp = uiInit( &initOptions ); tmp != nullptr ) {
      spdlog::error( fmt::runtime( "main - {:s}" ), tmp );
      return 1;
    }

    SFG::SystemSimulator::LuigiInterface::MainWindow mainWindow;

    uiWindowOnClosing( mainWindow.getUiWindow(), onCloseMainWindow, nullptr );
    uiControlShow( uiControl( mainWindow.getUiWindow() ) );

    uiMain();
  }

  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return retCode;
}
