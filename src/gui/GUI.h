//
// Created by Romain on 23/12/2024.
//

#ifndef GUI_H
#define GUI_H

#include "DebugGUI.h"
#include "ViewportGUI.h"
#include "pch.h"

class GUI {
   public:
    GUI();
    ~GUI() = default;

    void Init();
    void Render();
    void Shutdown();

    static std::shared_ptr<GUI> Create();

    /* Getters */
    std::shared_ptr<DebugGUI> GetDebugGUI() const { return m_DebugGUI; }
    std::shared_ptr<ViewportGUI> GetViewport() const { return m_ViewportGUI; }

   private:
    static bool m_Open;
    std::shared_ptr<DebugGUI> m_DebugGUI;
    std::shared_ptr<ViewportGUI> m_ViewportGUI;
};

#endif  // GUI_H
