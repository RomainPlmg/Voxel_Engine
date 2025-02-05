//
// Created by Romain on 30/12/2024.
//

#ifndef DEBUG_GUI_H
#define DEBUG_GUI_H

// The debug refresh rate in second
constexpr double DEBUG_GUI_REFRESH_RATE = 0.25;

#define GL_LINE 0x1B01
#define GL_FILL 0x1B02

class DebugGUI {
   public:
    DebugGUI();
    ~DebugGUI() = default;

    void Render();

    /* Setters */
    void SetPlayerPosition(glm::vec3 position);

    static std::shared_ptr<DebugGUI> Create();

   private:
    glm::vec3 m_PlayerPos;

    // Used to update the FPS text
    uint64_t m_DebugLastFrameTime;
    double m_DebugDeltaTime;
    double m_DebugFPS;
};

#endif  // DEBUG_GUI_H
