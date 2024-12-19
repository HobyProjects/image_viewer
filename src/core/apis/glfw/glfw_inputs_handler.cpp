#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "glfw_inputs_handler.hpp"
#include "asserts.hpp"

namespace IMGV::Core
{
    static Reference<Window> s_TargetWindow = IMGV_NULLPTR;

    void GLFW_InputHandler::TargetWindow(const Reference<Window>& window)
    {
        s_TargetWindow = window;
    }

    Boolean GLFW_InputHandler::IsKeyPressed(KeyCodes keyCode)
    {
        if(!s_TargetWindow)
        {
            IMGV_CORE_ERROR("Target window not set");
            return IMGV_FALSE;
        }

        auto state = glfwGetKey((GLFWwindow*)s_TargetWindow->GetNativeWindow(), static_cast<Int32>(keyCode));
        return state == IMGV::Core::KeyState::KEY_PRESSED || state == IMGV::Core::KeyState::KEY_REPEAT;
    }

    Boolean GLFW_InputHandler::IsMouseButtonPressed(MouseButton button)
    {
        if(!s_TargetWindow)
        {
            IMGV_CORE_ERROR("Target window not set");
            return IMGV_FALSE;
        }

        auto state = glfwGetMouseButton((GLFWwindow*)s_TargetWindow->GetNativeWindow(), static_cast<Int32>(button));
        return state == IMGV::Core::MouseButtonState::MOUSE_BUTTON_PRESSED;
    }

    Vec2 GLFW_InputHandler::GetMousePosition()
    {
        if(!s_TargetWindow)
        {
            IMGV_CORE_ERROR("Target window not set");
            return {0, 0};
        }

        double x{}, y{};
        glfwGetCursorPos((GLFWwindow*)s_TargetWindow->GetNativeWindow(), &x, &y);
        return {static_cast<Float>(x), static_cast<Float>(y)};        
    }   
}