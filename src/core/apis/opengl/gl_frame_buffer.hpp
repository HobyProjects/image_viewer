#pragma once

#include <glad/glad.h>

#include "base.hpp"
#include "frame_buffer.hpp"

namespace IMGV::Core
{
    class IMGV_API GL_FrameBuffer final : public FrameBuffer
    {
        public:
            GL_FrameBuffer() = default;
            GL_FrameBuffer(const FrameBufferSpecification& specification);
            virtual ~GL_FrameBuffer();

            virtual void Bind() const override;
            virtual void Unbind() const override;
            virtual void ResizeFrame(UInt32 width, UInt32 height) override;
            virtual FrameBufferID GetFrameBufferID() const override;
            virtual FrameBufferAttachmentID GetColorAttachment() const override;
            virtual FrameBufferSpecification& GetFrameSpecification() override;

        protected:
            virtual void CreateFrame() override;

        private:
            FrameBufferID m_FrameBufferID{IMGV_NULL};
            FrameBufferAttachmentID m_ColorAttachment{IMGV_NULL};
            FrameBufferAttachmentID m_DepthAttachment{IMGV_NULL};
            FrameBufferSpecification m_Specification;
    };
}