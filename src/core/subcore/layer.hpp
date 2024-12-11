#pragma once

#include "typedef.hpp"
#include "timer.hpp"
#include "events.hpp"

namespace IMGV::Core
{
    class IMGV_API Layer
    {
        public:

        #ifdef IMGV_DEBUG
            Layer(const String& name) : m_DebugName(name) {}
         #endif

            Layer() = default;
            virtual ~Layer() = default;

            virtual void OnAttach() {}
            virtual void OnDetach() {}

            virtual void OnUpdate(Timer deltaTime) {}
            virtual void OnEvent(Event& event) {}
            virtual void OnUIRendering() {}

        #ifdef IMGV_DEBUG

        public:
            const String& GetName() const { return m_DebugName; }        
        protected:
            String m_DebugName{String("Unknown")};
        
        #endif
    };
}