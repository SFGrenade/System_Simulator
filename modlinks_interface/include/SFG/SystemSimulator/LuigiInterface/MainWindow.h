#pragma once

// Project includes
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/LuigiInterface/Models/FolderModel.h>
#include <SFG/SystemSimulator/LuigiInterface/Models/ModLinksModel.h>
#include <SFG/SystemSimulator/LuigiInterface/Models/UserModel.h>
#include <SFG/SystemSimulator/LuigiInterface/UI/AbstractTable.h>
#include <SFG/SystemSimulator/LuigiInterface/libui_all.h>

namespace SFG {
namespace SystemSimulator {
namespace LuigiInterface {

class MainWindow {
  public:
  explicit MainWindow();
  ~MainWindow();

  uiWindow* getUiWindow() const;

  private:
  SFG::SystemSimulator::Logger::spdlogger logger_;
  uiWindow* window_ = nullptr;
  uiBox* buttonPanel_ = nullptr;
  uiBox* mainPanel_ = nullptr;
  uiButton* installButton_ = nullptr;
  uiButton* disableButton_ = nullptr;
  uiButton* enableButton_ = nullptr;
  uiButton* uninstallButton_ = nullptr;
  uiButton* updateButton_ = nullptr;
  // Models::FolderModel model_;
  Models::ModLinksModel model_;
  // Models::UserModel model_;
  UI::AbstractTable* table_ = nullptr;

  private:
  void installButtonClicked();
  void disableButtonClicked();
  void enableButtonClicked();
  void uninstallButtonClicked();
  void updateButtonClicked();
};

}  // namespace LuigiInterface
}  // namespace SystemSimulator
}  // namespace SFG
