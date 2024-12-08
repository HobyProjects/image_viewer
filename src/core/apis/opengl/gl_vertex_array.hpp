#pragma once

#include <glad/glad.h>
#include "vertex_array.hpp"

namespace IMGV::Core
{
    class IMGV_API GL_VertexArray final : public VertexArray
    {
        public:
            GL_VertexArray() = default;
            virtual ~GL_VertexArray() override;

            virtual void Bind() const override;
            virtual void Unbind() const override;
            
            virtual VertexArrayID GetID() const override;
            virtual void EmplaceVtxBuffer(const Ref<VertexBuffer>& vtxBuffer) override;
            virtual void EmplaceIdxBuffer(const Ref<IndexBuffer>& idxBuffer) override;
            virtual const std::vector<Ref<VertexBuffer>>& GetVtxBuffers() const override;
            virtual const Ref<IndexBuffer>& GetIdexBuffer() const override;

        private:
            VertexArrayID m_VertexArrayID{IMGV_NULL};
            std::vector<Ref<VertexBuffer>> m_VtxBuffers;
            Ref<IndexBuffer> m_IdexBuffer;
    };
}