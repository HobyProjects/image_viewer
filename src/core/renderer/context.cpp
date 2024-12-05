#include "renderer.hpp"
#include "opengl/opengl.hpp"

namespace IMGV::Core
{
    Ref<Context> IMGV::Core::CreateContext(IMGV_Window window)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::None:         IMGV_ASSERT(IMGV_FALSE, "No rendering API selected"); return nullptr;
            case RendererAPI::OpenGL:       return CreateRef<GL_Context>(window);
            case RendererAPI::Vulkan:       IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return nullptr;
            case RendererAPI::DirectX:      IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return nullptr;
            default:                        return nullptr;
        }
    }
}