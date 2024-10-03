#ifndef SETTINGS_INTERFACE_MODELS_LISTTOTABLEMODEL_H_
#define SETTINGS_INTERFACE_MODELS_LISTTOTABLEMODEL_H_

#include <QAbstractListModel>
#include <QAbstractTableModel>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

namespace SFG {
namespace SystemSimulator {
namespace SettingsInterface {

class ListToTableModel : public QAbstractTableModel {
  Q_OBJECT;
  // Q_PROPERTY();

  public:
  ListToTableModel( QObject *parent = nullptr );
  ~ListToTableModel();

  public:
  void setSourceModel( QAbstractListModel *model = nullptr );

  // Reimplementations
  public:
  QHash< int, QByteArray > roleNames() const override;
  int columnCount( QModelIndex const &parent = QModelIndex() ) const override;
  int rowCount( QModelIndex const &parent = QModelIndex() ) const override;
  Qt::ItemFlags flags( QModelIndex const &index ) const override;
  QVariant data( QModelIndex const &index, int role = Qt::DisplayRole ) const override;
  QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const override;
  bool setData( QModelIndex const &index, QVariant const &value, int role = Qt::EditRole ) override;
  bool setHeaderData( int section, Qt::Orientation orientation, QVariant const &value, int role = Qt::EditRole ) override;
  bool insertColumns( int column, int count, QModelIndex const &parent = QModelIndex() ) override;
  bool insertRows( int row, int count, QModelIndex const &parent = QModelIndex() ) override;
  bool removeColumns( int column, int count, QModelIndex const &parent = QModelIndex() ) override;
  bool removeRows( int row, int count, QModelIndex const &parent = QModelIndex() ) override;

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  QAbstractListModel *model_;
};

}  // namespace SettingsInterface
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* SETTINGS_INTERFACE_MODELS_LISTTOTABLEMODEL_H_ */
