//
// Created by Romain on 20/12/2024.
//

#include "GraphicContext.h"

#include "utils/Log.h"

GraphicContext::GraphicContext(SDL_Window* windowHandler) : m_Handler(windowHandler) {}

void GraphicContext::Init() {
    m_GLContext = SDL_GL_CreateContext(m_Handler);
    if (!m_GLContext) {
        ERROR_MSG("Failed to create OpenGL context: {0}", SDL_GetError())
        SDL_DestroyWindow(m_Handler);
        SDL_Quit();
        return;
    }

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress))) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }  // Initialized glad
}

void GraphicContext::Destroy() const { SDL_GL_DeleteContext(m_GLContext); }

std::shared_ptr<GraphicContext> GraphicContext::Create(SDL_Window* windowHandler) {
    return std::make_shared<GraphicContext>(windowHandler);
}
