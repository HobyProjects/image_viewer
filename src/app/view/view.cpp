#include "view.hpp"

namespace IMGV::App
{
    static Reference<CameraController> s_CameraController{IMGV_NULLPTR};

    ViewLayer::ViewLayer(const Reference<IMGV::Core::Window>& window, const Reference<IMGV::Core::UILayer>& uiLayer)
    {
        m_Window = window;
        m_UILayer = uiLayer;
        s_CameraController = CreateRef<CameraController>();
    }

    void ViewLayer::OnAttach()
    {
        IMGV::Core::FrameBufferSpecification frameSpec{};
        frameSpec.Width = 1280;
        frameSpec.Height = 720;
        m_Framebuffer = IMGV::Core::CreateFrameBuffer(frameSpec);
    }

    void ViewLayer::OnDetach()
    {
    }

    void ViewLayer::OnUpdate(IMGV::Core::Timer deltaTime)
    {
        //s_CameraController->OnUpdate(deltaTime);
        IMGV::Core::FrameBufferSpecification& frameSpec = m_Framebuffer->GetFrameSpecification();
        if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (frameSpec.Width != m_ViewportSize.x || frameSpec.Height != m_ViewportSize.y))
            m_Framebuffer->ResizeFrame((UInt32)m_ViewportSize.x, (UInt32)m_ViewportSize.y);

        m_Framebuffer->Bind();

        IMGV::Core::Renderer::ClearColor({0.243, 0.243, 0.243, 1.0f});
        IMGV::Core::Renderer::Clear();

        m_Framebuffer->Unbind();
    }

    void ViewLayer::OnEvent(IMGV::Core::Event& event)
    {
    }

    void ViewLayer::OnUIRendering()
    {
    }


}