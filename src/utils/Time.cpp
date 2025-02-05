//
// Created by Romain on 22/12/2024.
//

#include "Time.h"

#include "Log.h"
#include "gfx/GraphicContext.h"

Time* Time::m_Instance = new Time();
uint32_t Time::m_LastTime = 0;
double Time::m_DeltaTime = 0.0;
float Time::m_FPS = 0.0f;

void Time::Update() {
    uint32_t currentTime = SDL_GetTicks();

    if (m_LastTime == 0) {
        m_LastTime = currentTime;
    }
    m_DeltaTime = static_cast<double>(currentTime - m_LastTime) / 1000.0;
    m_FPS = 1.0f / m_DeltaTime;

    m_LastTime = currentTime;
}
