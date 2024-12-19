#include "gl_buffers.hpp"

namespace IMGV::Core
{
    GL_VertexBuffer::GL_VertexBuffer(UInt32 allocatorSize)
    {
        glCreateBuffers(1, &m_VertexBufferID);
        glNamedBufferData(m_VertexBufferID, allocatorSize, nullptr, GL_DYNAMIC_DRAW);
    }

    GL_VertexBuffer::GL_VertexBuffer(VertexBufferData data, UInt32 dataSize)
    {
        glCreateBuffers(1, &m_VertexBufferID);
        glNamedBufferData(m_VertexBufferID, dataSize, data, GL_STATIC_DRAW);
    }

    GL_VertexBuffer::~GL_VertexBuffer()
    {
        glDeleteBuffers(1, &m_VertexBufferID);
    }

    void GL_VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    }

    void GL_VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void GL_VertexBuffer::SetData(const void* data, UInt32 size)
    {
        glNamedBufferSubData(m_VertexBufferID, 0, size, data);
    }

    void GL_VertexBuffer::SetLayout(const BufferLayout& layout)
    {
        m_Layout = layout;
    }

    GL_IndexBuffer::GL_IndexBuffer(IndexBufferData data, UInt32 indicesCount)
    {
        glCreateBuffers(1, &m_IndexBufferID);
        glNamedBufferData(m_IndexBufferID, indicesCount * sizeof(UInt32), data, GL_STATIC_DRAW);
        m_Count = indicesCount;
    }

    GL_IndexBuffer::~GL_IndexBuffer()
    {
        glDeleteBuffers(1, &m_IndexBufferID);
    }

    void GL_IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
    }

    void GL_IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}