#pragma once
#ifndef OXYGINE_INCLUDE
#define OXYGINE_INCLUDE
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

//#define OXYGINE_NO_YEILD 1

// Platform enum macro
#define OXYGINE_MARMALADE 1
#define OXYGINE_EMSCRIPTEN 2
#define OXYGINE_FLASH 3
#define OXYGINE_WINDOWS 4
#define OXYGINE_MAC 5
#define OXYGINE_LINUX 6
#define OXYGINE_ANDROID 7
#define OXYGINE_IOS 8

#if __S3E__
  #define OXYGINE_PLATFORM OXYGINE_MARMALADE
	#ifdef IW_DEBUG
		#define OX_DEBUG 1
	#endif
#elif EMSCRIPTEN
  #define OXYGINE_PLATFORM OXYGINE_EMSCRIPTEN
	#ifndef NDEBUG
		#define OX_DEBUG 1
	#endif // DEBUG	
#elif ANDROID
  #define OXYGINE_PLATFORM OXYGINE_ANDROID
#elif TARGET_OS_IPHONE
  #define OXYGINE_PLATFORM OXYGINE_IOS
#else
  // Windows/Mac/Linux using DLC
	#define OXYGINE_SDL 1
	
  #ifdef WIN32
    #define OXYGINE_PLATFORM OXYGINE_WINDOWS
		#ifndef _CRT_SECURE_NO_WARNINGS
			#define _CRT_SECURE_NO_WARNINGS
		#endif
  #elif __unix__
    // guesswork    
    #define OXYGINE_PLATFORM OXYGINE_LINUX
  #elif __APPLE__
    // guesswork
    #define OXYGINE_PLATFORM OXYGINE_MAC
	#endif
#endif

#ifndef OXYGINE_PLATFORM
#error "Could not detect Oxygine platform"
#endif

// Macro to check that the platform is the current build target
#define OX_PLATFORM(platform) ( OXYGINE_PLATFORM == OXYGINE_##platform )

#if _DEBUG || DEBUG
	#ifndef OX_DEBUG
		#define OX_DEBUG 1
	#endif
#endif


#define DYNAMIC_OBJECT_NAME 1

#ifndef OX_DEBUG
  #if !OX_PLATFORM(EMSCRIPTEN)
		#define USE_MEMORY_POOL 1
		#define OBJECT_POOL_ALLOCATOR 1
	#endif
#endif

#if OX_DEBUG
	#define OXYGINE_DEBUG_TRACE_LEAKS 1
	#define OXYGINE_DEBUG_T2P 1
	#define OXYGINE_DEBUG_SAFECAST 1
	#define OXYGINE_TRACE_VIDEO_STATS 1
#endif

#define OXYGINE_ASSERT2LOG 1

#if OXYGINE_ASSERT2LOG
namespace oxygine{namespace log{void error(const char *format, ...);}}
#ifdef OXYGINE_QT
#define OX_ASSERT(x) if (!(x)) {__asm("int3");oxygine::log::error("Assert! %d %s", __LINE__, __FILE__); }(assert(x))
#elif OX_PLATFORM(EMSCRIPTEN)
#define OX_ASSERT(x) if (!(x)) {oxygine::log::error("Assert! %d %s", __LINE__, __FILE__);}
#else
#define OX_ASSERT(x) if (!(x)) {oxygine::log::error("Assert! %d %s", __LINE__, __FILE__);}(assert(x))
#endif
#else
#define OX_ASSERT(x) (if (!(x)) oxygine::log::error("Assert! %d %s", __LINE__, __FILE__))
#endif

#define OXYGINE_HAS_RESTORE

#ifdef __GNUC__
#define OXYGINE_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define OXYGINE_DEPRECATED __declspec(deprecated)
#else
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define OXYGINE_DEPRECATED
#endif

#endif //OXYGINE_INCLUDE
