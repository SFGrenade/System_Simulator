#ifndef SETTINGS_INTERFACE_MODELS_USERDATA_H_
#define SETTINGS_INTERFACE_MODELS_USERDATA_H_

#include <QObject>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

namespace SFG {
namespace SystemSimulator {
namespace SettingsInterface {

class UserData : public QObject {
  Q_OBJECT;
  Q_PROPERTY( uint64_t user_id READ get_user_id WRITE set_user_id NOTIFY user_id_changed );
  Q_PROPERTY( QString user_name READ get_user_name WRITE set_user_name NOTIFY user_name_changed );
  Q_PROPERTY( QString user_password_hash READ get_user_password_hash WRITE set_user_password_hash NOTIFY user_password_hash_changed );

  public:
  UserData( QObject* parent = nullptr );
  ~UserData( void );

  public:
  uint64_t get_user_id( void );
  QString get_user_name( void );
  QString get_user_password_hash( void );

  public slots:
  void set_user_id( uint64_t value );
  void set_user_name( QString const& value );
  void set_user_password_hash( QString const& value );

  signals:
  void user_id_changed( void );
  void user_name_changed( void );
  void user_password_hash_changed( void );

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  uint64_t userId_ = 0;
  QString userName_ = "";
  QString userPasswordHash_ = "";
};

}  // namespace SettingsInterface
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* SETTINGS_INTERFACE_MODELS_USERDATA_H_ */
