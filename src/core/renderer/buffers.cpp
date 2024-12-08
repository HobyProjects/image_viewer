#include "renderer.hpp"
#include "opengl/opengl.hpp"

namespace IMGV::Core
{
    Ref<VertexBuffer> CreateVertexBuffer(UInt32 allocatorSize)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::None:         IMGV_ASSERT(IMGV_FALSE, "No rendering API selected"); return IMGV_NULLPTR;
            case RendererAPI::OpenGL:       return CreateRef<GL_VertexBuffer>(allocatorSize);
            case RendererAPI::Vulkan:       IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return IMGV_NULLPTR;
            case RendererAPI::DirectX:      IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return IMGV_NULLPTR;
            default:                        return IMGV_NULLPTR;
        }
    }

    Ref<VertexBuffer> CreateVertexBuffer(VertexBufferData data, UInt32 size)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::None:         IMGV_ASSERT(IMGV_FALSE, "No rendering API selected"); return IMGV_NULLPTR;
            case RendererAPI::OpenGL:       return CreateRef<GL_VertexBuffer>(data, size);
            case RendererAPI::Vulkan:       IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return IMGV_NULLPTR;
            case RendererAPI::DirectX:      IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return IMGV_NULLPTR;
            default:                        return IMGV_NULLPTR;
        }
    }

    Ref<IndexBuffer> CreateIndexBuffer(IndexBufferData data, UInt32 count)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::None:         IMGV_ASSERT(IMGV_FALSE, "No rendering API selected"); return IMGV_NULLPTR;
            case RendererAPI::OpenGL:       return CreateRef<GL_IndexBuffer>(data, count);
            case RendererAPI::Vulkan:       IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return IMGV_NULLPTR;
            case RendererAPI::DirectX:      IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return IMGV_NULLPTR;
            default:                        return IMGV_NULLPTR;
        }
    }
}