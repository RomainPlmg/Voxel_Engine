//
// Created by Romain on 20/12/2024.
//

#ifndef LOGGING_H
#define LOGGING_H

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

class Log {
   public:
    Log() = default;
    ~Log() = default;

    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetLogger() { return m_Logger; }
    inline static bool IsInitialized() { return m_Initialized; }

   private:
    static std::shared_ptr<spdlog::logger> m_Logger;
    static bool m_Initialized;
};

#define TRACE_MSG(...) Log::GetLogger()->trace(__VA_ARGS__);
#define INFO_MSG(...) Log::GetLogger()->info(__VA_ARGS__);
#define WARN_MSG(...) Log::GetLogger()->warn(__VA_ARGS__);
#define ERROR_MSG(...) Log::GetLogger()->error(__VA_ARGS__);
#define FATAL_MSG(...)                       \
    Log::GetLogger()->critical(__VA_ARGS__); \
    std::abort();

#endif  // LOGGING_H
