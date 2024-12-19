#pragma once

#include <glad/glad.h>
#include "vertex_array.hpp"

namespace IMGV::Core
{
    class IMGV_API GL_VertexArray final : public VertexArray
    {
        public:
            GL_VertexArray();
            virtual ~GL_VertexArray();

            virtual void Bind() const override;
            virtual void Unbind() const override;
            
            virtual VertexArrayID GetID() const override;
            virtual void EmplaceVtxBuffer(const Reference<VertexBuffer>& vtxBuffer) override;
            virtual void EmplaceIdxBuffer(const Reference<IndexBuffer>& idxBuffer) override;
            virtual const std::vector<Reference<VertexBuffer>>& GetVtxBuffers() const override;
            virtual const Reference<IndexBuffer>& GetIdexBuffer() const override;

        private:
            VertexArrayID m_VertexArrayID{IMGV_NULL};
            std::vector<Reference<VertexBuffer>> m_VtxBuffers;
            Reference<IndexBuffer> m_IdexBuffer;
    };
}