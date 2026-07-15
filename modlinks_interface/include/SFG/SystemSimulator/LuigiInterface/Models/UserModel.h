#pragma once

// Project includes
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/LuigiInterface/libui_all.h>
#include <SFG/SystemSimulator/LuigiInterface/models/AbstractModel.h>

// C++ includes
#include <cstdint>
#include <string>
#include <vector>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace Models {

class UserModel : public AbstractModel {
  public:
  struct Data {
    uint64_t userId = 0;
    std::string userName = "";
    std::string userPasswordHash = "";
  };

  public:
  explicit UserModel();
  ~UserModel();

  public:
  AbstractModel::index_t columnCount() const override;
  uiTableValueType columnType( AbstractModel::index_t column ) const override;
  AbstractModel::index_t rowCount() const override;
  uiTableValue* getCell( AbstractModel::index_t row, AbstractModel::index_t column ) const override;

  void createUser( uint64_t userId, std::string const& userName, std::string const& userPasswordHash );
  UserModel::Data readUser( uint64_t userId );
  UserModel::Data readUserByIndex( int index );
  void updateUser( uint64_t userId, std::string const& newUserName, std::string const& newUserPasswordHash );
  void deleteUser( uint64_t userId );

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  std::vector< UserModel::Data > dataList_;
};

}  // namespace Models
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
