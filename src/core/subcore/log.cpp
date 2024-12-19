#include "log.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace IMGV::Core
{
    static Boolean s_Initialized = IMGV_FALSE;
    static Reference<spdlog::logger> s_CoreLogger = IMGV_NULLPTR;
    static Reference<spdlog::logger> s_ClientLogger = IMGV_NULLPTR;

    static void Init()
    {
        std::vector<spdlog::sink_ptr> log_skin{};
        log_skin.emplace_back(CreateRef<spdlog::sinks::stdout_color_sink_mt>());
        log_skin.emplace_back(CreateRef<spdlog::sinks::basic_file_sink_mt>("imgv.log", IMGV_TRUE));
        log_skin[0]->set_pattern("%^[%T] %n: %v%$");
        log_skin[1]->set_pattern("[%T][%l] %n: %v");

        s_CoreLogger = CreateRef<spdlog::logger>("IMGV:CORE", std::begin(log_skin), std::end(log_skin));
        spdlog::register_logger(s_CoreLogger);
        s_CoreLogger->set_level(spdlog::level::trace);
        s_CoreLogger->flush_on(spdlog::level::trace);

        s_ClientLogger = CreateRef<spdlog::logger>("TE:Client", std::begin(log_skin), std::end(log_skin));
        spdlog::register_logger(s_ClientLogger);
        s_ClientLogger->set_level(spdlog::level::trace);
        s_ClientLogger->flush_on(spdlog::level::trace);
        s_Initialized = IMGV_TRUE;
    }

    Reference<spdlog::logger>& Logger::GetCoreLogger() 
    {
        if(!s_Initialized)
            Init();

        return s_CoreLogger;
    }

    Reference<spdlog::logger>& Logger::GetClientLogger() 
    {
        if(!s_Initialized)
            Init();

        return s_ClientLogger;
    }
}