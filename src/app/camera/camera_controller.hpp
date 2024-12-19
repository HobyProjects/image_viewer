#pragma once

#include "core.hpp"

namespace IMGV::App
{
    class CameraController
    {
        public:
            CameraController(const Reference<IMGV::Core::Window>& window);
            ~CameraController() = default;

            void OnUpdate(IMGV::Core::Timer deltaTime);
            void OnEvent(IMGV::Core::Event& event);
            void OnWindowResize(UInt32 width, UInt32 height);
            void SetZoomLevel(Float zoomLevel) { m_ZoomLevel = zoomLevel; }

        private:
            Boolean OnMouseWheelEvent(IMGV::Core::MouseScrollEvent& event);
            Boolean OnWindowResizeEvent(IMGV::Core::WindowResizeEvent& event);

        private:
            IMGV::Core::Camera2D m_Camera{};
            IMGV::Core::CameraBounds m_Bounds{};

            Float m_ZoomLevel{1.0f};
            Float m_TranslationSpeed{100.0f};

            Double m_MouseY{0.0};
            Double m_MouseX{0.0};
            Float m_Sensitivity{10.0f};

            UInt32 m_WindowWidth{IMGV_NULL};
            UInt32 m_WindowHeight{IMGV_NULL};
    };  
}