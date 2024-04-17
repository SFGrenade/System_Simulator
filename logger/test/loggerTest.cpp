#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <SFG/SystemSimulator/Logger/scopedLogger.h>
#include <gtest/gtest.h>

TEST( Logger, ScopedLogger ) {
  { SFG::SystemSimulator::Logger::ScopedLogger( SFG::SystemSimulator::Logger::LoggerFactory::get_logger( "ScopedLogger" ), "Entry", "Exit" ); }
  EXPECT_TRUE( true );
}
