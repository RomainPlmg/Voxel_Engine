//
// Created by Romain on 20/12/2024.
//

#include "Log.h"

std::shared_ptr<spdlog::logger> Log::m_Logger;
bool Log::m_Initialized = false;

void Log::Init() {
    if (m_Initialized) {
        WARN_MSG("Logger already initialized.");
        return;
    }

    spdlog::set_pattern("%^[%T] %n: %v%$");  // [HH:MM:SS] loggerName: log

    m_Logger = spdlog::stdout_color_mt("VOX");

#ifndef _NDEBUG
    m_Logger->set_level(spdlog::level::trace);
#endif

    INFO_MSG("Engine logger initialized");

    m_Initialized = true;
}
