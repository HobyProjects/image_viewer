#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "window.hpp"
#include "context.hpp"

namespace IMGV::Core
{
    class IMGV_API GLFW_ServiceAPI : public ServiceAPI
    {
        public:
            GLFW_ServiceAPI() = default;
            virtual ~GLFW_ServiceAPI() = default;

            virtual Boolean Init() override;
            virtual void Shutdown() override;
            virtual ServiceAPIs GetAPI() override{ return ServiceAPIs::API_GLFW; }
    };

    class IMGV_API GLFW_Window : public Window
    {
        public:
            GLFW_Window(const String& title);
            virtual ~GLFW_Window();

            virtual IMGV_Window GetNativeWindow() const override { return (IMGV_Window)m_NativeWindow; }
            virtual WindowSpecification& GetWindowSpecification() override { return m_Specification; }
            virtual Reference<Context> GetContext() override { return m_Context; }
            virtual void SwapBuffers() override;

        private:
            GLFWwindow* m_NativeWindow{IMGV_NULLPTR};
            WindowSpecification m_Specification{};
            Reference<Context> m_Context{IMGV_NULLPTR};
    };
}