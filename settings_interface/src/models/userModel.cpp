#include "SFG/SystemSimulator/SettingsInterface/models/userModel.h"

#include <SFG/SystemSimulator/Logger-Qt/qtFormatter.h>

namespace SFG {
namespace SystemSimulator {
namespace SettingsInterface {

UserModel::UserModel( QObject *parent ) : QAbstractListModel( parent ), logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "UserModel" ) ) {
  this->logger_->trace( fmt::runtime( "UserModel( parent: {:p} )" ), static_cast< void * >( parent ) );

  this->logger_->trace( fmt::runtime( "UserModel()~" ) );
}

UserModel::~UserModel() {
  this->logger_->trace( fmt::runtime( "~UserModel()" ) );

  this->logger_->trace( fmt::runtime( "~UserModel()~" ) );
}

QHash< int, QByteArray > UserModel::roleNames() const {
  SFG::SystemSimulator::Logger::ScopedLog( this->logger_, fmt::format( fmt::runtime( "roleNames()" ) ), fmt::format( fmt::runtime( "roleNames()~" ) ) );

  QHash< int, QByteArray > ret{
      { static_cast< int >( SFG::SystemSimulator::SettingsInterface::UserModel::Roles::UserId ), "userId" },
      { static_cast< int >( SFG::SystemSimulator::SettingsInterface::UserModel::Roles::UserName ), "userName" },
      { static_cast< int >( SFG::SystemSimulator::SettingsInterface::UserModel::Roles::UserPasswordHash ), "userPasswordHash" },
  };
  return ret;
}

int UserModel::rowCount( QModelIndex const &parent ) const {
  SFG::SystemSimulator::Logger::ScopedLog( this->logger_,
                                           fmt::format( fmt::runtime( "rowCount( parent: {:qmi} )" ), parent ),
                                           fmt::format( fmt::runtime( "rowCount()~" ) ) );

  if( parent.isValid() ) {
    return 0;
  }
  return userList_.size();
}

Qt::ItemFlags UserModel::flags( QModelIndex const &index ) const {
  SFG::SystemSimulator::Logger::ScopedLog( this->logger_,
                                           fmt::format( fmt::runtime( "flags( index: {:qmi} )" ), index ),
                                           fmt::format( fmt::runtime( "flags()~" ) ) );

  if( !index.isValid() ) {
    return Qt::ItemFlag::NoItemFlags;
  }
  if( index.column() != 0 ) {
    return Qt::ItemFlag::NoItemFlags;
  }
  if( index.row() < 0 ) {
    return Qt::ItemFlag::NoItemFlags;
  }
  if( index.row() >= rowCount() ) {
    return Qt::ItemFlag::NoItemFlags;
  }
  return Qt::ItemFlag::ItemIsSelectable | Qt::ItemFlag::ItemIsEditable | Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemNeverHasChildren;
}

QVariant UserModel::data( QModelIndex const &index, int role ) const {
  SFG::SystemSimulator::Logger::ScopedLog( this->logger_,
                                           fmt::format( fmt::runtime( "data( index: {:qmi}, role: {:d} )" ), index, role ),
                                           fmt::format( fmt::runtime( "data()~" ) ) );

  if( !index.isValid() ) {
    return QVariant();
  }
  if( index.column() != 0 ) {
    return QVariant();
  }
  if( index.row() < 0 ) {
    return QVariant();
  }
  if( index.row() >= rowCount() ) {
    return QVariant();
  }
  switch( role ) {
    case static_cast< int >( UserModel::Roles::UserId ):
      return userList_.at( index.row() )->get_user_id();
    case static_cast< int >( UserModel::Roles::UserName ):
      return userList_.at( index.row() )->get_user_name();
    case static_cast< int >( UserModel::Roles::UserPasswordHash ):
      return userList_.at( index.row() )->get_user_password_hash();
    default:
      return QVariant();
  }
}

QVariant UserModel::headerData( int section, Qt::Orientation orientation, int role ) const {
  SFG::SystemSimulator::Logger::ScopedLog( this->logger_,
                                           fmt::format( fmt::runtime( "headerData( section: {:d}, orientation: {:d}, role: {:d} )" ),
                                                        section,
                                                        static_cast< int >( orientation ),
                                                        role ),
                                           fmt::format( fmt::runtime( "headerData()~" ) ) );

  if( orientation == Qt::Orientation::Horizontal && section != 0 ) {
    return QVariant();
  }
  if( orientation == Qt::Orientation::Vertical && section < 0 ) {
    return QVariant();
  }
  if( orientation == Qt::Orientation::Vertical && section >= rowCount() ) {
    return QVariant();
  }
  switch( role ) {
    case static_cast< int >( UserModel::Roles::UserId ):
      return "User ID";
    case static_cast< int >( UserModel::Roles::UserName ):
      return "Username";
    case static_cast< int >( UserModel::Roles::UserPasswordHash ):
      return "Password Hash";
    default:
      return QVariant();
  }
}

bool UserModel::setData( QModelIndex const &index, QVariant const &value, int role ) {
  SFG::SystemSimulator::Logger::ScopedLog( this->logger_,
                                           fmt::format( fmt::runtime( "setData( index: {:qmi}, value: '{:qs}', role: {:d} )" ), index, value.toString(), role ),
                                           fmt::format( fmt::runtime( "setData()~" ) ) );

  if( !index.isValid() ) {
    return false;
  }
  if( index.column() != 0 ) {
    return false;
  }
  if( index.row() < 0 ) {
    return false;
  }
  if( index.row() >= rowCount() ) {
    return false;
  }
  switch( role ) {
    case static_cast< int >( UserModel::Roles::UserId ): {
      // if( std::string( value.typeName() ) != std::string( QVariant::fromValue( 0ULL ).typeName() ) )
      //   return false;
      userList_.at( index.row() )->set_user_id( value.toULongLong() );
      emit this->dataChanged( index, index, QVector< int >{ role } );
      return true;
    }
    case static_cast< int >( UserModel::Roles::UserName ): {
      // if( std::string( value.typeName() ) != std::string( QVariant::fromValue( QString( "" ) ).typeName() ) )
      //   return false;
      userList_.at( index.row() )->set_user_name( value.toString() );
      emit this->dataChanged( index, index, QVector< int >{ role } );
      return true;
    }
    case static_cast< int >( UserModel::Roles::UserPasswordHash ): {
      // if( std::string( value.typeName() ) != std::string( QVariant::fromValue( QString( "" ) ).typeName() ) )
      //   return false;
      userList_.at( index.row() )->set_user_password_hash( value.toString() );
      emit this->dataChanged( index, index, QVector< int >{ role } );
      return true;
    }
    default:
      return false;
  }
}

bool UserModel::setHeaderData( int section, Qt::Orientation orientation, QVariant const &value, int role ) {
  SFG::SystemSimulator::Logger::ScopedLog( this->logger_,
                                           fmt::format( fmt::runtime( "setHeaderData( section: {:d}, orientation: {:d}, value: '{:qs}', role: {:d} )" ),
                                                        section,
                                                        static_cast< int >( orientation ),
                                                        value.toString(),
                                                        role ),
                                           fmt::format( fmt::runtime( "setHeaderData()~" ) ) );

  // No setting header data
  return false;
}

bool UserModel::insertRows( int row, int count, QModelIndex const &parent ) {
  SFG::SystemSimulator::Logger::ScopedLog( this->logger_,
                                           fmt::format( fmt::runtime( "insertRows( row: {:d}, count: {:d}, parent: {:qmi} )" ), row, count, parent ),
                                           fmt::format( fmt::runtime( "insertRows()~" ) ) );

  if( parent.isValid() ) {
    return false;
  }
  if( row < 0 ) {
    return false;
  }
  if( row > rowCount() ) {
    return false;
  }
  this->beginInsertRows( parent, row, row + count - 1 );
  for( int i = row; i < row + count; i++ ) {
    this->userList_.insert( this->userList_.begin() + i, new SFG::SystemSimulator::SettingsInterface::UserData( this ) );
  }
  this->endInsertRows();
  return true;
}

bool UserModel::removeRows( int row, int count, QModelIndex const &parent ) {
  SFG::SystemSimulator::Logger::ScopedLog( this->logger_,
                                           fmt::format( fmt::runtime( "removeRows( row: {:d}, count: {:d}, parent: {:qmi} )" ), row, count, parent ),
                                           fmt::format( fmt::runtime( "removeRows()~" ) ) );

  if( parent.isValid() ) {
    return false;
  }
  if( row < 0 ) {
    return false;
  }
  if( row >= rowCount() ) {
    return false;
  }
  this->beginRemoveRows( parent, row, row + count - 1 );
  for( int i = row + count - 1; i >= row; i-- ) {
    this->userList_.at( i )->deleteLater();
  }
  this->userList_.erase( this->userList_.begin() + row, this->userList_.begin() + row + count - 1 );
  this->endRemoveRows();
  return true;
}

}  // namespace SettingsInterface
}  // namespace SystemSimulator
}  // namespace SFG
