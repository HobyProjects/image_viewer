#include "renderer.hpp"
#include "opengl/opengl.hpp"

namespace IMGV::Core
{
    Reference<Shader> CreateShader(const String& name, const std::filesystem::path& vtxShader, const std::filesystem::path& fragShader)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::None:             IMGV_ASSERT(IMGV_FALSE, "No rendering API selected"); return IMGV_NULLPTR;
            case RendererAPI::OpenGL:           return CreateRef<GL_Shader>(name, vtxShader, fragShader);
            case RendererAPI::Vulkan:           IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return IMGV_NULLPTR;
            case RendererAPI::DirectX:          IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); return IMGV_NULLPTR;
            default:                            return IMGV_NULLPTR;
        };
    }
}