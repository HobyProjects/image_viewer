#include "renderer.hpp"
#include "opengl/opengl.hpp"

namespace IMGV::Core
{
    Ref<VertexBuffer> CreateVertexBuffer(UInt32 allocatorSize)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::None:         IMGV_ASSERT(IMGV_FALSE, "No rendering API selected"); return nullptr;
            case RendererAPI::OpenGL:       return CreateRef<GL_VertexBuffer>(allocatorSize);
            case RendererAPI::Vulkan:       IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return nullptr;
            case RendererAPI::DirectX:      IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return nullptr;
            default:                        return nullptr;
        }
    }

    Ref<VertexBuffer> CreateVertexBuffer(VertexBufferData data, UInt32 size)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::None:         IMGV_ASSERT(IMGV_FALSE, "No rendering API selected"); return nullptr;
            case RendererAPI::OpenGL:       return CreateRef<GL_VertexBuffer>(data, size);
            case RendererAPI::Vulkan:       IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return nullptr;
            case RendererAPI::DirectX:      IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return nullptr;
            default:                        return nullptr;
        }
    }

    Ref<IndexBuffer> CreateIndexBuffer(IndexBufferData data, UInt32 count)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::None:         IMGV_ASSERT(IMGV_FALSE, "No rendering API selected"); return nullptr;
            case RendererAPI::OpenGL:       return CreateRef<GL_IndexBuffer>(data, count);
            case RendererAPI::Vulkan:       IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return nullptr;
            case RendererAPI::DirectX:      IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return nullptr;
            default:                        return IMGV_NULLPTR;
        }
    }
}