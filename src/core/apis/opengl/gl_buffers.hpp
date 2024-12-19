#pragma once

#include <glad/glad.h>
#include "buffers.hpp"

namespace IMGV::Core
{
    class IMGV_API GL_VertexBuffer final : public VertexBuffer
    {
        public:
            GL_VertexBuffer() = default;
            GL_VertexBuffer(UInt32 allocatorSize);
            GL_VertexBuffer(VertexBufferData data, UInt32 dataSize);
            virtual ~GL_VertexBuffer();

            virtual void Bind() const override;
            virtual void Unbind() const override;
            virtual VertexBufferID GetID() const override { return m_VertexBufferID; }
            virtual void SetData(const void* data, UInt32 size) override;
            virtual void SetLayout(const BufferLayout& layout) override;
            virtual const BufferLayout& GetLayout() const override { return m_Layout; }

        private:
            VertexBufferID m_VertexBufferID{IMGV_NULL};
            BufferLayout m_Layout;
    };

    class IMGV_API GL_IndexBuffer final : public IndexBuffer
    {
        public:
            GL_IndexBuffer() = default;
            GL_IndexBuffer(IndexBufferData data, UInt32 indicesCount);
            virtual ~GL_IndexBuffer();

            virtual void Bind() const override;
            virtual void Unbind() const override;
            virtual IndexBufferID GetID() const override { return m_IndexBufferID; }
            virtual UInt32 GetCount() const override { return m_Count; }

        private:
            IndexBufferID m_IndexBufferID{IMGV_NULL};
            UInt32 m_Count{IMGV_NULL};
    };
}

