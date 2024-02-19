#include "mainWindow.h"

#include <networkMessages.pb.h>

#include "loggerFactory.h"

namespace SFG {
namespace SystemSimulator {
namespace ConfigHmi {

MainWindow::MainWindow( QWidget *parent ) : QMainWindow( parent ), logger_( LoggerFactory::get_logger( "MainWindow" ) ) {
  logger_->trace( fmt::runtime( "MainWindow( parent: {:p} )" ), static_cast< void * >( parent ) );

  _MenuBar = new QMenuBar( this );
  _Widget = new QWidget( this );
  _StatusBar = new QStatusBar( this );
  _VBoxLayout = new QVBoxLayout( _Widget );
  _PushButton = new QPushButton( "Push me", _Widget );

  _Widget->setLayout( _VBoxLayout );
  _VBoxLayout->addWidget( _PushButton, 1, Qt::AlignmentFlag::AlignCenter );

  setMenuBar( _MenuBar );
  setCentralWidget( _Widget );
  setStatusBar( _StatusBar );

  connect( _PushButton, &QPushButton::clicked, this, &MainWindow::buttonClicked );

  logger_->trace( fmt::runtime( "MainWindow()~" ) );
}

MainWindow::~MainWindow() {
  logger_->trace( fmt::runtime( "~MainWindow()" ) );
  logger_->trace( fmt::runtime( "~MainWindow()~" ) );
}

void MainWindow::buttonClicked() {
  logger_->trace( fmt::runtime( "buttonClicked()" ) );

  SFG::SystemSimulator::Proto::MsgContent myMessage;
  myMessage.set_username( "set_username" );
  myMessage.set_msgtext( "set_msgtext" );
  logger_->trace( fmt::runtime( "buttonClicked - myMessage.username: '{:s}'" ), myMessage.username() );
  logger_->trace( fmt::runtime( "buttonClicked - myMessage.msgtext: '{:s}'" ), myMessage.msgtext() );
  logger_->trace( fmt::runtime( "buttonClicked - myMessage.SerializeAsString: '{:s}'" ), myMessage.SerializeAsString() );

  logger_->trace( fmt::runtime( "buttonClicked()~" ) );
}

}  // namespace ConfigHmi
}  // namespace SystemSimulator
}  // namespace SFG
