#pragma once

#include "base.hpp"
#include "typedef.hpp"

namespace IMGV::Core
{
    struct IMGV_API FrameBufferSpecification
    {
        UInt32 Width{IMGV_NULL};
        UInt32 Height{IMGV_NULL};
        Boolean SwapChainTarget{IMGV_FALSE};
    };

    class IMGV_API FrameBuffer
    {
        public:
            FrameBuffer() = default;
            virtual ~FrameBuffer() = default;

            virtual void Bind() const = IMGV_NULL;
            virtual void Unbind() const = IMGV_NULL;
            virtual void ResizeFrame(UInt32 width, UInt32 height) = IMGV_NULL;
            virtual FrameBufferID GetFrameBufferID() const = IMGV_NULL;
            virtual FrameBufferAttachmentID GetColorAttachment() const = IMGV_NULL;
            virtual FrameBufferSpecification& GetFrameSpecification() = IMGV_NULL;

        protected:
            virtual void CreateFrame() = IMGV_NULL;
    };

    IMGV_NODISCARD IMGV_API Reference<FrameBuffer> CreateFrameBuffer(const FrameBufferSpecification& specification);

}