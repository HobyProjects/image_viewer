#pragma once

#ifdef IMGV_DEBUG

    #if defined(IMGV_PLATFORM_WINDOWS)
        #define IMGV_DEBUGBREAK() __debugbreak()
    #elif defined(IMGV_PLATFORM_LINUX)
        #include <signal.h>
        #define IMGV_DEBUGBREAK() raise(SIGTRAP)
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif

    #ifdef IMGV_SHARED
        #ifdef IMGV_PLATFORM_WINDOWS
            #ifdef IMGV_BUILD_DLL
                #define IMGV_API __declspec(dllexport)
            #else
                #define IMGV_API __declspec(dllimport)
            #endif
        #elif defined(IMGV_PLATFORM_LINUX)
            #ifdef IMGV_BUILD_DLL
                #define IMGV_API __attribute__((visibility("default")))
            #else
                #define IMGV_API
            #endif
        #endif
    #else
        #define IMGV_API
    #endif

    #ifdef IMGV_STATIC
        #define IMGV_API
    #endif

    #define IMGV_INSTRUMENTS_ENABLED
    #define IMGV_ASSERTS_ENABLED
    #define IMGV_TOSTRING(x) #x
    #define IMGV_BIT(x) (1 << x)

#else

    #define IMGV_DEBUGBREAK()
    #define IMGV_MACTOSTRING(x) #x

#endif