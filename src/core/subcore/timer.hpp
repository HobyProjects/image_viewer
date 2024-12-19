#pragma once

#include "base.hpp"
#include "typedef.hpp"

namespace IMGV::Core
{
    class IMGV_API Timer
    {
        public:
            Timer() = default;
            Timer(Float deltaTime) : m_DeltaTime(deltaTime) {}
            ~Timer() = default;

            Float GetDeltaTime() const { return m_DeltaTime; }
            Float GetDeltaTimeSeconds() const { return m_DeltaTime; }
            Float GetDeltaTimeInMilliseconds() const { return m_DeltaTime * 1000.0f; }
            operator Float() const { return m_DeltaTime; }

        private:
            Float m_DeltaTime{0.0f};
    };
}