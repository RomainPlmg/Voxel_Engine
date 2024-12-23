//
// Created by Romain on 22/12/2024.
//

#ifndef INPUT_H
#define INPUT_H

#include "pch.h"

struct GLFWwindow;

class Input {
   public:
    static bool IsKeyPressed(int keycode);
    static bool IsMouseButtonPressed(int button);
    static glm::dvec2 GetMousePosition();

   private:
    static GLFWwindow* m_Handler;
};

#endif  // INPUT_H
