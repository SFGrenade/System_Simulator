#include "SFG/SystemSimulator/LuigiInterface/Models/UserModel.h"

// Project includes
#include <SFG/SystemSimulator/Logger/scopedLogger.h>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {
namespace Models {

UserModel::UserModel() : logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "UserModel" ) ) {
  this->logger_->trace( fmt::runtime( "UserModel()" ) );

  uiToAbstract_.insert( { uiModel_, this } );

  this->logger_->trace( fmt::runtime( "UserModel()~" ) );
}

UserModel::~UserModel() {
  this->logger_->trace( fmt::runtime( "~UserModel()" ) );

  this->logger_->trace( fmt::runtime( "~UserModel()~" ) );
}

AbstractModel::index_t UserModel::columnCount() const {
  return 3;
}

uiTableValueType UserModel::columnType( AbstractModel::index_t column ) const {
  switch( column ) {
    case 0:
      // ID
      return uiTableValueTypeInt;
    case 1:
      // Name
      return uiTableValueTypeString;
    case 2:
      // Password Hash
      return uiTableValueTypeString;
    default:
      return uiTableValueTypeString;
  }
}

AbstractModel::index_t UserModel::rowCount() const {
  return dataList_.size();
}

uiTableValue* UserModel::getCell( AbstractModel::index_t row, AbstractModel::index_t column ) const {
  if( ( 0 <= row ) && ( row < rowCount() ) ) {
    UserModel::Data const& item = dataList_[row];
    if( ( column < 0 ) || ( columnCount() <= column ) ) {
      return nullptr;
    }
    if( column == 0 ) {
      return uiNewTableValueInt( item.userId );
    } else if( column == 1 ) {
      return uiNewTableValueString( item.userName.c_str() );
    } else {
      return uiNewTableValueString( item.userPasswordHash.c_str() );
    }
  }
  return nullptr;
}

void UserModel::createUser( uint64_t userId, std::string const& userName, std::string const& userPasswordHash ) {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "createUser( userId: {:d}, userName: {:?}, userPasswordHash: {:?} )" ),
                                                                   userId,
                                                                   userName,
                                                                   userPasswordHash ),
                                                      fmt::format( fmt::runtime( "createUser()~" ) ) );

  UserModel::Data tmp;
  tmp.userId = userId;
  tmp.userName = userName;
  tmp.userPasswordHash = userPasswordHash;
  dataList_.push_back( tmp );

  uiTableModelRowInserted( uiModel_, dataList_.size() - 1 );
}

UserModel::Data UserModel::readUser( uint64_t userId ) {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "readUser( userId: {:d} )" ), userId ),
                                                      fmt::format( fmt::runtime( "readUser()~" ) ) );

  for( size_t i = 0; i < dataList_.size(); i++ ) {
    if( dataList_[i].userId == userId ) {
      return dataList_[i];
    }
  }
  return {};
}

UserModel::Data UserModel::readUserByIndex( int index ) {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "readUserByIndex( index: {:d} )" ), index ),
                                                      fmt::format( fmt::runtime( "readUserByIndex()~" ) ) );

  for( size_t i = 0; i < dataList_.size(); i++ ) {
    if( i == index ) {
      return dataList_[i];
    }
  }
  return {};
}

void UserModel::updateUser( uint64_t userId, std::string const& newUserName, std::string const& newUserPasswordHash ) {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "updateUser( userId: {:d}, newUserName: {:?}, newUserPasswordHash: {:?} )" ),
                                                                   userId,
                                                                   newUserName,
                                                                   newUserPasswordHash ),
                                                      fmt::format( fmt::runtime( "updateUser()~" ) ) );

  for( size_t i = 0; i < dataList_.size(); i++ ) {
    if( dataList_[i].userId == userId ) {
      dataList_[i].userName = newUserName;
      dataList_[i].userPasswordHash = newUserPasswordHash;
      uiTableModelRowChanged( uiModel_, i );
    }
  }
}

void UserModel::deleteUser( uint64_t userId ) {
  SFG::SystemSimulator::Logger::ScopedLogger _scolog( this->logger_,
                                                      fmt::format( fmt::runtime( "deleteUser( userId: {:d} )" ), userId ),
                                                      fmt::format( fmt::runtime( "deleteUser()~" ) ) );

  for( size_t i = 0; i < dataList_.size(); i++ ) {
    if( dataList_[i].userId == userId ) {
      dataList_.erase( dataList_.begin() + i );
      uiTableModelRowDeleted( uiModel_, i );
    }
  }
}

}  // namespace Models
}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
