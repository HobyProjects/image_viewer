#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "events_receiver.hpp"

namespace IMGV::Core
{
    class IMGV_API GLFW_EventsReceiver final : public EventsReceiver
    {
        public:
            GLFW_EventsReceiver() = default;
            virtual ~GLFW_EventsReceiver() = default;
            
            void PollEvents() override;
            virtual void SetCallbackWindow(const Reference<Window>& window, const EventCallBack& eventsCallback) override;
    };
}