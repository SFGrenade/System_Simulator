#include "SFG/SystemSimulator/SettingsInterface/mainWindow.h"

#include <SFG/SystemSimulator/Logger-Qt/qtFormatter.h>
#include <SFG/SystemSimulator/NetworkMessages/Database.pb.h>

namespace SSSNM = SFG::SystemSimulator::NetworkMessages;

namespace SFG {
namespace SystemSimulator {
namespace SettingsInterface {

MainWindow::MainWindow( QWidget *parent ) : QMainWindow( parent ), logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "MainWindow" ) ) {
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

  SSSNM::MsgContent myMessage;
  myMessage.set_username( "username" );
  myMessage.set_msg_text( "msgText" );
  logger_->trace( fmt::runtime( "buttonClicked - myMessage.username: '{:s}'" ), myMessage.username() );
  logger_->trace( fmt::runtime( "buttonClicked - myMessage.msg_text: '{:s}'" ), myMessage.msg_text() );

  logger_->trace( fmt::runtime( "buttonClicked()~" ) );
}

}  // namespace SettingsInterface
}  // namespace SystemSimulator
}  // namespace SFG
