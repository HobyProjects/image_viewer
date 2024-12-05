#pragma once

#include <memory>
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
    
    IMGV_API Ref<Context> CreateContext(IMGV_Window window);
}