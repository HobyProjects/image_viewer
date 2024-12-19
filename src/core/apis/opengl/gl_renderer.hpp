#pragma once 

#include <glad/glad.h>

#include "base.hpp"
#include "gl_debug.hpp"
#include "typedef.hpp"

namespace IMGV::Core
{
    class IMGV_API GL_Renderer
    {
        private:
            GL_Renderer() = default;
            ~GL_Renderer() = default;

        public:
            static void Init();
            static void Shutdown();
            static void Clear();
            static void ClearColor(const Vec4& color);
            static void SetViewport(UInt32 x, UInt32 y, UInt32 width, UInt32 height);
    };
}
