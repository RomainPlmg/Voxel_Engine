//
// Created by Romain on 22/12/2024.
//

#include "Time.h"

#include "gfx/GraphicContext.h"

Time* Time::m_Instance = new Time();
double Time::m_LastTime = 0.0;
double Time::m_DeltaTime = 0.0f;
uint32_t Time::m_FPS = 0;

void Time::Update() {
    const double currentTime = glfwGetTime();

    if (m_LastTime == 0) {
        m_LastTime = currentTime;
    }
    m_DeltaTime = (currentTime - m_LastTime);
    m_FPS = static_cast<uint32_t>(std::floor(1.0f / m_DeltaTime));

    m_LastTime = currentTime;
}
