#include "asserts.hpp"
#include "renderer.hpp"
#include "opengl/opengl.hpp"

namespace IMGV::Core
{
    Reference<Texture2D> CreateTexture2D(Int32 width, Int32 height)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::None:             IMGV_ASSERT(IMGV_FALSE, "No rendering API selected"); return IMGV_NULLPTR;
            case RendererAPI::OpenGL:           return CreateRef<GL_Texture2D>(width, height);
            case RendererAPI::Vulkan:           IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return IMGV_NULLPTR;
            case RendererAPI::DirectX:          IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return IMGV_NULLPTR;
            default:                            return IMGV_NULLPTR;
        };
    }

    Reference<Texture2D> CreateTexture2D(const std::filesystem::path& path, Boolean flip)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::None:             IMGV_ASSERT(IMGV_FALSE, "No rendering API selected"); return IMGV_NULLPTR;
            case RendererAPI::OpenGL:           return CreateRef<GL_Texture2D>(path, flip);
            case RendererAPI::Vulkan:           IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return IMGV_NULLPTR;
            case RendererAPI::DirectX:          IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return IMGV_NULLPTR;
            default:                            return IMGV_NULLPTR;
        };
    }

    SubTexture2D::SubTexture2D(const Reference<Texture2D>& texture, const Vec2& min, const Vec2& max)
    {
        m_Texture = texture;
        m_TexCoords[0] = { min.x, min.y };
        m_TexCoords[1] = { max.x, min.y };
        m_TexCoords[2] = { max.x, max.y };
        m_TexCoords[3] = { min.x, max.y };
    }

    Reference<SubTexture2D> CreateSubTexture2D(const Reference<Texture2D>& texture, const Vec2& coords, const Vec2& cellSize, const Vec2& spriteSize)
    {
        Float textureWidth = static_cast<Float>(texture->GetWidth());
        Float textureHeight = static_cast<Float>(texture->GetHeight());
        Vec2 min = { (coords.x * cellSize.x) / textureWidth, (coords.y * cellSize.y) / textureHeight };
        Vec2 max = { ((coords.x + spriteSize.x) * cellSize.x) / textureWidth, ((coords.y + spriteSize.y) * cellSize.y) / textureHeight };
        return CreateRef<SubTexture2D>(texture, min, max);
    }
}