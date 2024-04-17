#include <QAbstractItemModelTester>
#include <SFG/SystemSimulator/Logger-Qt/qtFormatter.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/SettingsInterface/models/userModel.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

TEST( SettingsInterface, UserModelTest ) {
  spdlog::trace( fmt::runtime( "Running QAbstractItemModelTester on UserModel" ) );
  SFG::SystemSimulator::SettingsInterface::UserModel* userModel = new SFG::SystemSimulator::SettingsInterface::UserModel();
  QAbstractItemModelTester* modelTester_UserModel = new QAbstractItemModelTester( userModel, QAbstractItemModelTester::FailureReportingMode::Fatal );

  EXPECT_TRUE( userModel->insertRow( 0 ) );
  EXPECT_TRUE( userModel->setData( userModel->index( 0 ), 1ULL, static_cast< int >( SFG::SystemSimulator::SettingsInterface::UserModel::Roles::UserId ) ) );
  EXPECT_TRUE( userModel->setData( userModel->index( 0 ),
                                   QString( "Username" ),
                                   static_cast< int >( SFG::SystemSimulator::SettingsInterface::UserModel::Roles::UserName ) ) );
  EXPECT_TRUE( userModel->setData( userModel->index( 0 ),
                                   QString( "Password" ),
                                   static_cast< int >( SFG::SystemSimulator::SettingsInterface::UserModel::Roles::UserPasswordHash ) ) );

  delete modelTester_UserModel;
  delete userModel;

  EXPECT_TRUE( true );
}
