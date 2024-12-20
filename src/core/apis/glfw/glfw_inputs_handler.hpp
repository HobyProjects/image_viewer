#pragma once

#include "inputs_handler.hpp"

namespace IMGV::Core
{
    class IMGV_API GLFW_InputHandler final : public InputHandler
    {
        public:
            GLFW_InputHandler() = default;
            virtual ~GLFW_InputHandler() = default;

            virtual void TargetWindow(const Reference<Window>& window) override;
            virtual Boolean IsKeyPressed(KeyCodes keyCode) override;
            virtual Boolean IsMouseButtonPressed(MouseButton button) override;
            virtual Vec2 GetMousePosition() override;
    };
}