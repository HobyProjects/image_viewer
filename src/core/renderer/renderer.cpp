#include "renderer.hpp"
#include "opengl/opengl.hpp"

namespace IMGV::Core
{
    static RendererAPI s_RendererAPI = RendererAPI::OpenGL;

    void Renderer::Init()
    {
        switch(s_RendererAPI)
        {
            case RendererAPI::OpenGL:
            {
                GL_Renderer::Init();
                break;
            }
            case RendererAPI::Vulkan:
            {
                IMGV_ASSERT(IMGV_FALSE, "Not implemented yet");
                break;
            }
            case RendererAPI::DirectX:
            {
                IMGV_ASSERT(IMGV_FALSE, "Not implemented yet");
                break;
            }
            default:
            {
                break;
            }
        }
    }

    void Renderer::Shutdown()
    {
        switch(s_RendererAPI)
        {
            case RendererAPI::OpenGL:
            {
                GL_Renderer::Shutdown();
                break;
            }
            case RendererAPI::Vulkan:
            {
                IMGV_ASSERT(IMGV_FALSE, "Not implemented yet");
                break;
            }
            case RendererAPI::DirectX:
            {
                IMGV_ASSERT(IMGV_FALSE, "Not implemented yet");
                break;
            }
            default:
            {
                break;
            }
        }    
    }

    RendererAPI Renderer::GetAPI()
    {
        return s_RendererAPI;
    }

    void Renderer::ChangeAPI(RendererAPI api)
    {
        s_RendererAPI = api;
        //[TODO]: Implement this function to change the renderer API
    }

    void Renderer::ClearColor(const Vec4& color)
    {
        switch(s_RendererAPI)
        {
            case RendererAPI::OpenGL:
            {
                GL_Renderer::ClearColor(color);
                break;
            }
            case RendererAPI::Vulkan:
            {
                IMGV_ASSERT(IMGV_FALSE, "Not implemented yet");
                break;
            }
            case RendererAPI::DirectX:
            {
                IMGV_ASSERT(IMGV_FALSE, "Not implemented yet");
                break;
            }
            default:
            {
                break;
            }            
        }
    }

    void Renderer::Clear()
    {
        switch(s_RendererAPI)
        {
            case RendererAPI::OpenGL:
            {
                GL_Renderer::Clear();
                break;
            }
            case RendererAPI::Vulkan:
            {
                IMGV_ASSERT(IMGV_FALSE, "Not implemented yet");
                break;
            }
            case RendererAPI::DirectX:
            {
                IMGV_ASSERT(IMGV_FALSE, "Not implemented yet");
                break;
            }
            default:
            {
                break;
            }            
        }
    }

    void Renderer::SetViewport(UInt32 x, UInt32 y, UInt32 width, UInt32 height)
    {
        switch(s_RendererAPI)
        {
            case RendererAPI::OpenGL:
            {
                GL_Renderer::SetViewport(x, y, width, height);
                break;
            }
            case RendererAPI::Vulkan:
            {
                IMGV_ASSERT(IMGV_FALSE, "Not implemented yet");
                break;
            }
            case RendererAPI::DirectX:
            {
                IMGV_ASSERT(IMGV_FALSE, "Not implemented yet");
                break;
            }
            default:
            {
                break;
            }            
        }
    }
}