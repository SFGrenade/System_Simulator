#include "SFG/SystemSimulator/SettingsInterface/models/userData.h"

namespace SFG {
namespace SystemSimulator {
namespace SettingsInterface {

UserData::UserData( QObject* parent ) : QObject( parent ), logger_( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "UserData" ) ) {
  this->logger_->trace( fmt::runtime( "UserData( parent: {:p} )" ), static_cast< void* >( parent ) );

  this->logger_->trace( fmt::runtime( "UserData()~" ) );
}

UserData::~UserData( void ) {
  this->logger_->trace( fmt::runtime( "~UserData()" ) );

  this->logger_->trace( fmt::runtime( "~UserData()~" ) );
}

uint64_t UserData::get_user_id( void ) {
  this->logger_->trace( fmt::runtime( "get_user_id()" ) );

  this->logger_->trace( fmt::runtime( "get_user_id()~" ) );
  return this->userId_;
}

QString UserData::get_user_name( void ) {
  this->logger_->trace( fmt::runtime( "get_user_name()" ) );

  this->logger_->trace( fmt::runtime( "get_user_name()~" ) );
  return this->userName_;
}

QString UserData::get_user_password_hash( void ) {
  this->logger_->trace( fmt::runtime( "get_user_password_hash()" ) );

  this->logger_->trace( fmt::runtime( "get_user_password_hash()~" ) );
  return this->userPasswordHash_;
}

void UserData::set_user_id( uint64_t value ) {
  this->logger_->trace( fmt::runtime( "set_user_id( value = {:d} )" ), value );

  this->userId_ = value;
  emit this->user_id_changed();

  this->logger_->trace( fmt::runtime( "set_user_id()~" ) );
}

void UserData::set_user_name( QString const& value ) {
  this->logger_->trace( fmt::runtime( "set_user_name( value = '{:s}' )" ), value.toStdString() );

  this->userName_ = value;
  emit this->user_name_changed();

  this->logger_->trace( fmt::runtime( "set_user_name()~" ) );
}

void UserData::set_user_password_hash( QString const& value ) {
  this->logger_->trace( fmt::runtime( "set_user_password_hash( value = '{:s}' )" ), value.toStdString() );

  this->userPasswordHash_ = value;
  emit this->user_password_hash_changed();

  this->logger_->trace( fmt::runtime( "set_user_password_hash()~" ) );
}

}  // namespace SettingsInterface
}  // namespace SystemSimulator
}  // namespace SFG
