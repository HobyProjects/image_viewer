#pragma once

#include "base.hpp"
#include "typedef.hpp"
#include "vertex_array.hpp"
#include "buffers.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "camera_2d.hpp"

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

            static void Restart();

        public:
            static void Init();
            static void Shutdown();

            static RendererAPI GetAPI();
            static void ChangeAPI(RendererAPI api);
            static void Clear();
            static void ClearColor(const Vec4& color);
            static void SetViewport(UInt32 x, UInt32 y, UInt32 width, UInt32 height);

            static void Begin(const Camera2D& camera, const Mat4& transform);
            static void End();
            static void Flush();

            static void DrawQuad(const Vec2& position, const Vec2& size, const Vec4& color);
            static void DrawQuad(const Vec2& position, const Vec2& size, const Vec4& color, Float rotation);
            static void DrawQuad(const Vec2& position, const Vec2& size, const Reference<Texture2D>& texture);
            static void DrawQuad(const Vec2& position, const Vec2& size, const Reference<Texture2D>& texture, Float rotation);
            static void DrawQuad(const Vec2& position, const Vec2& size, const Vec4& color, const Reference<Texture2D>& texture, Float tilingFactor = 1.0f);
            static void DrawQuad(const Vec2& position, const Vec2& size, const Vec4& color, const Reference<Texture2D>& texture, Float rotation = 1.0f, Float tilingFactor = 1.0f);
            static void DrawQuad(const Vec2& position, const Vec2& size, const glm::vec4& color, const Reference<SubTexture2D>& texture, Float rotation, Float tilingFactor = 1.0f);

            static void DrawQuad(const Mat4& transform, const Vec4& color);
            static void DrawQuad(const Mat4& transform, const Reference<Texture2D>& texture, const Vec4& tint = Vec4(1.0f), Float tilingFactor = 1.0f);
            static void DrawQuad(const Mat4& transform, const Reference<SubTexture2D>& texture, const Vec4& tint = Vec4(1.0f), Float tilingFactor = 1.0f);

            struct Status 
            {
                UInt32 DrawCount{IMGV_NULL};
                UInt32 QuadCount{IMGV_NULL};
            };

            static const Status& RenderingStatus();
            static void StatusReset();
    };
}