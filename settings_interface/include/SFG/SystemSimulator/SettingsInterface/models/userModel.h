#ifndef SETTINGS_INTERFACE_MODELS_USERMODEL_H_
#define SETTINGS_INTERFACE_MODELS_USERMODEL_H_

#include <QAbstractListModel>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

#include "SFG/SystemSimulator/SettingsInterface/models/userData.h"

namespace SFG {
namespace SystemSimulator {
namespace SettingsInterface {

class UserModel : public QAbstractListModel {
  Q_OBJECT;
  // Q_PROPERTY();

  public:
  enum class Roles {
    UserId = Qt::ItemDataRole::UserRole + 1,
    UserName,
    UserPasswordHash,
  };

  public:
  UserModel( QObject *parent = nullptr );
  ~UserModel();

  // Reimplementations
  public:
  QHash< int, QByteArray > roleNames() const override;
  int rowCount( const QModelIndex &parent = QModelIndex() ) const override;
  Qt::ItemFlags flags( const QModelIndex &index ) const override;
  QVariant data( const QModelIndex &index, int role = Qt::DisplayRole ) const override;
  QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const override;
  bool setData( const QModelIndex &index, const QVariant &value, int role = Qt::EditRole ) override;
  bool setHeaderData( int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole ) override;
  bool insertRows( int row, int count, const QModelIndex &parent = QModelIndex() ) override;
  bool removeRows( int row, int count, const QModelIndex &parent = QModelIndex() ) override;

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  std::vector< SFG::SystemSimulator::SettingsInterface::UserData * > userList_;
};

}  // namespace SettingsInterface
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* SETTINGS_INTERFACE_MODELS_USERMODEL_H_ */
