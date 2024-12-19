#include "application.hpp"

namespace IMGV::App
{
    static Application* s_Application = IMGV_NULLPTR;

    Application::Application()
    {
        m_Window = IMGV::Core::CreateWindow("Image Viewer", IMGV::Core::ServiceAPIs::API_GLFW);
        m_LayerStack = CreateRef<IMGV::Core::LayerStack>();
        m_UILayer = CreateRef<IMGV::Core::UILayer>(m_Window);
        m_EventsReceiver = IMGV::Core::CreateEventsReceiver(IMGV::Core::ServiceAPIs::API_GLFW);
        m_EventsReceiver->SetCallbackWindow(m_Window, IMGV_EVENT_CALLBACK(Application::OnEvent));
        IMGV::Core::Renderer::Init();

        PushOverlay(m_UILayer);
        s_Application = this;
    }

    Application::~Application()
    {
        IMGV::Core::Renderer::Shutdown();
    }

    void Application::Run()
    {
        while(m_Window->GetWindowSpecification().IsActive)
        {
            if(m_Window->GetWindowSpecification().WindowState != IMGV::Core::WindowState::Minimized)
            {
                Float currentTime = (Float)glfwGetTime(); //[TODO]: We need to create our own timer class.
                IMGV::Core::Timer deltaTime = currentTime - m_Timer;
                m_Timer = currentTime;

                for(auto& layer : *m_LayerStack)
                {
                    layer->OnUpdate(deltaTime);
                }
            }

            m_UILayer->Begin();

            for(auto& layer : *m_LayerStack)
            {
                layer->OnUIRendering();
            }

            m_UILayer->End();

            m_Window->SwapBuffers();
            m_EventsReceiver->PollEvents();
        }
    }

    void Application::OnEvent(IMGV::Core::Event& event)
    {
        IMGV::Core::EventHandler handler(event);
        handler.Dispatch<IMGV::Core::WindowCloseEvent>(IMGV_EVENT_CALLBACK(Application::OnWindowClose));
        handler.Dispatch<IMGV::Core::WindowResizeEvent>(IMGV_EVENT_CALLBACK(Application::OnWindowResize));

        for(auto it = m_LayerStack->rbegin(); it != m_LayerStack->rend(); ++it)
        {
            if(event.Handled)
            {
                break;
            }

            (*it)->OnEvent(event);
        }
    }

    Boolean Application::OnWindowClose(IMGV::Core::WindowCloseEvent& windowClose)
    {
        m_Window->GetWindowSpecification().IsActive = IMGV_FALSE;
        return IMGV_TRUE;
    }

    Boolean Application::OnWindowResize(IMGV::Core::WindowResizeEvent& windowResize)
    {
        if(m_Window->GetWindowSpecification().WindowState != IMGV::Core::WindowState::Minimized)
        {
            IMGV::Core::Renderer::SetViewport(0, 0, windowResize.GetWidth(), windowResize.GetHeight());
        }

        return IMGV_FALSE;
    }

    void Application::PushLayer(Reference<IMGV::Core::Layer> layer)
    {
        layer->OnAttach();
        m_LayerStack->PushLayer(layer);
    }

    void Application::PushOverlay(Reference<IMGV::Core::Layer> overlay)
    {
        overlay->OnAttach();
        m_LayerStack->PushOverlay(overlay);
    }

    IMGV_Window Application::GetWindow()
    {
        if(s_Application != IMGV_NULLPTR)
        {
            return s_Application->m_Window->GetNativeWindow();
        }

        IMGV_ASSERT(IMGV_FALSE, "Application instance is null.");
        return IMGV_NULLPTR;
    }

    Application* Application::GetApplication()
    {
        return s_Application;
    }
}