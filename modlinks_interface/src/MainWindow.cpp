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

  installButton_ = uiNewButton( "Install" );
  uiButtonOnClicked( installButton_, []( uiButton*, void* ctx ) { reinterpret_cast< MainWindow* >( ctx )->installButtonClicked(); }, this );
  uiBoxAppend( buttonPanel_, uiControl( installButton_ ), FALSE );

  disableButton_ = uiNewButton( "Disable" );
  uiButtonOnClicked( disableButton_, []( uiButton*, void* ctx ) { reinterpret_cast< MainWindow* >( ctx )->disableButtonClicked(); }, this );
  uiBoxAppend( buttonPanel_, uiControl( disableButton_ ), FALSE );

  enableButton_ = uiNewButton( "Enable" );
  uiButtonOnClicked( enableButton_, []( uiButton*, void* ctx ) { reinterpret_cast< MainWindow* >( ctx )->enableButtonClicked(); }, this );
  uiBoxAppend( buttonPanel_, uiControl( enableButton_ ), FALSE );

  uninstallButton_ = uiNewButton( "Uninstall" );
  uiButtonOnClicked( uninstallButton_, []( uiButton*, void* ctx ) { reinterpret_cast< MainWindow* >( ctx )->uninstallButtonClicked(); }, this );
  uiBoxAppend( buttonPanel_, uiControl( uninstallButton_ ), FALSE );

  updateButton_ = uiNewButton( "Update" );
  uiButtonOnClicked( updateButton_, []( uiButton*, void* ctx ) { reinterpret_cast< MainWindow* >( ctx )->updateButtonClicked(); }, this );
  uiBoxAppend( buttonPanel_, uiControl( updateButton_ ), FALSE );

  table_ = new UI::AbstractTable( &model_ );
  uiBoxAppend( mainPanel_, uiControl( table_->getUiTable() ), TRUE );

  uiTableAppendTextColumn( table_->getUiTable(), "Name", 1, uiTableModelColumnNeverEditable, nullptr );
  uiTableAppendTextColumn( table_->getUiTable(), "Description", 2, uiTableModelColumnNeverEditable, nullptr );
  uiTableAppendTextColumn( table_->getUiTable(), "Version", 3, uiTableModelColumnNeverEditable, nullptr );
  uiTableAppendTextColumn( table_->getUiTable(), "Tags", 11, uiTableModelColumnNeverEditable, nullptr );
  uiTableAppendTextColumn( table_->getUiTable(), "Authors", 12, uiTableModelColumnNeverEditable, nullptr );

  uiTableHeaderSetSortIndicator( table_->getUiTable(), 0, uiSortIndicatorAscending );
  uiTableHeaderSetSortIndicator( table_->getUiTable(), 1, uiSortIndicatorNone );
  uiTableHeaderSetSortIndicator( table_->getUiTable(), 2, uiSortIndicatorNone );
  uiTableHeaderSetSortIndicator( table_->getUiTable(), 3, uiSortIndicatorNone );
  uiTableHeaderSetSortIndicator( table_->getUiTable(), 4, uiSortIndicatorNone );
  uiTableSetSelectionMode( table_->getUiTable(), uiTableSelectionModeZeroOrMany );

  model_.setupFromOnline();

  logger_->trace( fmt::runtime( "MainWindow()~" ) );
}

MainWindow::~MainWindow() {
  logger_->trace( fmt::runtime( "~MainWindow()" ) );

  if( table_ ) {
    delete table_;
    table_ = nullptr;
  }

  logger_->trace( fmt::runtime( "~MainWindow()~" ) );
}

uiWindow* MainWindow::getUiWindow() const {
  return window_;
}

void MainWindow::installButtonClicked() {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "installButtonClicked()" ) ),
                                                      fmt::format( fmt::runtime( "installButtonClicked()~" ) ) );

  uiTableSelection* selection = uiTableGetSelection( table_->getUiTable() );
  std::vector< int > selectedRows;
  if( selection->NumRows > 0 ) {
    selectedRows.insert( selectedRows.begin(), selection->Rows, selection->Rows + selection->NumRows );
  }
  uiFreeTableSelection( selection );

  for( int selectedRow : selectedRows ) {
    uiTableValue* cellValue = model_.getCell( selectedRow, 0 );
    std::string selectedRowName = uiTableValueString( cellValue );
    uiFreeTableValue( cellValue );
    std::set< Models::ModLinksModel::Data > modsToInstall = model_.getModAndDeps( selectedRowName );
    logger_->debug( fmt::runtime( "installButtonClicked - Mods to install (from {:?}):" ), selectedRowName );
    for( auto const& item : modsToInstall ) {
      logger_->debug( fmt::runtime( "installButtonClicked -   - {:?}" ), item.name );
    }
  }

  // static size_t counter = size_t( 3 );
  // size_t userIdToUse = size_t( 1 ) << counter;
  // self->model_.createUser( userIdToUse, fmt::format( fmt::runtime( "User {:d}" ), userIdToUse ), fmt::format( fmt::runtime( "Password {:d}" ), userIdToUse )
  // ); counter++;
}

void MainWindow::disableButtonClicked() {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "disableButtonClicked()" ) ),
                                                      fmt::format( fmt::runtime( "disableButtonClicked()~" ) ) );

  // static size_t counter = size_t( 3 );
  // size_t userIdToUse = size_t( 1 ) << counter;
  // self->model_.createUser( userIdToUse, fmt::format( fmt::runtime( "User {:d}" ), userIdToUse ), fmt::format( fmt::runtime( "Password {:d}" ), userIdToUse )
  // ); counter++;
}

void MainWindow::enableButtonClicked() {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "enableButtonClicked()" ) ),
                                                      fmt::format( fmt::runtime( "enableButtonClicked()~" ) ) );

  // static size_t counter = size_t( 3 );
  // size_t userIdToUse = size_t( 1 ) << counter;
  // self->model_.createUser( userIdToUse, fmt::format( fmt::runtime( "User {:d}" ), userIdToUse ), fmt::format( fmt::runtime( "Password {:d}" ), userIdToUse )
  // ); counter++;
}

void MainWindow::uninstallButtonClicked() {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "uninstallButtonClicked()" ) ),
                                                      fmt::format( fmt::runtime( "uninstallButtonClicked()~" ) ) );

  // static size_t counter = size_t( 3 );
  // size_t userIdToUse = size_t( 1 ) << counter;
  // self->model_.createUser( userIdToUse, fmt::format( fmt::runtime( "User {:d}" ), userIdToUse ), fmt::format( fmt::runtime( "Password {:d}" ), userIdToUse )
  // ); counter++;
}

void MainWindow::updateButtonClicked() {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "updateButtonClicked()" ) ),
                                                      fmt::format( fmt::runtime( "updateButtonClicked()~" ) ) );

  // static size_t counter = size_t( 3 );
  // size_t userIdToUse = size_t( 1 ) << counter;
  // self->model_.createUser( userIdToUse, fmt::format( fmt::runtime( "User {:d}" ), userIdToUse ), fmt::format( fmt::runtime( "Password {:d}" ), userIdToUse )
  // ); counter++;
}

}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
