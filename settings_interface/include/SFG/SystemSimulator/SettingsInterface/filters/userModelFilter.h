#ifndef SETTINGS_INTERFACE_FILTERS_USERMODELFILTER_H_
#define SETTINGS_INTERFACE_FILTERS_USERMODELFILTER_H_

#include <QSortFilterProxyModel>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

namespace SFG {
namespace SystemSimulator {
namespace SettingsInterface {

class UserModelFilter : public QSortFilterProxyModel {
  Q_OBJECT;
  // Q_PROPERTY();

  public:
  UserModelFilter( QObject *parent = nullptr );
  ~UserModelFilter();

  // Reimplementations
  public:
  bool lessThan( QModelIndex const &sourceIndexLeft, QModelIndex const &sourceIndexRight ) const;

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
};

}  // namespace SettingsInterface
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* SETTINGS_INTERFACE_FILTERS_USERMODELFILTER_H_ */
