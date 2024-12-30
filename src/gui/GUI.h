//
// Created by Romain on 23/12/2024.
//

#ifndef GUI_H
#define GUI_H

#include "InfoWindow.h"
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
    std::shared_ptr<InfoWindow> GetInfoWindow() const { return m_InfoWindow; }

   private:
    std::shared_ptr<InfoWindow> m_InfoWindow;
};

#endif  // GUI_H
