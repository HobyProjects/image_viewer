#include "gl_renderer.hpp"

namespace IMGV::Core
{
    void GL_Renderer::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        #ifdef IMGV_DEBUG

            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(DebugMessageCallback, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
        
        #endif
    }

    void GL_Renderer::Shutdown()
    {
    }

    void GL_Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GL_Renderer::ClearColor(const Vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void GL_Renderer::SetViewport(UInt32 x, UInt32 y, UInt32 width, UInt32 height)
    {
        glViewport(x, y, width, height);
    }
}