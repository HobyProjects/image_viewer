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
            void PushLayer(Ref<IMGV::Core::Layer> layer);
            void PushOverlay(Ref<IMGV::Core::Layer> overlay);

            static Application* GetApplication();
            static IMGV_Window GetWindow();

        private:
            Boolean OnWindowClose(IMGV::Core::WindowCloseEvent& windowClose);
            Boolean OnWindowResize(IMGV::Core::WindowResizeEvent& windowResize);

        private:
            Ref<IMGV::Core::Window>         m_Window{IMGV_NULLPTR};
            Ref<IMGV::Core::LayerStack>     m_LayerStack{IMGV_NULLPTR};
            Ref<IMGV::Core::UILayer>        m_UILayer{IMGV_NULLPTR};
            Ref<IMGV::Core::EventsReceiver> m_EventsReceiver{IMGV_NULLPTR};
            IMGV::Core::Timer m_Timer{0.0f};
    };
}