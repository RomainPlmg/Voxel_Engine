//
// Created by Romain on 20/12/2024.
//

#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h> // Include GLFW after glad
// clang-format on

class GraphicContext {
   public:
    explicit GraphicContext(GLFWwindow* windowHandler);

    void Init() const;

    static std::shared_ptr<GraphicContext> Create(GLFWwindow* windowHandler);

   private:
    GLFWwindow* m_Handler;
};

#endif  // OPENGLCONTEXT_H
