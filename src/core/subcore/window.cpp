#include "glfw/glfw.hpp"

namespace IMGV::Core
{
    static Boolean s_ServiceAPIInitialized = IMGV_FALSE;
    static Ref<ServiceAPI> s_ServiceAPI = IMGV_NULLPTR;

    Ref<ServiceAPI> GetPlatformServiceAPI()
    {
        #ifdef IMGV_PLATFORM_WINDOWS
            //TODO: This should Win32 API, for now it's GLFW
            if(!s_ServiceAPIInitialized)
            {
                s_ServiceAPI = CreateRef<GLFW_ServiceAPI>();
                s_ServiceAPIInitialized = IMGV_TRUE;
            }
            return s_ServiceAPI;
        #endif

        #ifdef IMGV_PLATFORM_LINUX
            //FIXME: I don't know what is best API for Linux
            if(!s_ServiceAPIInitialized)
            {
                s_ServiceAPI = CreateRef<GLFW_ServiceAPI>();
                s_ServiceAPIInitialized = IMGV_TRUE;
            }
            return s_ServiceAPI;
        #endif

        #ifdef IMGV_PLATFORM_MAC
            //FIXME: I don't know what is best API for Mac
            if(!s_ServiceAPIInitialized)
            {
                s_ServiceAPI = CreateRef<GLFW_ServiceAPI>();
                s_ServiceAPIInitialized = IMGV_TRUE;
            }
            return s_ServiceAPI;
        #endif
    }

    Ref<Window> CreateWindow(const String& title, ServiceAPIs api)
    {
        switch(api)
        {
            case ServiceAPIs::API_GLFW:             return CreateRef<GLFW_Window>(title);
            case ServiceAPIs::API_SDL:              IMGV_ASSERT(IMGV_FALSE, "SDL is not supported yet!");
            case ServiceAPIs::API_WIN32:            IMGV_ASSERT(IMGV_FALSE, "Win32 is not supported yet!");
            default:                                return IMGV_NULLPTR;
        }
    };
}