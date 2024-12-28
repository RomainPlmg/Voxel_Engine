//
// Created by Romain on 23/12/2024.
//

#ifndef GUI_H
#define GUI_H

#include "pch.h"

class GUI {
   public:
    GUI() = default;
    ~GUI() = default;

    void Init();
    void Render();
    void Shutdown();

    static std::shared_ptr<GUI> Create();
};

#endif  // GUI_H
