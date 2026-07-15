#pragma once

// Project includes
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/LuigiInterface/libui_all.h>
#include <SFG/SystemSimulator/LuigiInterface/models/AbstractModel.h>

// C++ includes
#include <cstdint>
#include <filesystem>
#include <vector>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace Models {

class FolderModel : public AbstractModel {
  public:
  struct Data {
    std::filesystem::path path;
    std::filesystem::file_status status;
    uintmax_t size;
  };

  public:
  explicit FolderModel();
  ~FolderModel();

  public:
  AbstractModel::index_t columnCount() const override;
  uiTableValueType columnType( AbstractModel::index_t column ) const override;
  AbstractModel::index_t rowCount() const override;
  uiTableValue* getCell( AbstractModel::index_t row, AbstractModel::index_t column ) const override;

  void setRootFolder( std::filesystem::path const& root );
  void refresh();

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  std::filesystem::path root_;
  std::vector< FolderModel::Data > dataList_;
};

}  // namespace Models
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
