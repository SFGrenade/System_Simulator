#pragma once

// Library includes
#include <ui.h>

// Platform includes
#if defined( __linux__ )
// first
#include <gtk/gtk.h>
// then
#include <ui_unix.h>
#endif
#if defined( __APPLE__ )
// first
#include <Cocoa/Cocoa.h>
// then
#include <ui_darwin.h>
#endif
#if defined( _WIN32 ) || defined( __MINGW32__ )
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
// first
#include <Windows.h>
// then
#include <ui_windows.h>
#endif
