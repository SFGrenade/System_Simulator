#include "SFG/SystemSimulator/LuigiInterface/UI/AbstractTable.h"

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace UI {

AbstractTable::AbstractTable( Models::AbstractModel* model ) {
  model_ = model;

  uiTableParams tableParams;
  tableParams.Model = model_->getUiModel();
  tableParams.RowBackgroundColorModelColumn = -1;
  table_ = uiNewTable( &tableParams );
}

AbstractTable::~AbstractTable() {}

uiTable* AbstractTable::getUiTable() const {
  return table_;
}

void AbstractTable::onModelRowInserted( int index ) {
  uiTableModelRowInserted( model_->getUiModel(), index );
}

void AbstractTable::onModelRowChanged( int index ) {
  uiTableModelRowChanged( model_->getUiModel(), index );
}

void AbstractTable::onModelRowDeleted( int index ) {
  uiTableModelRowDeleted( model_->getUiModel(), index );
}

}  // namespace UI
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
