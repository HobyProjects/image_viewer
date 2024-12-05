#include "glfw/glfw.hpp"

namespace IMGV::Core
{
    Ref<InputHandler> CreateInputHandler(ServiceAPIs api)
    {
        switch(api)
        {
            case ServiceAPIs::API_GLFW:     return CreateRef<GLFW_InputHandler>();
            case ServiceAPIs::API_SDL:      IMGV_ASSERT(IMGV_FALSE, "SDL is not supported yet.");
            case ServiceAPIs::API_WIN32:    IMGV_ASSERT(IMGV_FALSE, "Win32 is not supported yet.");
            default:                        return nullptr;
        };
    }
}