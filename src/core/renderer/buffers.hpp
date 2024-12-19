#pragma once

#include <vector>
#include <initializer_list>

#include "typedef.hpp"

namespace IMGV::Core
{
    enum class BufferComponents
    {
        X       = 1,    
        XY      = 2,    
        UV      = 2,    
        XYZ     = 3,    
        RGB     = 3,    
        RGBA    = 4,    
        XYZW    = 4,    
        MAT3    = 3,    
        MAT4    = 4, 
    };

    enum class BufferStride 
    {
        BOOLEAN     = sizeof(Boolean),          
        F1          = sizeof(Float),            
        F2          = sizeof(Float) * 2,        
        F3          = sizeof(Float) * 3,        
        F4          = sizeof(Float) * 4,        
        MAT3        = sizeof(Float) * 3 * 3,    
        MAT4        = sizeof(Float) * 4 * 4,    
    };

    struct IMGV_API BufferElements 
    {
        Int32 Offset{IMGV_NULL};              
        String Name{};                      
        BufferStride Stride{};             
        Boolean Normalized{IMGV_FALSE};       
        BufferComponents Components{};     


        BufferElements() = default;
        BufferElements(const String& name, BufferComponents components, BufferStride stride, Boolean normalized) : Name(name), Components(components), Stride(stride), Normalized(normalized) {}
        ~BufferElements() = default;
    };

    class IMGV_API BufferLayout 
    {
        public:
            BufferLayout() = default;
            BufferLayout(std::initializer_list<BufferElements> elements) : m_Elements(elements) { CalStride(); }
            ~BufferLayout() = default;


            UInt32 GetStride() const { return m_Stride; }

            const std::vector<BufferElements>& GetElements() const { return m_Elements; }
            std::vector<BufferElements>::iterator begin() { return m_Elements.begin(); }
            std::vector<BufferElements>::iterator end() { return m_Elements.end(); }
            std::vector<BufferElements>::const_iterator begin() const { return m_Elements.begin(); }
            std::vector<BufferElements>::const_iterator end() const { return m_Elements.end(); }

        private:
            void CalStride()
            {
                m_Stride         = IMGV_NULL;
                UInt32 offset    = IMGV_NULL;

                for(auto& element : m_Elements)
                {
                    element.Offset = offset;
                    m_Stride += static_cast<UInt32>(element.Stride);
                    offset += static_cast<UInt32>(element.Stride);
                }
            }
        
        private:
            std::vector<BufferElements> m_Elements{};
            UInt32 m_Stride{IMGV_NULL};
    };

    class IMGV_API VertexBuffer
    {
        public:
            VertexBuffer() = default;
            virtual ~VertexBuffer() = default;

            virtual void Bind() const = IMGV_NULL;
            virtual void Unbind() const = IMGV_NULL;
            virtual VertexBufferID GetID() const = IMGV_NULL;

            virtual void SetData(const void* data, UInt32 size) = IMGV_NULL;
            virtual void SetLayout(const BufferLayout& layout) = IMGV_NULL;
            virtual const BufferLayout& GetLayout() const = IMGV_NULL;
    };

    class IMGV_API IndexBuffer
    {
        public:
            IndexBuffer() = default;
            virtual ~IndexBuffer() = default;

            virtual void Bind() const = IMGV_NULL;
            virtual void Unbind() const = IMGV_NULL;
            virtual IndexBufferID GetID() const = IMGV_NULL;
            virtual UInt32 GetCount() const = IMGV_NULL;
    };

    IMGV_NODISCARD IMGV_API Ref<VertexBuffer> CreateVertexBuffer(UInt32 allocatorSize);
    IMGV_NODISCARD IMGV_API Ref<VertexBuffer> CreateVertexBuffer(VertexBufferData data, UInt32 size);
    IMGV_NODISCARD IMGV_API Ref<IndexBuffer> CreateIndexBuffer(IndexBufferData data, UInt32 count);
}