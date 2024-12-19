#include "gl_context.hpp"
#include "asserts.hpp"

namespace IMGV::Core
{
    GL_Context::GL_Context(IMGV_Window window): m_NativeWindow(window){}

    Boolean GL_Context::MakeContextCurrent()
    {
        IMGV_ASSERT(m_NativeWindow, "GL_Context::MakeContextCurrent: m_NativeWindow is null");
        glfwMakeContextCurrent((GLFWwindow*)m_NativeWindow);
        glfwSwapInterval(1);

        GLenum status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if(status == IMGV_NULL)
        {
            IMGV_CORE_CRITICAL("GL_Context::MakeContextCurrent: Failed to initialize GLAD");
            return IMGV_FALSE;
        }

        IMGV_CORE_INFO("GL_Context::MakeContextCurrent: Created");
        return IMGV_TRUE;
    }

    void GL_Context::SwapBuffers()
    {
        IMGV_ASSERT(m_NativeWindow, "GL_Context::SwapBuffers: m_NativeWindow is null");
        glfwSwapBuffers((GLFWwindow*)m_NativeWindow);
    }

    void GL_Context::ChangeSwapInterval(UInt32 interval)
    {
        IMGV_ASSERT(m_NativeWindow, "GL_Context::ChangeSwapInterval: m_NativeWindow is null");
        glfwSwapInterval(interval);
    }
}