#include <SFG/SystemSimulator/Configuration/configuration.h>
#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <gtest/gtest.h>
#include <string>

TEST( Configuration, ReadingStringValue ) {
  SFG::SystemSimulator::Configuration::Configuration config( "config/test_conf.ini" );
  std::string myVal = config.get< std::string >( "Test", "Key" );
  spdlog::trace( fmt::runtime( "myVal = {:s}" ), myVal );
  EXPECT_EQ( myVal, "value" );
}
