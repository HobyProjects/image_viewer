#pragma once

#include <memory>

#include "buffers.hpp"
#include "typedef.hpp"

namespace IMGV::Core
{
    class IMGV_API VertexArray
    {
        public:
            VertexArray() = default;
            virtual ~VertexArray() = default;

            virtual void Bind() const = IMGV_NULL;
            virtual void Unbind() const = IMGV_NULL;
            
            virtual VertexArrayID GetID() const = IMGV_NULL;
            virtual void EmplaceVtxBuffer(const Ref<VertexBuffer>& vtxBuffer) = IMGV_NULL;
            virtual void EmplaceIdxBuffer(const Ref<IndexBuffer>& idxBuffer) = IMGV_NULL;
            virtual const std::vector<Ref<VertexBuffer>>& GetVtxBuffers() const = IMGV_NULL;
            virtual const Ref<IndexBuffer>& GetIdexBuffer() const = IMGV_NULL;
    };

    IMGV_NODISCARD IMGV_API Ref<VertexArray> CreateVertexArray();
}