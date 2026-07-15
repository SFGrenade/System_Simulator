#pragma once

// Project includes
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/LuigiInterface/libui_all.h>

// C++ includes
#include <map>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace Models {

class AbstractModel {
  public:
  typedef int index_t;

  public:
  explicit AbstractModel();
  virtual ~AbstractModel();

  virtual AbstractModel::index_t columnCount() const;
  virtual uiTableValueType columnType( AbstractModel::index_t column ) const;
  virtual AbstractModel::index_t rowCount() const;
  virtual uiTableValue* getCell( AbstractModel::index_t row, AbstractModel::index_t column ) const;
  virtual void setCell( AbstractModel::index_t row, AbstractModel::index_t column, uiTableValue const* value );

  uiTableModel* getUiModel() const;

  protected:
  static AbstractModel::index_t s_columnCount( uiTableModelHandler* uiHandler, uiTableModel* uiModel );
  static uiTableValueType s_columnType( uiTableModelHandler* uiHandler, uiTableModel* uiModel, AbstractModel::index_t column );
  static AbstractModel::index_t s_rowCount( uiTableModelHandler* uiHandler, uiTableModel* uiModel );
  static uiTableValue* s_getCell( uiTableModelHandler* uiHandler, uiTableModel* uiModel, AbstractModel::index_t row, AbstractModel::index_t column );
  static void s_setCell( uiTableModelHandler* uiHandler, uiTableModel* uiModel, AbstractModel::index_t row, AbstractModel::index_t column, uiTableValue const* value );

  protected:
  static std::map< uiTableModel*, AbstractModel* > uiToAbstract_;
  uiTableModelHandler uiHandler_;
  uiTableModel* uiModel_ = nullptr;

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
};

}  // namespace Models
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
