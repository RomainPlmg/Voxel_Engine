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
    ViewportGUI() = default;
    ~ViewportGUI() = default;

    void Init();
    void Render();

    static std::shared_ptr<ViewportGUI> Create();

   private:
    ImVec2 m_ViewportSize, m_ViewportPos;
    std::shared_ptr<FrameBuffer> m_FrameBuffer;
};

#endif  // VIEWPORT_GUI_H