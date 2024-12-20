#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "base.hpp"
#include "typedef.hpp"

namespace IMGV::Core
{
    class IMGV_API Logger
    {
        private:
            Logger() = default;
            ~Logger() = default;
            
        public:
            static Reference<spdlog::logger>& GetCoreLogger();
            static Reference<spdlog::logger>& GetClientLogger();
    };
}

#define IMGV_CORE_TRACE(...) IMGV::Core::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define IMGV_CORE_INFO(...) IMGV::Core::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define IMGV_CORE_WARN(...) IMGV::Core::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define IMGV_CORE_ERROR(...) IMGV::Core::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define IMGV_CORE_CRITICAL(...) IMGV::Core::Logger::GetCoreLogger()->critical(__VA_ARGS__)

#define IMGV_TRACE(...) IMGV::Core::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define IMGV_INFO(...) IMGV::Core::Logger::GetClientLogger()->info(__VA_ARGS__)
#define IMGV_WARN(...) IMGV::Core::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define IMGV_ERROR(...) IMGV::Core::Logger::GetClientLogger()->error(__VA_ARGS__)
#define IMGV_CRITICAL(...) IMGV::Core::Logger::GetClientLogger()->critical(__VA_ARGS__)