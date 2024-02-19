#ifndef CONFIG_HMI_MAINWINDOW_H_
#define CONFIG_HMI_MAINWINDOW_H_

#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QWidget>

#include "_spdlog.h"

namespace SFG {
namespace SystemSimulator {
namespace ConfigHmi {

class MainWindow : public QMainWindow {
  Q_OBJECT;

  public:
  MainWindow( QWidget* parent = nullptr );
  ~MainWindow();

  private:
  spdlogger logger_;
  QMenuBar* _MenuBar;
  QWidget* _Widget;
  QStatusBar* _StatusBar;
  QVBoxLayout* _VBoxLayout;
  QPushButton* _PushButton;

  private slots:
  void buttonClicked();
};

}  // namespace ConfigHmi
}  // namespace SystemSimulator
}  // namespace SFG

#endif /* CONFIG_HMI_MAINWINDOW_H_ */