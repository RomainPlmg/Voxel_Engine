//
// Created by Romain on 30/12/2024.
//

#ifndef MONITOR_H
#define MONITOR_H

class Monitor {
   public:
    Monitor() = default;
    ~Monitor() = default;

    static uint32_t GetRAMConsumption();
};

#endif  // MONITOR_H
