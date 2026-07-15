#include "SFG/SystemSimulator/LuigiInterface/MainWindow.h"

// Project includes
#include <SFG/SystemSimulator/Logger/scopedLogger.h>
#include <SFG/SystemSimulator/NetworkMessages/Database.pb.h>

namespace SSSNM = SFG::SystemSimulator::NetworkMessages;

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {

MainWindow::MainWindow() : logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "MainWindow" ) ) {
  logger_->trace( fmt::runtime( "MainWindow()" ) );

  window_ = uiNewWindow( "MainWindow", 640, 480, FALSE );
  uiWindowSetMargined( window_, TRUE );
  mainPanel_ = uiNewVerticalBox();
  uiBoxSetPadded( mainPanel_, TRUE );
  uiWindowSetChild( window_, uiControl( mainPanel_ ) );
  buttonPanel_ = uiNewHorizontalBox();
  uiBoxSetPadded( buttonPanel_, TRUE );
  uiBoxAppend( mainPanel_, uiControl( buttonPanel_ ), FALSE );

  addButton_ = uiNewButton( "Add new User" );
  uiButtonOnClicked( addButton_, MainWindow::addButtonClicked, this );
  uiBoxAppend( buttonPanel_, uiControl( addButton_ ), FALSE );
  deleteButton_ = uiNewButton( "Delete User" );
  uiButtonOnClicked( deleteButton_, MainWindow::deleteButtonClicked, this );
  uiBoxAppend( buttonPanel_, uiControl( deleteButton_ ), FALSE );
  table_ = new UI::AbstractTable( &model_ );
  uiBoxAppend( mainPanel_, uiControl( table_->getUiTable() ), TRUE );

  uiTableAppendTextColumn( table_->getUiTable(), "Name", 0, uiTableModelColumnNeverEditable, nullptr );
  uiTableAppendTextColumn( table_->getUiTable(), "Description", 1, uiTableModelColumnNeverEditable, nullptr );
  uiTableAppendTextColumn( table_->getUiTable(), "Version", 2, uiTableModelColumnNeverEditable, nullptr );
  uiTableAppendTextColumn( table_->getUiTable(), "Dependencies", 3, uiTableModelColumnNeverEditable, nullptr );
  uiTableAppendTextColumn( table_->getUiTable(), "Integrations", 4, uiTableModelColumnNeverEditable, nullptr );
  uiTableAppendTextColumn( table_->getUiTable(), "Tags", 5, uiTableModelColumnNeverEditable, nullptr );
  uiTableAppendTextColumn( table_->getUiTable(), "Authors", 6, uiTableModelColumnNeverEditable, nullptr );

  // model_.setRootFolder( "C:/Users/SFG/Downloads/" );
  model_.setupFromOnline();
  // model_.createUser( 1, "Admin", "1337" );
  // model_.createUser( 2, "Fantastic User", "1337" );
  // model_.createUser( 3, "Some Guy", "1337" );

  logger_->trace( fmt::runtime( "MainWindow()~" ) );
}

MainWindow::~MainWindow() {
  logger_->trace( fmt::runtime( "~MainWindow()" ) );

  if( table_ )
    delete table_;

  logger_->trace( fmt::runtime( "~MainWindow()~" ) );
}

uiWindow* MainWindow::getUiWindow() const {
  return window_;
}

void MainWindow::addButtonClicked( uiButton* /*button*/, void* /*context*/ ) {
  // MainWindow* self = reinterpret_cast< MainWindow* >( context );

  // static size_t counter = size_t( 3 );
  // size_t userIdToUse = size_t( 1 ) << counter;
  // self->model_.createUser( userIdToUse, fmt::format( fmt::runtime( "User {:d}" ), userIdToUse ), fmt::format( fmt::runtime( "Password {:d}" ), userIdToUse )
  // ); counter++;
}

void MainWindow::deleteButtonClicked( uiButton* /*button*/, void* /*context*/ ) {
  // MainWindow* self = reinterpret_cast< MainWindow* >( context );

  // int selectedIndex = self->model_.selectedIndex();
  // if( ( 0 <= selectedIndex ) && ( selectedIndex < self->model_.rowCount() ) ) {
  //   Models::UserModel::Data userToDelete = self->model_.readUserByIndex( selectedIndex );
  //   uint64_t userIdToDelete = userToDelete.userId;
  //   self->model_.deleteUser( userIdToDelete );
  // }
}

}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
