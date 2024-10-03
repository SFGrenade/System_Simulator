#include "SFG/SystemSimulator/SettingsInterface/mainWindow.h"

#include <QHeaderView>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QTableView>
#include <QVBoxLayout>
#include <SFG/SystemSimulator/Logger-Qt/qtFormatter.h>
#include <SFG/SystemSimulator/Logger/scopedLogger.h>
#include <SFG/SystemSimulator/NetworkMessages/Database.pb.h>

#include "SFG/SystemSimulator/SettingsInterface/models/listToTableModel.h"
#include "SFG/SystemSimulator/SettingsInterface/models/userModel.h"

namespace SSSNM = SFG::SystemSimulator::NetworkMessages;

namespace SFG {
namespace SystemSimulator {
namespace SettingsInterface {

MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent ), logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "MainWindow" ) ) {
  logger_->trace( fmt::runtime( "MainWindow( parent: {:p} )" ), static_cast< void* >( parent ) );

  QMenuBar* menuBar = new QMenuBar( this );
  QWidget* widget = new QWidget( this );
  QStatusBar* statusBar = new QStatusBar( this );
  QVBoxLayout* vBoxLayout = new QVBoxLayout( widget );
  QPushButton* pushButton = new QPushButton( "Push me", widget );
  QTableView* tableView = new QTableView( widget );
  ListToTableModel* listToTableModel = new ListToTableModel( tableView );
  UserModel* userModel = new UserModel( listToTableModel );

  widget->setLayout( vBoxLayout );

  vBoxLayout->addWidget( pushButton, 0, Qt::AlignmentFlag::AlignCenter );
  vBoxLayout->addWidget( tableView, 1 );

  tableView->setModel( listToTableModel );

  listToTableModel->setSourceModel( userModel );

  userModel->insertRow( 0 );
  userModel->setData( userModel->index( 0 ), QVariant::fromValue< uint64_t >( 1ull ), static_cast< int >( UserModel::Roles::UserId ) );
  userModel->setData( userModel->index( 0 ), QString( "First Entry" ), static_cast< int >( UserModel::Roles::UserName ) );
  userModel->setData( userModel->index( 0 ), QString( "whatever tbh" ), static_cast< int >( UserModel::Roles::UserPasswordHash ) );

  setMenuBar( menuBar );
  setCentralWidget( widget );
  setStatusBar( statusBar );

  connect( pushButton, &QPushButton::clicked, this, &MainWindow::buttonClicked );

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
