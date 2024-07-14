#ifndef SETTINGS_INTERFACE_MAINWINDOW_H_
#define SETTINGS_INTERFACE_MAINWINDOW_H_

#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QWidget>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>

namespace SFG {
namespace SystemSimulator {
namespace SettingsInterface {

class MainWindow : public QMainWindow {
  Q_OBJECT;

  public:
  MainWindow( QWidget* parent = nullptr );
  ~MainWindow();

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  QMenuBar* _MenuBar;
  QWidget* _Widget;
  QStatusBar* _StatusBar;
  QVBoxLayout* _VBoxLayout;
  QPushButton* _PushButton;

  private slots:
  void buttonClicked();
};

}  // namespace SettingsInterface
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* SETTINGS_INTERFACE_MAINWINDOW_H_ */
