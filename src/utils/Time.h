//
// Created by Romain on 22/12/2024.
//

#ifndef TIME_H
#define TIME_H

#include "pch.h"

class Time {
   private:
    static Time* m_Instance;
    static double m_LastTime;   // Time since last call
    static double m_DeltaTime;  // Elapsed time between two frames
    static uint32_t m_FPS;

   public:
    // Call this method at the start of each frame
    static void Update();

    // Return deltaTime in seconds
    static double GetDeltaTime() { return m_DeltaTime; }
    static uint32_t GetFPS() { return m_FPS; }
};

#endif  // TIME_H
