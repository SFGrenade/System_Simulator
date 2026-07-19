#pragma once

// Project includes
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/LuigiInterface/Models/AbstractModel.h>
#include <SFG/SystemSimulator/LuigiInterface/Types/ModManifest.h>
#include <SFG/SystemSimulator/LuigiInterface/libui_all.h>

// C++ includes
#include <string>
#include <vector>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace Models {

class ModLinksModel : public AbstractModel {
  static std::string const SERVER_ADDRESS;
  static std::string const SERVER_PATH;

  public:
  using Data = Types::ModManifest;

  public:
  explicit ModLinksModel();
  ~ModLinksModel();

  std::set< ModLinksModel::Data > getModAndDeps( std::string const& modName ) const;
  std::set< ModLinksModel::Data > getModAndDeps( ModLinksModel::Data const& mod ) const;

  public:
  AbstractModel::index_t columnCount() const override;
  uiTableValueType columnType( AbstractModel::index_t column ) const override;
  AbstractModel::index_t rowCount() const override;
  uiTableValue* getCell( AbstractModel::index_t row, AbstractModel::index_t column ) const override;

  void setupFromOnline();
  void setupFromCache();

  private:
  void integrateNewList( std::vector< mm::Manifest >& manifestList );

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  std::vector< ModLinksModel::Data > dataList_;
};

}  // namespace Models
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG

SFG::SystemSimulator::LuigiInterface::Models::ModLinksModel::Data fromXml( mm::Manifest const& manifest );
bool isDifferent( SFG::SystemSimulator::LuigiInterface::Models::ModLinksModel::Data const& a, mm::Manifest const& b );
