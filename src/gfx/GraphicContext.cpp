//
// Created by Romain on 20/12/2024.
//

#include "GraphicContext.h"

GraphicContext::GraphicContext(GLFWwindow* windowHandler) : m_Handler(windowHandler) {}

void GraphicContext::Init() const {
    glfwMakeContextCurrent(m_Handler);  // Make OpenGL context
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }  // Initialized glad
}

std::shared_ptr<GraphicContext> GraphicContext::Create(GLFWwindow* windowHandler) {
    return std::make_shared<GraphicContext>(windowHandler);
}
