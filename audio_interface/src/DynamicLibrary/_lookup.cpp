// Assigned Header
#include "SFG/SystemSimulator/AudioInterface/Sources/ALSA.h"

namespace SFG::SystemSimulator::AudioInterface::DynamicLibrary {

LibraryHandle loadLibrary( std::string const& library_name ) {
  LoadedDllHandle ret = nullptr;
#if defined( _WIN32 ) || defined( _WIN64 )
  ret = ::LoadLibraryA( library_name.c_str() );
#elif defined( __APPLE__ ) || defined( __linux__ )
  ret = ::dlopen( library_name.c_str(), RTLD_NOW );
#endif
  return LibraryHandle( ret, []( LoadedDllHandle p ) {
#if defined( _WIN32 ) || defined( _WIN64 )
    ::FreeLibrary( p );
#elif defined( __APPLE__ ) || defined( __linux__ )
    ::dlclose( p );
#endif
  } );
}

}  // namespace SFG::SystemSimulator::AudioInterface::DynamicLibrary
