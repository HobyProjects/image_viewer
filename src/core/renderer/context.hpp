#pragma once

#include <memory>

#include "base.hpp"
#include "typedef.hpp"

namespace IMGV::Core
{
    class IMGV_API Context
    {
        public:
            Context() = default;
            virtual ~Context() = default;

            virtual Boolean MakeContextCurrent() = IMGV_NULL;
            virtual void SwapBuffers() = IMGV_NULL;
            virtual void ChangeSwapInterval(UInt32 interval) = IMGV_NULL;
    };
    
    IMGV_NODISCARD IMGV_API Reference<Context> CreateContext(IMGV_Window window);
}