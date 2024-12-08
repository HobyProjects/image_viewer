#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "context.hpp"
#include "typedef.hpp"

namespace IMGV::Core
{
    class IMGV_API GL_Context final : public Context
    {
        public:
            GL_Context() = default;
            GL_Context(IMGV_Window window);
            virtual ~GL_Context() override;

            virtual Boolean MakeContextCurrent() override;
            virtual void SwapBuffers() override;
            virtual void ChangeSwapInterval(UInt32 interval) override;

        private:
            IMGV_Window m_NativeWindow{IMGV_NULLPTR};
    };
}