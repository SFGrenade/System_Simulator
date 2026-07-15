#include "SFG/SystemSimulator/LuigiInterface/Models/AbstractModel.h"

// Project includes
#include <SFG/SystemSimulator/Logger/scopedLogger.h>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace Models {

std::map< uiTableModel*, AbstractModel* > AbstractModel::uiToAbstract_;

AbstractModel::AbstractModel() : logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "AbstractModel" ) ) {
  this->logger_->trace( fmt::runtime( "AbstractModel()" ) );

  uiHandler_.NumColumns = s_columnCount;
  uiHandler_.ColumnType = s_columnType;
  uiHandler_.NumRows = s_rowCount;
  uiHandler_.CellValue = s_getCell;
  uiHandler_.SetCellValue = s_setCell;

  uiModel_ = uiNewTableModel( &uiHandler_ );

  this->logger_->trace( fmt::runtime( "AbstractModel()~" ) );
}

AbstractModel::~AbstractModel() {
  this->logger_->trace( fmt::runtime( "~AbstractModel()" ) );

  AbstractModel::uiToAbstract_.erase( uiModel_ );
  uiFreeTableModel( uiModel_ );

  this->logger_->trace( fmt::runtime( "~AbstractModel()~" ) );
}

AbstractModel::index_t AbstractModel::columnCount() const {
  return 0;
}

uiTableValueType AbstractModel::columnType( AbstractModel::index_t ) const {
  return uiTableValueTypeString;
}

AbstractModel::index_t AbstractModel::rowCount() const {
  return 0;
}

uiTableValue* AbstractModel::getCell( AbstractModel::index_t, AbstractModel::index_t ) const {
  // uiNewTableValue*
  return nullptr;
}

void AbstractModel::setCell( AbstractModel::index_t, AbstractModel::index_t, uiTableValue const* ) {}

uiTableModel* AbstractModel::getUiModel() const {
  return uiModel_;
}

AbstractModel::index_t AbstractModel::s_columnCount( uiTableModelHandler*, uiTableModel* uiModel ) {
  auto iter = uiToAbstract_.find( uiModel );
  if( iter != uiToAbstract_.end() ) {
    return iter->second->columnCount();
  }
  return 0;
}

uiTableValueType AbstractModel::s_columnType( uiTableModelHandler*, uiTableModel* uiModel, AbstractModel::index_t column ) {
  auto iter = uiToAbstract_.find( uiModel );
  if( iter != uiToAbstract_.end() ) {
    return iter->second->columnType( column );
  }
  return {};
}

AbstractModel::index_t AbstractModel::s_rowCount( uiTableModelHandler*, uiTableModel* uiModel ) {
  auto iter = uiToAbstract_.find( uiModel );
  if( iter != uiToAbstract_.end() ) {
    return iter->second->rowCount();
  }
  return 0;
}

uiTableValue* AbstractModel::s_getCell( uiTableModelHandler*, uiTableModel* uiModel, AbstractModel::index_t row, AbstractModel::index_t column ) {
  auto iter = uiToAbstract_.find( uiModel );
  if( iter != uiToAbstract_.end() ) {
    return iter->second->getCell( row, column );
  }
  return nullptr;
}

void AbstractModel::s_setCell( uiTableModelHandler*, uiTableModel* uiModel, AbstractModel::index_t row, AbstractModel::index_t column, uiTableValue const* value ) {
  auto iter = uiToAbstract_.find( uiModel );
  if( iter != uiToAbstract_.end() ) {
    return iter->second->setCell( row, column, value );
  }
}

}  // namespace Models
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
