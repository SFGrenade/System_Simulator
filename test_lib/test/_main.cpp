#include <SFG/SystemSimulator/Logger/loggerFactory.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

static int g_allocationCount = 0;
static int g_copyCount = 0;
static int g_moveCount = 0;

void* operator new( size_t size ) {
  g_allocationCount++;
  return malloc( size );
}
/*template < class T >
T::T( T const& other ) {
  g_copyCount++;
}
template < class T >
T::T( T&& other ) {
  g_moveCount++;
}*/

int main( int argc, char** argv ) {
  SFG::SystemSimulator::Logger::LoggerFactory::init( "testLogs/test_lib_test.log", false );
  std::vector< std::string > args;
  args.reserve( argc );
  for( int i = 0; i < argc; i++ ) {
    args.push_back( std::string( argv[i] ) );
  }
  spdlog::trace( fmt::runtime( "main( argc: {:d}, argv: '{:s}' )" ), argc, fmt::join( args, "', '" ) );

  testing::InitGoogleTest( &argc, argv );
  int retVal = RUN_ALL_TESTS();

  spdlog::trace( fmt::runtime( "Allocations: {}" ) );
  spdlog::trace( fmt::runtime( "Copies: {}" ) );
  spdlog::trace( fmt::runtime( "Moves: {}" ) );
  spdlog::trace( fmt::runtime( "~main" ) );
  SFG::SystemSimulator::Logger::LoggerFactory::deinit();
  return retVal;
}
