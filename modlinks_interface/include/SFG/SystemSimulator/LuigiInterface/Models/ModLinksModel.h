#pragma once

// Project includes
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/LuigiInterface/Models/AbstractModel.h>
#include <SFG/SystemSimulator/LuigiInterface/Models/ModLinksXmlModel.h>
#include <SFG/SystemSimulator/LuigiInterface/Types/Version.h>
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
  struct Data {
    std::string name = "";
    std::string displayName = "";
    std::string description = "";
    Types::Version version{};
    struct Links {
      struct Link {
        std::string sha = "";   // sha256
        std::string link = "";  // url
      } linux{}, mac{}, windows{};
    } links{};
    std::vector< std::string > dependencies{};
    std::string repository = "";  // URL
    std::string readme = "";      // URL
    std::string issues = "";      // URL
    std::vector< std::string > integrations{};
    std::vector< mm::Tag > tags{};
    std::vector< std::string > authors{};
  };

  public:
  explicit ModLinksModel();
  ~ModLinksModel();

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
