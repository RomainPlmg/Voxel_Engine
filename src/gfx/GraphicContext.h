//
// Created by Romain on 20/12/2024.
//

#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H

// clang-format off
#include <glad/glad.h>
#include <SDL2/SDL.h>
// clang-format on

class GraphicContext {
   public:
    explicit GraphicContext(SDL_Window* windowHandler);

    void Init();
    void Destroy() const;

    /* Getters */
    SDL_GLContext GetGLContext() const { return m_GLContext; }

    static std::shared_ptr<GraphicContext> Create(SDL_Window* windowHandler);

   private:
    SDL_Window* m_Handler;
    SDL_GLContext m_GLContext;
};

#endif  // OPENGLCONTEXT_H
