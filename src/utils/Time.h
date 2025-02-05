//
// Created by Romain on 22/12/2024.
//

#ifndef TIME_H
#define TIME_H

#include "pch.h"

class Time {
   private:
    static Time* m_Instance;
    static uint64_t m_CurrentTime;  // Actual time
    static uint64_t m_LastTime;     // Time since last call
    static uint64_t m_CounterFreq;  // The counter frequency
    static double m_DeltaTime;      // Elapsed time between two frames in seconds
    static double m_FPS;

   public:
    // Call this method at the start of each frame
    static void Update();

    static uint64_t GetCurrentTime() { return m_CurrentTime; }
    static uint64_t GetCounterFreq() { return m_CounterFreq; }

    // Return deltaTime in second
    static double GetDeltaTime() { return m_DeltaTime; }
    static double GetFPS() { return m_FPS; }
};

#endif  // TIME_H
