#pragma once

#include "base.hpp"
#include "log.hpp"

#ifdef IMGV_ASSERTS_ENABLED
    #define IMGV_ASSERT(condition, ...) if(!(condition)) { IMGV_CORE_CRITICAL("Assertion failed: {0}", __VA_ARGS__); IMGV_DEBUGBREAK(); }
#else
    #define IMGV_ASSERT(condition, ...)
#endif // IMGV_ASSERTS_ENABLED