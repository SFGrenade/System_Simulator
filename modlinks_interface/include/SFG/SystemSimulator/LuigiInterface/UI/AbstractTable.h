#pragma once

// Project includes
#include <SFG/SystemSimulator/LuigiInterface/Models/AbstractModel.h>
#include <SFG/SystemSimulator/LuigiInterface/libui_all.h>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace UI {

class AbstractTable {
  public:
  explicit AbstractTable( Models::AbstractModel* model );
  virtual ~AbstractTable();

  uiTable* getUiTable() const;

  protected:
  virtual void onModelRowInserted( int index );
  virtual void onModelRowChanged( int index );
  virtual void onModelRowDeleted( int index );

  protected:
  uiTable* table_ = nullptr;
  Models::AbstractModel* model_ = nullptr;
};

}  // namespace UI
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
