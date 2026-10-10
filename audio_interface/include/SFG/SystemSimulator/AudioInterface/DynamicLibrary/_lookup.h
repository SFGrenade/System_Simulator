#pragma once

// C++ Includes
#include <memory>
#include <string>

// System includes
#if defined( _WIN32 ) || defined( _WIN64 )
#if !defined( WIN32_LEAN_AND_MEAN )
#define WIN32_LEAN_AND_MEAN
#endif
#if !defined( NOMINMAX )
#define NOMINMAX
#endif
#include <Windows.h>
#elif defined( __APPLE__ ) || defined( __linux__ )
#include <dlfcn.h>
#endif

namespace SFG::SystemSimulator::AudioInterface::DynamicLibrary {

#if defined( _WIN32 ) || defined( _WIN64 )
using LoadedDllHandle = HMODULE;
using LibraryHandle = std::shared_ptr< HINSTANCE__ >;
#elif defined( __APPLE__ ) || defined( __linux__ )
using LoadedDllHandle = void*;
using LibraryHandle = std::shared_ptr< void >;
#endif

LibraryHandle loadLibrary( std::string const& library_name );

template < typename FunctionType >
FunctionType loadSymbol( LibraryHandle library, std::string const& name ) {
#if defined( _WIN32 ) || defined( _WIN64 )
  return reinterpret_cast< FunctionType >( ::GetProcAddress( library.get(), name.c_str() ) );
#elif defined( __APPLE__ ) || defined( __linux__ )
  return reinterpret_cast< FunctionType >( ::dlsym( library.get(), name.c_str() ) );
#endif
}

}  // namespace SFG::SystemSimulator::AudioInterface::DynamicLibrary
