#include "glfw/glfw.hpp"

namespace IMGV::Core
{
    Ref<EventsReceiver> CreateEventsReceiver(ServiceAPIs api)
    {
        switch(api)
        {
            case ServiceAPIs::API_GLFW:     return CreateRef<GLFW_EventsReceiver>();
            case ServiceAPIs::API_SDL:      IMGV_ASSERT(IMGV_FALSE, "SDL is not supported yet.");
            case ServiceAPIs::API_WIN32:    IMGV_ASSERT(IMGV_FALSE, "None is not supported yet.");
            default:                        return IMGV_NULLPTR;
        }
    }
}