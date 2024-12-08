#pragma once

#include "renderer.hpp"
#include "context.hpp"
#include "typedef.hpp"

namespace IMGV::Core
{
    enum class WindowState
    {
        Minimized       = 0,
        Maximized       = 1,
        Normal          = 2
    };

    struct IMGV_API WindowSpecification
    {
        UInt32 Width{0};                           
        UInt32 Height{0};                          
        Boolean IsVSyncEnabled{IMGV_NULL};           
        Boolean IsActive{IMGV_NULL};                 
        Boolean IsFocused{IMGV_NULL};                
        UInt32 RedColorBits{8};               
        UInt32 GreenColorBits{8};             
        UInt32 BlueColorBits{8};              
        UInt32 AlphaColorBits{8};             
        UInt32 DepthColorBits{24};            
        UInt32 StencilColorBits{8};           
        UInt32 RefreshRate{60};               
        UInt32 FixedWidth{IMGV_NULL};           
        UInt32 FixedHeight{IMGV_NULL};          
        UInt32 MinWidth{1280};                
        UInt32 MinHeight{720};                
        UInt32 PosX{IMGV_NULL};                 
        UInt32 PosY{IMGV_NULL};                 
        Int32 FramebufferWidth{IMGV_NULL};      
        Int32 FramebufferHeight{IMGV_NULL};     
        WindowState WindowState{WindowState::Normal};   
        String Title{String()};
    };

    enum class ServiceAPIs
    {
        API_None        = IMGV_BIT(0),
        API_GLFW        = IMGV_BIT(1),
        API_SDL         = IMGV_BIT(2),
        API_WIN32       = IMGV_BIT(3),
    };

    class IMGV_API ServiceAPI
    {
        public:
            ServiceAPI() = default;
            virtual ~ServiceAPI() = default;

            virtual Boolean Init() = IMGV_NULL;
            virtual void Shutdown() = IMGV_NULL;
            virtual ServiceAPIs GetAPI() = IMGV_NULL;
    };

    class Window
    {
        public:
            Window() = default;
            virtual ~Window() = default;

            virtual IMGV_Window GetNativeWindow() const = IMGV_NULL;
            virtual WindowSpecification& GetWindowSpecification() = IMGV_NULL;
            virtual Ref<Context> GetContext() = IMGV_NULL;
            virtual void SwapBuffers() = IMGV_NULL;
    };

    IMGV_NODISCARD IMGV_API Ref<ServiceAPI> GetPlatformServiceAPI();
    IMGV_NODISCARD IMGV_API Ref<Window> CreateWindow(const String& title, ServiceAPIs api);
}