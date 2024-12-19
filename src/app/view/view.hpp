#pragma once 

#include "core.hpp"
#include "camera_controller.hpp"

namespace IMGV::App
{
    class ViewLayer final : public IMGV::Core::Layer
    {
        public:
            ViewLayer() = default;
            ViewLayer(const Reference<IMGV::Core::Window>& window, const Reference<IMGV::Core::UILayer>& uiLayer);
            virtual ~ViewLayer() = default;

            virtual void OnAttach() override;
            virtual void OnDetach() override;

            virtual void OnUpdate(IMGV::Core::Timer deltaTime) override;
            virtual void OnEvent(IMGV::Core::Event& event) override;
            virtual void OnUIRendering() override;
        
        private:
            Reference<IMGV::Core::Window> m_Window{IMGV_NULLPTR};
            Reference<IMGV::Core::UILayer> m_UILayer{IMGV_NULLPTR};
            Reference<IMGV::Core::FrameBuffer> m_Framebuffer{IMGV_NULLPTR};

            Vec2 m_ViewportSize{1280.0f, 720.0f};
            Boolean m_IsViewportFocused{IMGV_FALSE}, m_IsViewportHovered{IMGV_FALSE};

            IMGV::Core::Entity* m_SquareEntity;
    };
}