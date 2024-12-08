#include "gl_texture.hpp"
#include <stb/stb_image.h>

namespace IMGV::Core
{
    GL_Texture2D::GL_Texture2D(UInt32 width, UInt32 height)
    {
        m_Width = width;
        m_Height = height;
        m_Channels = GL_RGBA;

        m_Data = new UInt8[m_Width * m_Height * m_Channels];
        std::memset(m_Data, 255, m_Width * m_Height * m_Channels);
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, m_Data);
        glGenerateMipmap(GL_TEXTURE_2D);

        m_FromImageFile = false;

    }

    GL_Texture2D::GL_Texture2D(const std::filesystem::path& path, Boolean flip)
    {
        if(!std::filesystem::exists(path))
        {
			IMGV_CORE_ERROR("{0} Texture file does not exist!", path.string());
			return;
		}

        stbi_set_flip_vertically_on_load(flip);
        m_Data = stbi_load(path.string().c_str(), &m_Width, &m_Height, &m_Channels, 0);

        if (!m_Data) 
        {
            IMGV_CORE_ERROR("Failed to load texture file -> {0}!", path.string());
            return;
        }

        if (m_Channels == 4) 
        {
			m_InternalFormat    = GL_RGBA8;
			m_DataFormat        = GL_RGBA;
		} 
        else
        {
			m_InternalFormat    = GL_RGB8;
			m_DataFormat        = GL_RGB;
		}

        glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, m_Data);
		glGenerateMipmap(GL_TEXTURE_2D);
		m_FromImageFile = IMGV_TRUE;
    }

    GL_Texture2D::~GL_Texture2D()
    {
        (m_FromImageFile) ? stbi_image_free(m_Data) : delete[] m_Data;
        glDeleteTextures(1, &m_TextureID);
    }

    void GL_Texture2D::Bind(UInt32 slot) const
    {
        glBindTextureUnit(slot, m_TextureID);
    }

    void GL_Texture2D::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}