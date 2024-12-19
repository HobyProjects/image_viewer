#include "renderer.hpp"
#include "opengl/opengl.hpp"

namespace IMGV::Core
{
    static const UInt32 MAX_QUADS                 = 20000;
    static const UInt32 MAX_VERTICES              = MAX_QUADS * 4;
    static const UInt32 MAX_INDICES               = MAX_QUADS * 6;
    static const UInt32 MAX_TEXTURE_SLOTS         = 32;
    static const UInt32 MAX_QUAD_VERTEX_COUNT     = 4;
    static const Vec4 DEFAULT_COLOR               = { 1.0f, 1.0f, 1.0f, 1.0f };
    static const Vec2 DEFAULT_TEX_COORDS[]        = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    static RendererAPI s_RendererAPI              = RendererAPI::OpenGL;

    struct Vertex 
    {
		Vec3 Position;
		Vec4 Color;
		Vec2 TexCoords;
		Float TexIndex;
		Float TilingFactor;
	};

    struct BatchData 
    {
        Reference<VertexArray> QuadVAO{ IMGV_NULLPTR };
        Reference<VertexBuffer> QuadVBO{ IMGV_NULLPTR };
        Reference<IndexBuffer> QuadIBO{ IMGV_NULLPTR };

        Reference<Texture2D> PlainTexture{ IMGV_NULLPTR };
        UInt32 PlainTextureSlot{ IMGV_NULL };
        UInt32 IndexCount{ IMGV_NULL };

        Vertex* QuadBuffer{ IMGV_NULLPTR };
        Vertex* QuadBufferPtr{ IMGV_NULLPTR };

        Reference<Shader> BatchShader{ IMGV_NULLPTR };
        std::array<Reference<Texture2D>, MAX_TEXTURE_SLOTS> TextureSlots;
        UInt32 TextureSlotIndex{ 1 };

        Renderer::Status RenderingStatus;
        Vec4 QuadVertexPositions[MAX_QUAD_VERTEX_COUNT];

    }; static BatchData s_BatchData;

    void Renderer::Restart() 
    {
        End();
        s_BatchData.QuadBufferPtr       = s_BatchData.QuadBuffer;
        s_BatchData.IndexCount          = 0;
        s_BatchData.TextureSlotIndex    = 1;
    }

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

        s_BatchData.QuadBuffer = new Vertex[MAX_VERTICES];
        s_BatchData.QuadVAO = CreateVertexArray();
        s_BatchData.QuadVAO->Bind();
        {
            s_BatchData.QuadVBO = CreateVertexBuffer(MAX_VERTICES * sizeof(Vertex));
            s_BatchData.QuadVBO->Bind();
            {
                s_BatchData.QuadVBO->SetLayout({
                    {"u_Position", BufferComponents::XYZ, BufferStride::F3, IMGV_FALSE },
                    {"u_Color", BufferComponents::RGBA, BufferStride::F4, IMGV_FALSE },
                    {"u_TexCoords", BufferComponents::UV, BufferStride::F2, IMGV_FALSE },
                    {"u_TexIndex", BufferComponents::X, BufferStride::F1, IMGV_FALSE },
                    {"u_TilingFactor", BufferComponents::X, BufferStride::F1, IMGV_FALSE }
                });

                s_BatchData.QuadVAO->EmplaceVtxBuffer(s_BatchData.QuadVBO);

                UInt32 indices[MAX_INDICES];
                UInt32 offset = 0;
                for(UInt32 i = 0; i < MAX_INDICES; i += 6)
                {
                    indices[i + 0] = offset + 0;
                    indices[i + 1] = offset + 1;
                    indices[i + 2] = offset + 2;
                    indices[i + 3] = offset + 2;
                    indices[i + 4] = offset + 3;
                    indices[i + 5] = offset + 0;
                    offset += 4;
                }

                s_BatchData.QuadIBO = CreateIndexBuffer(indices, MAX_INDICES);
                s_BatchData.QuadVAO->EmplaceIdxBuffer(s_BatchData.QuadIBO);

                for(UInt32 i = 0; i < MAX_TEXTURE_SLOTS; i++)
                    s_BatchData.TextureSlots[i] = nullptr;

                s_BatchData.PlainTexture = CreateTexture2D(1, 1);
                s_BatchData.TextureSlots[0] = s_BatchData.PlainTexture;

                //TODO: Create a Asset Manager to load shaders
                s_BatchData.BatchShader = CreateShader("Renderer2D-GL-DefaultShaders", "Assets/Shaders/Renderer2D-Vertex.glsl", "Assets/Shaders/Renderer2D-Fragment.glsl");

                s_BatchData.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
                s_BatchData.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
                s_BatchData.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
                s_BatchData.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
            }
        }

        s_BatchData.QuadVAO->Unbind();
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

        delete[] s_BatchData.QuadBuffer;   
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

    void Renderer::Begin(const Camera2D& camera, const Mat4& transform)
    {
        s_BatchData.BatchShader->Bind();
        s_BatchData.BatchShader->SetUniform("u_MVP", camera.GetViewProjection());

        UInt32 texture_location = s_BatchData.BatchShader->GetUniformLocation("u_Textures");
        Int32 samplers[MAX_TEXTURE_SLOTS];
        for(UInt32 i = 0; i < MAX_TEXTURE_SLOTS; i++) 
            samplers[i] = i;

        switch(Renderer::GetAPI())
        {
            case RendererAPI::None:         IMGV_ASSERT(IMGV_FALSE, "No rendering API selected"); break;
            case RendererAPI::OpenGL:       glUniform1iv(texture_location, MAX_TEXTURE_SLOTS, samplers); break;
            case RendererAPI::Vulkan:       IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); break;
            case RendererAPI::DirectX:      IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); break;
            default:                        break;
        };

        s_BatchData.QuadBufferPtr = s_BatchData.QuadBuffer;
    }

    void Renderer::End()
    {
        UInt32 size = (UInt8*)s_BatchData.QuadBufferPtr - (UInt8*)s_BatchData.QuadBuffer;
        s_BatchData.QuadVBO->Bind();
        s_BatchData.QuadVBO->SetData(s_BatchData.QuadBuffer, size);
        Flush();
    }

    void Renderer::Flush()
    {
        for(UInt32 i = 0; i < s_BatchData.TextureSlotIndex; i++) 
        {
            s_BatchData.TextureSlots[i]->Bind(i);
		}

        s_BatchData.QuadVAO->Bind();

        switch(Renderer::GetAPI())
        {
            case RendererAPI::None:         IMGV_ASSERT(IMGV_FALSE, "No rendering API selected"); break;
            case RendererAPI::OpenGL:       glDrawElements(GL_TRIANGLES, s_BatchData.IndexCount, GL_UNSIGNED_INT, nullptr); break;
            case RendererAPI::Vulkan:       IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); break;
            case RendererAPI::DirectX:      IMGV_ASSERT(IMGV_FALSE, "Not implemented yet"); break;
            default:                        break;
        };

        s_BatchData.RenderingStatus.DrawCount++;
		s_BatchData.IndexCount = 0;
		s_BatchData.TextureSlotIndex = 1;
    }

    void Renderer::DrawQuad(const Vec2& position, const Vec2& size, const Vec4& color)
    {
        DrawQuad(position, size, color, s_BatchData.PlainTexture, 0.0f, 1.0f);
    }

    void Renderer::DrawQuad(const Vec2& position, const Vec2& size, const Vec4& color, Float rotation)
    {
        DrawQuad(position, size, color, s_BatchData.PlainTexture, rotation, 1.0f);
    }

    void Renderer::DrawQuad(const Vec2& position, const Vec2& size, const Reference<Texture2D>& texture)
    {
        DrawQuad(position, size, Vec4(1.0f), texture, 0.0f, 1.0f);
    }

    void Renderer::DrawQuad(const Vec2& position, const Vec2& size, const Reference<Texture2D>& texture, Float rotation)
    {
        DrawQuad(position, size, Vec4(1.0f), texture, rotation, 1.0f);
    }

    void Renderer::DrawQuad(const Vec2& position, const Vec2 & size, const Vec4& color, const Reference<Texture2D>& texture, Float tilingFactor)
    {
        DrawQuad(position, size, color, texture, 0.0f, tilingFactor);
    }

    void Renderer::DrawQuad(const Vec2& position, const Vec2& size, const Vec4& color, const Reference<Texture2D>& texture, Float rotation, Float tilingFactor)
    {
        if (s_BatchData.IndexCount >= MAX_INDICES || s_BatchData.TextureSlotIndex >= MAX_TEXTURE_SLOTS) 
        {
            Restart();
        }

        Float texture_index = 0.0f;
        for(UInt32 i = 1; i < s_BatchData.TextureSlotIndex; i++) 
        {
			if (s_BatchData.TextureSlots[i] == texture) 
            {
				texture_index = static_cast<Float>(i);
				break;
			}
		}

        if(texture_index == 0.0f) 
        {
			texture_index = static_cast<Float>(s_BatchData.TextureSlotIndex);
			s_BatchData.TextureSlots[s_BatchData.TextureSlotIndex] = texture;
			s_BatchData.TextureSlotIndex++;
		}

        Mat4 transform = glm::translate(Mat4(1.0f), { position.x, position.y, 0.0f }) * glm::rotate(Mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(Mat4(1.0f), { size.x, size.y, 1.0f });

		for(UInt32 i = 0; i < MAX_QUAD_VERTEX_COUNT; i++) 
        {
			s_BatchData.QuadBufferPtr->Position             = transform * s_BatchData.QuadVertexPositions[i];
			s_BatchData.QuadBufferPtr->Color                = color;
			s_BatchData.QuadBufferPtr->TexCoords            = DEFAULT_TEX_COORDS[i];
			s_BatchData.QuadBufferPtr->TexIndex             = texture_index;
			s_BatchData.QuadBufferPtr->TilingFactor         = tilingFactor;
			s_BatchData.QuadBufferPtr++;
		}

		s_BatchData.IndexCount += 6;
		s_BatchData.RenderingStatus.QuadCount++;
    }

    void Renderer::DrawQuad(const Vec2& position, const Vec2& size, const glm::vec4& color, const Reference<SubTexture2D>& texture, Float rotation, Float tilingFactor)
    {
        if (s_BatchData.IndexCount >= MAX_INDICES || s_BatchData.TextureSlotIndex >= MAX_TEXTURE_SLOTS) 
        {
			Restart();
		}

        const Vec2* tex_coords = texture->GetTextureCoords();
        Float texture_index = 0.0f;

        for (UInt32 i = 1; i < s_BatchData.TextureSlotIndex; i++) 
        {
            if (s_BatchData.TextureSlots[i] == texture->GetTexturePtr()) {
                texture_index = static_cast<Float>(i);
                break;
            }
        }

        if(texture_index == 0.0f) 
        {
			texture_index = static_cast<Float>(s_BatchData.TextureSlotIndex);
			s_BatchData.TextureSlots[s_BatchData.TextureSlotIndex] = texture->GetTexturePtr();
			s_BatchData.TextureSlotIndex++;
		}

        Mat4 transform = glm::translate(Mat4(1.0f), { position.x, position.y, 0.0f }) * glm::rotate(Mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(Mat4(1.0f), { size.x, size.y, 1.0f });

		for (UInt32 i = 0; i < MAX_QUAD_VERTEX_COUNT; i++) 
        {
			s_BatchData.QuadBufferPtr->Position         = transform * s_BatchData.QuadVertexPositions[i];
			s_BatchData.QuadBufferPtr->Color            = color;
			s_BatchData.QuadBufferPtr->TexCoords        = tex_coords[i];
			s_BatchData.QuadBufferPtr->TexIndex         = texture_index;
			s_BatchData.QuadBufferPtr->TilingFactor     = tilingFactor;
			s_BatchData.QuadBufferPtr++;
		}

		s_BatchData.IndexCount += 6;
		s_BatchData.RenderingStatus.QuadCount++;
    }

    void Renderer::DrawQuad(const Mat4& transform, const Vec4& color)
    {
        DrawQuad(transform, s_BatchData.PlainTexture, color, 1.0f);
    }

    void Renderer::DrawQuad(const Mat4 & transform, const Reference<Texture2D>& texture, const Vec4 & tint, Float tilingFactor)
    {
        if (s_BatchData.IndexCount >= MAX_INDICES || s_BatchData.TextureSlotIndex >= MAX_TEXTURE_SLOTS) {
            Restart();
        }

        Float texture_index = 0.0f;
        for (uint32_t i = 1; i < s_BatchData.TextureSlotIndex; i++) 
        {
            if (s_BatchData.TextureSlots[i] == texture) 
            {
                texture_index = static_cast<Float>(i);
                break;
            }
        }

        if (texture_index == 0.0f) 
        {
            texture_index = static_cast<Float>(s_BatchData.TextureSlotIndex);
            s_BatchData.TextureSlots[s_BatchData.TextureSlotIndex] = texture;
            s_BatchData.TextureSlotIndex++;
        }

        for (UInt32 i = 0; i < MAX_QUAD_VERTEX_COUNT; i++) 
        {
            s_BatchData.QuadBufferPtr->Position         = transform * s_BatchData.QuadVertexPositions[i];
            s_BatchData.QuadBufferPtr->Color            = tint;
            s_BatchData.QuadBufferPtr->TexCoords        = DEFAULT_TEX_COORDS[i];
            s_BatchData.QuadBufferPtr->TexIndex         = texture_index;
            s_BatchData.QuadBufferPtr->TilingFactor     = tilingFactor;
            s_BatchData.QuadBufferPtr++;
        }

        s_BatchData.IndexCount += 6;
        s_BatchData.RenderingStatus.QuadCount++;
    }

    void Renderer::DrawQuad(const Mat4& transform, const Reference<SubTexture2D>& texture, const Vec4& tint, Float tilingFactor)
    {
        if (s_BatchData.IndexCount >= MAX_INDICES || s_BatchData.TextureSlotIndex >= MAX_TEXTURE_SLOTS) 
        {
            Restart();
        }

        const glm::vec2* tex_coords = texture->GetTextureCoords();
        float texture_index = 0.0f;

        for (uint32_t i = 1; i < s_BatchData.TextureSlotIndex; i++) 
        {
            if (s_BatchData.TextureSlots[i] == texture->GetTexturePtr()) 
            {
                texture_index = static_cast<float>(i);
                break;
            }
        }

        if (texture_index == 0.0f) 
        {
            texture_index = static_cast<float>(s_BatchData.TextureSlotIndex);
            s_BatchData.TextureSlots[s_BatchData.TextureSlotIndex] = texture->GetTexturePtr();
            s_BatchData.TextureSlotIndex++;
        }


        for (uint32_t i = 0; i < MAX_QUAD_VERTEX_COUNT; i++) 
        {
            s_BatchData.QuadBufferPtr->Position             = transform * s_BatchData.QuadVertexPositions[i];
            s_BatchData.QuadBufferPtr->Color                = tint;
            s_BatchData.QuadBufferPtr->TexCoords            = tex_coords[i];
            s_BatchData.QuadBufferPtr->TexIndex             = texture_index;
            s_BatchData.QuadBufferPtr->TilingFactor         = tilingFactor;
            s_BatchData.QuadBufferPtr++;
        }

        s_BatchData.IndexCount += 6;
        s_BatchData.RenderingStatus.QuadCount++;
    }

    const Renderer::Status& Renderer::RenderingStatus()
    {
        return s_BatchData.RenderingStatus;
    }

    void Renderer::StatusReset()
    {
        s_BatchData.RenderingStatus.DrawCount = IMGV_NULL;
        s_BatchData.RenderingStatus.QuadCount = IMGV_NULL;
    }
}