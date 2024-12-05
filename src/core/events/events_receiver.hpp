#pragma once

#include "window.hpp"
#include "window_events.hpp"
#include "keyboard_events.hpp"
#include "mouse_events.hpp"

namespace IMGV::Core
{
    class IMGV_API EventsReceiver
    {
        public:
            EventsReceiver() = default;
            virtual ~EventsReceiver() = default;

            virtual void PollEvents() = IMGV_NULL;
            virtual void SetCallbackWindow(const Ref<Window>& window, const EventCallBack& callBack) = IMGV_NULL;
    };

    IMGV_API Ref<EventsReceiver> CreateEventsReceiver(ServiceAPIs api);
}