//
// Created by Romain on 30/12/2024.
//

#ifndef DEBUG_GUI_H
#define DEBUG_GUI_H

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
};

#endif  // DEBUG_GUI_H
