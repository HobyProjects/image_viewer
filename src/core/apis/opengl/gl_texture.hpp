#pragma once

#include <glad/glad.h>
#include "texture.hpp"

namespace IMGV::Core
{
    class IMGV_API GL_Texture2D final : public Texture2D
    {
        public:
            GL_Texture2D(UInt32 width, UInt32 height);
            GL_Texture2D(const std::filesystem::path& path, Boolean flip = IMGV_TRUE);
            virtual ~GL_Texture2D() override;

            virtual void Bind(UInt32 slot = 0) const override;
            virtual void Unbind() const override;

            virtual TextureID GetID() const override { return m_TextureID; }
            virtual Int32 GetWidth() const override { return m_Width; }
            virtual Int32 GetHeight() const override { return m_Height; }
            virtual Int32 GetChannels() const override { return m_Channels; }
            virtual UInt32 GetInternalFormat() const override { return m_InternalFormat; }
            virtual UInt32 GetDataFormat() const override { return m_DataFormat; }
            virtual TextureData GetTextureData() const override { return m_Data; }

        private:
            Int32 m_Width{IMGV_NULL};
            Int32 m_Height{IMGV_NULL};
            Int32 m_Channels{IMGV_NULL};
            TextureData m_Data{IMGV_NULLPTR};
            TextureID m_TextureID{IMGV_NULL};
            Boolean m_FromImageFile{IMGV_FALSE};
            UInt32 m_InternalFormat{IMGV_NULL};
            UInt32 m_DataFormat{IMGV_NULL};
    };
}