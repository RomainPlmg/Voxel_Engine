//
// Created by Romain on 30/12/2024.
//

#include "Monitor.h"

#ifdef _WIN32

// clang-format off
#include <Windows.h>
#include <Psapi.h>
// clang-format on

uint32_t Monitor::GetRAMConsumption() {
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    return pmc.WorkingSetSize / 1024;
}

#elif __unix__

#include <sys/resource.h>

uint32_t Monitor::GetRAMConsumption() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

#else

uint32_t Monitor::GetRAMConsumption() { return 0; }

#endif
