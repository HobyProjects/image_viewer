#include "glfw_event_receiver.hpp"

namespace IMGV::Core
{
    static Ref<Window> s_Window = IMGV_NULLPTR;
    static EventCallBack s_EventCallback;

    static void SetCallBacks()
    {
        glfwSetWindowCloseCallback((GLFWwindow*)s_Window->GetNativeWindow(), [](GLFWwindow* window) 
        {
            WindowCloseEvent windowClose;
            s_EventCallback(windowClose); 
        });

        glfwSetWindowSizeCallback((GLFWwindow*)s_Window->GetNativeWindow(), [](GLFWwindow* window, int width, int height) 
        {
            WindowResizeEvent windowResize(width, height);
            s_Window->GetWindowSpecification().Width = width;
            s_Window->GetWindowSpecification().Height = height;
            s_EventCallback(windowResize);
        });

        glfwSetWindowPosCallback((GLFWwindow*)s_Window->GetNativeWindow(), [](GLFWwindow* window, int x, int y) 
        {
            WindowMovedEvent windowPosChange(x, y);
            s_Window->GetWindowSpecification().PosX = x;
            s_Window->GetWindowSpecification().PosY = y;
            s_EventCallback(windowPosChange);
        });

        glfwSetWindowFocusCallback((GLFWwindow*)s_Window->GetNativeWindow(), [](GLFWwindow* window, int focused) 
        {
            if (focused) {
                WindowFocusGainedEvent windowFocusGain;
                s_Window->GetWindowSpecification().IsFocused = true;
                s_EventCallback(windowFocusGain);
            } 
            else {
                WindowFocusLostEvent windowFocusLost;
                s_Window->GetWindowSpecification().IsFocused = false;
                s_EventCallback(windowFocusLost);
            }
        });

        glfwSetWindowMaximizeCallback((GLFWwindow*)s_Window->GetNativeWindow(), [](GLFWwindow* window, int maximized) 
        {
            WindowMaximizedEvent windowMaximized;
            s_Window->GetWindowSpecification().WindowState = WindowState::Maximized;
            s_EventCallback(windowMaximized);
        });

        glfwSetWindowIconifyCallback((GLFWwindow*)s_Window->GetNativeWindow(), [](GLFWwindow* window, int iconified) 
        {
            WindowMinimizedEvent windowMinimized;
            s_Window->GetWindowSpecification().WindowState = WindowState::Minimized;
            s_EventCallback(windowMinimized);
        });

        glfwSetFramebufferSizeCallback((GLFWwindow*)s_Window->GetNativeWindow(), [](GLFWwindow* window, int width, int height) 
        {
            WindowFramePixelSizeChangedEvent windowFrameResize(width, height);
            s_Window->GetWindowSpecification().FramebufferWidth = width;
            s_Window->GetWindowSpecification().FramebufferHeight = height;
            s_EventCallback(windowFrameResize);
        });

        glfwSetCursorEnterCallback((GLFWwindow*)s_Window->GetNativeWindow(), [](GLFWwindow* window, int entered) 
        {
            if (entered) {
                MouseCursorEnterEvent cursorEnter;
                s_EventCallback(cursorEnter);
            } 
            else {
                MouseCursorLeaveEvent cursorLeave;
                s_EventCallback(cursorLeave);
            }
        });

        glfwSetCursorPosCallback((GLFWwindow*)s_Window->GetNativeWindow(), [](GLFWwindow* window, double x, double y) 
        {
            MouseCursorMovedEvent cursorMove(x, y);
            s_EventCallback(cursorMove);
        });

        glfwSetScrollCallback((GLFWwindow*)s_Window->GetNativeWindow(), [](GLFWwindow* window, double xoffset, double yoffset) 
        {
            MouseScrollEvent scroll(xoffset, yoffset);
            s_EventCallback(scroll);
        });

        glfwSetMouseButtonCallback((GLFWwindow*)s_Window->GetNativeWindow(), [](GLFWwindow* window, int button, int action, int mods) 
        {
            if(action == GLFW_PRESS) {
                MouseButtonPressEvent mouseButtonPress(static_cast<MouseButton>(button));
                s_EventCallback(mouseButtonPress);
            } 

            if(action == GLFW_RELEASE) {
                MouseButtonReleaseEvent mouseButtonRelease(static_cast<MouseButton>(button));
                s_EventCallback(mouseButtonRelease);
            }
        });

        glfwSetKeyCallback((GLFWwindow*)s_Window->GetNativeWindow(), [](GLFWwindow* window, int key, int scancode, int action, int mods) 
        {
            if(action == GLFW_PRESS) {
                KeyboardKeyPressEvent keyPress((KeyCodes)key);
                s_EventCallback(keyPress);
            } 

            if(action == GLFW_RELEASE) {
                KeyboardKeyReleaseEvent keyRelease((KeyCodes)key);
                s_EventCallback(keyRelease);
            }
            
            if(action == GLFW_REPEAT) {
                KeyboardKeyRepeatEvent keyRepeat((KeyCodes)key);
                s_EventCallback(keyRepeat);
            }
        });

        glfwSetCharCallback((GLFWwindow*)s_Window->GetNativeWindow(), [](GLFWwindow* window, unsigned int codepoint) 
        {
            KeyboardKeyCharEvent keyChar(codepoint);
            s_EventCallback(keyChar);
        });        
    }

    void GLFW_EventsReceiver::PollEvents()
    {
        glfwWaitEvents();
    }

    void GLFW_EventsReceiver::SetCallbackWindow(const Ref<Window>& window, const EventCallBack & eventsCallback)
    {
        s_Window = window;
        s_EventCallback = eventsCallback;
        SetCallBacks();
    }
}