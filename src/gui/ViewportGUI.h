//
// Created by Romain on 30/01/2025.
//

#ifndef VIEWPORT_GUI_H
#define VIEWPORT_GUI_H

#include "imgui.h"

class FrameBuffer;
class Renderer;

class ViewportGUI {
   public:
    ViewportGUI();
    ~ViewportGUI() = default;

    void Render();

    static std::shared_ptr<ViewportGUI> Create();

   private:
    ImVec2 m_ViewportSize;
    std::shared_ptr<FrameBuffer> m_FrameBuffer;
};

#endif  // VIEWPORT_GUI_H