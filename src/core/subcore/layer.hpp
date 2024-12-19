#pragma once

#include "base.hpp"
#include "typedef.hpp"
#include "timer.hpp"
#include "events.hpp"

namespace IMGV::Core
{
    class IMGV_API Layer
    {
        public:
            Layer() = default;
            virtual ~Layer() = default;

            virtual void OnAttach() {}
            virtual void OnDetach() {}

            virtual void OnUpdate(Timer deltaTime) {}
            virtual void OnEvent(Event& event) {}
            virtual void OnUIRendering() {}
    };
}