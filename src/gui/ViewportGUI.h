//
// Created by Romain on 30/01/2025.
//

#ifndef VIEWPORT_GUI_H
#define VIEWPORT_GUI_H

#include "imgui.h"

class FrameBuffer;
class Renderer;
class Event;

class ViewportGUI {
   public:
    ViewportGUI();
    ~ViewportGUI() = default;

    void Init();
    void Render();

    /* Getters */
    glm::mat4 GetProjMatrix() const { return m_ProjMatrix; }

    static std::shared_ptr<ViewportGUI> Create();

   private:
    ImVec2 m_ViewportSize;
    glm::mat4 m_ProjMatrix;
    std::shared_ptr<FrameBuffer> m_FrameBuffer;
};

#endif  // VIEWPORT_GUI_H