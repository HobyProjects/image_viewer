#pragma once

#include "core.hpp"

namespace IMGV::App
{
    class Application
    {
        public:
            Application();
            ~Application();

            void Run();
            void OnEvent(IMGV::Core::Event& events);
            void PushLayer(Reference<IMGV::Core::Layer> layer);
            void PushOverlay(Reference<IMGV::Core::Layer> overlay);

            static Application* GetApplication();
            static IMGV_Window GetWindow();

        private:
            Boolean OnWindowClose(IMGV::Core::WindowCloseEvent& windowClose);
            Boolean OnWindowResize(IMGV::Core::WindowResizeEvent& windowResize);

        private:
            Reference<IMGV::Core::Window>         m_Window{IMGV_NULLPTR};
            Reference<IMGV::Core::EventsReceiver> m_EventsReceiver{IMGV_NULLPTR};
            IMGV::Core::Timer m_Timer{0.0f};

            Reference<IMGV::Core::LayerStack>     m_LayerStack{IMGV_NULLPTR};
            Reference<IMGV::Core::UILayer>        m_UILayer{IMGV_NULLPTR};
    };
}