#pragma once

#include "window.hpp"
#include "keycodes.hpp"

namespace IMGV::Core
{
    class IMGV_API InputHandler
    {
        public:
            InputHandler() = default;
            virtual ~InputHandler() = default;

            virtual void TargetWindow(const Ref<Window>& window) = IMGV_NULL;
            virtual Boolean IsKeyPressed(KeyCodes keyCode) = IMGV_NULL;
            virtual Boolean IsMouseButtonPressed(MouseButton button) = IMGV_NULL;
            virtual Vec2 GetMousePosition() = IMGV_NULL;
    };

    IMGV_NODISCARD IMGV_API Ref<InputHandler> CreateInputHandler(ServiceAPIs api);
}