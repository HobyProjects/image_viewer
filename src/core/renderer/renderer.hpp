#pragma once

#include "typedef.hpp"

namespace IMGV::Core
{
    enum class RendererAPI
    {
        None        = IMGV_BIT(0),
        OpenGL      = IMGV_BIT(1),
        Vulkan      = IMGV_BIT(2),
        DirectX     = IMGV_BIT(3)
    };

    class IMGV_API Renderer
    {
        private:
            Renderer() = default;
            ~Renderer() = default;

        public:
            static void Init();
            static void Shutdown();

            static RendererAPI GetAPI();
            static void ChangeAPI(RendererAPI api);
            static void Clear();
            static void ClearColor(const Vec4& color);
            static void SetViewport(UInt32 x, UInt32 y, UInt32 width, UInt32 height);
    };
}