#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_internal.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "layer.hpp"
#include "window.hpp"

namespace IMGV::Core
{
    enum class UITheme
    {
        Dark    = 0,   
        Light   = 1,    
        Classic = 2     
    };

    class UILayer final : public Layer
    {
        public:
            UILayer(Ref<Window> window, UITheme theme = UITheme::Dark);
            virtual ~UILayer() = default;

            virtual void OnAttach() override;
            virtual void OnDetach() override;
            virtual void OnEvent(Event& event) override;

            void Begin();
            void End();

            void AllowEvents(Boolean allowEvents);
            void SetTheme(UITheme theme);

        private:
            void SetDarkTheme();
            void SetLightTheme();
            void SetClassicTheme();

        private:
            Ref<Window> m_Window{IMGV_NULLPTR};
            Boolean m_AllowEvents{IMGV_FALSE};
            UITheme m_Theme{UITheme::Dark};
    };    
}