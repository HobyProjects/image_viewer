#pragma once

#include "typedef.hpp"

namespace IMGV::Core
{
    class IMGV_API Texture2D
    {
        public:
            Texture2D() = default;
            virtual ~Texture2D() = default;

            virtual void Bind(UInt32 slot = 0) const = IMGV_NULL;
            virtual void Unbind() const = IMGV_NULL;

            virtual TextureID GetID() const = IMGV_NULL;
            virtual Int32 GetWidth() const = IMGV_NULL;
            virtual Int32 GetHeight() const = IMGV_NULL;
            virtual Int32 GetChannels() const = IMGV_NULL;
            virtual UInt32 GetInternalFormat() const = IMGV_NULL;
            virtual UInt32 GetDataFormat() const = IMGV_NULL;
            virtual TextureData GetTextureData() const = IMGV_NULL;
    };

    class IMGV_API SubTexture2D
    {
        public:
            SubTexture2D() = default;
            SubTexture2D(const Reference<Texture2D>& texture, const Vec2& min, const Vec2& max);
            ~SubTexture2D() = default;

            const Reference<Texture2D>& GetTexturePtr() const { return m_Texture; }
            const Vec2* GetTextureCoords() const { return m_TexCoords; }
            UInt32 GetInternalFormat() const { return m_InternalFormat; }
            UInt32 GetDataFormat() const { return m_DataFormat; }

        private:
            static const UInt32 NUMBER_OF_TEXTURE_COORDS = 4;
            Reference<Texture2D> m_Texture{IMGV_NULLPTR};
            Vec2 m_TexCoords[NUMBER_OF_TEXTURE_COORDS];
            UInt32 m_InternalFormat{IMGV_NULL};
            UInt32 m_DataFormat{IMGV_NULL};
    };

    IMGV_NODISCARD IMGV_API Reference<Texture2D> CreateTexture2D(Int32 width, Int32 height);
    IMGV_NODISCARD IMGV_API Reference<Texture2D> CreateTexture2D(const std::filesystem::path& path, Boolean flip = IMGV_TRUE);
    IMGV_NODISCARD IMGV_API Reference<SubTexture2D> CreateSubTexture2D(const Reference<Texture2D>& texture, const Vec2& coords, const Vec2& cellSize, const Vec2& spriteSize);
}