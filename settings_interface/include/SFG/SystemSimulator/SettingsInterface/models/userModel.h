#ifndef SETTINGS_INTERFACE_MODELS_USERMODEL_H_
#define SETTINGS_INTERFACE_MODELS_USERMODEL_H_

#include <QAbstractListModel>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

namespace SFG {
namespace SystemSimulator {
namespace SettingsInterface {

class UserModel : public QAbstractListModel {
  Q_OBJECT;
  // Q_PROPERTY();

  public:
  UserModel( QObject* parent = nullptr );
  ~UserModel();

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
};

}  // namespace SettingsInterface
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* SETTINGS_INTERFACE_MODELS_USERMODEL_H_ */