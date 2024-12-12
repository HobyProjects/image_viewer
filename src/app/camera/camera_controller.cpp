#include "camera_controller.hpp"

namespace IMGV::App
{
    CameraController::CameraController(const Ref<IMGV::Core::Window>& window)
    {
        m_WindowWidth       = window->GetWindowSpecification().Width;
        m_WindowHeight      = window->GetWindowSpecification().Height;
        Float aspectRatio   = (Float)m_WindowWidth / (Float)m_WindowHeight;
        m_Camera.SetAspectRatio((Float)m_WindowWidth / (Float)m_WindowHeight);
        m_Bounds = { -aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
    }

    void CameraController::OnUpdate(IMGV::Core::Timer deltaTime)
    {
        // Since this is a image viewer, we don't need to update the camera
    }

    void CameraController::OnEvent(IMGV::Core::Event& event)
    {
        IMGV::Core::EventHandler handler(event);
        handler.Dispatch<IMGV::Core::MouseScrollEvent>(IMGV_EVENT_CALLBACK(CameraController::OnMouseWheelEvent));
        handler.Dispatch<IMGV::Core::WindowResizeEvent>(IMGV_EVENT_CALLBACK(CameraController::OnWindowResizeEvent));
    }

    void CameraController::OnWindowResize(UInt32 width, UInt32 height)
    {
        m_WindowWidth       = width;
        m_WindowHeight      = height;
        Float aspectRatio   = (Float)width / (Float)height;
        m_Camera.SetAspectRatio(aspectRatio);

        m_Bounds = { -aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
        m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
    }

    Boolean CameraController::OnMouseWheelEvent(IMGV::Core::MouseScrollEvent& event)
    {
        m_ZoomLevel -= event.GetMouseScrollOffsetY();
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        return IMGV_FALSE;
    }

    Boolean CameraController::OnWindowResizeEvent(IMGV::Core::WindowResizeEvent& event)
    {
        OnWindowResize(event.GetWidth(), event.GetHeight());
        return IMGV_FALSE;
    }
}