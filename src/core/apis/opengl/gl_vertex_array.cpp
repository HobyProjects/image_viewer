#include "gl_vertex_array.hpp"

namespace IMGV::Core
{
    GL_VertexArray::GL_VertexArray()
    {
        glCreateVertexArrays(1, &m_VertexArrayID);
    }

    GL_VertexArray::~GL_VertexArray()
    {
        glDeleteVertexArrays(1, &m_VertexArrayID);
    }

    void GL_VertexArray::Bind() const
    {
        glBindVertexArray(m_VertexArrayID);
    }

    void GL_VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    VertexArrayID GL_VertexArray::GetID() const
    {
        return m_VertexArrayID;
    }

    static GLenum GetDataType(BufferStride component) 
    {
        switch (component) 
        {
            case BufferStride::F1: return GL_FLOAT;
            case BufferStride::F2: return GL_FLOAT;
            case BufferStride::F3: return GL_FLOAT;
            case BufferStride::F4: return GL_FLOAT;
            case BufferStride::MAT3: return GL_FLOAT;
            case BufferStride::MAT4: return GL_FLOAT;
            default: return 0;
        }

        IMGV_CORE_ERROR("Unknown component type");
        return IMGV_ERROR;
    }

    void GL_VertexArray::EmplaceVtxBuffer(const Reference<VertexBuffer>& vtxBuffer)
    {
        glBindVertexArray(m_VertexArrayID);
        vtxBuffer->Bind();
        const auto& layout = vtxBuffer->GetLayout();
        const auto& elements = layout.GetElements();
        UInt32 layout_index{ 0 };

        for (auto& element : elements) 
        {
            glEnableVertexAttribArray(layout_index);
            glVertexAttribPointer(
                layout_index,
                static_cast<GLint>(element.Components),
                GL_FLOAT,
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)element.Offset
            );
        }

        m_VtxBuffers.emplace_back(vtxBuffer);
    }
    void GL_VertexArray::EmplaceIdxBuffer(const Reference<IndexBuffer>& idxBuffer)
    {
        glBindVertexArray(m_VertexArrayID);
        m_IdexBuffer = idxBuffer;
        m_IdexBuffer->Bind();
    }

    const std::vector<Reference<VertexBuffer>>& GL_VertexArray::GetVtxBuffers() const
    {
        return m_VtxBuffers;
    }
    
    const Reference<IndexBuffer>& GL_VertexArray::GetIdexBuffer() const
    {
        return m_IdexBuffer;
    }
}