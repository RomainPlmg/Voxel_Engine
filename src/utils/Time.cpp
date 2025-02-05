//
// Created by Romain on 22/12/2024.
//

#include "Time.h"

#include "gfx/GraphicContext.h"

Time* Time::m_Instance = new Time();
uint64_t Time::m_CurrentTime = 0;
uint64_t Time::m_LastTime = 0;
uint64_t Time::m_CounterFreq = 0;
double Time::m_DeltaTime = 0.0;
double Time::m_FPS = 0.0f;

void Time::Update() {
    m_CurrentTime = SDL_GetPerformanceCounter();

    if (m_LastTime == 0) {
        m_LastTime = m_CurrentTime;
    }

    m_CounterFreq = SDL_GetPerformanceFrequency();
    m_DeltaTime = static_cast<double>(m_CurrentTime - m_LastTime) / m_CounterFreq;
    m_FPS = 1.0f / m_DeltaTime;

    m_LastTime = m_CurrentTime;
}
