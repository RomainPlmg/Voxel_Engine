//
// Created by Romain on 20/12/2024.
//

#include "Window.h"

#include "Application.h"
#include "events/EventApplication.h"
#include "events/EventDispatcher.h"
#include "events/EventKeyboard.h"
#include "events/EventMouse.h"
#include "gfx/GraphicContext.h"
#include "utils/Log.h"

Window::Window(const WindowProps& props) : m_Properties(props), m_Handler(nullptr), m_IsRunning(true) {}

void Window::Init(const bool automatic) {
    // SDL2 initialization
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        FATAL_MSG("Failed to initialize SDL2: {0}", SDL_GetError());
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);                           // OpenGL 4.x
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);                           // OpenGL 4.6
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);  // Core Profile
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);                                    // Enable double buffering

    // Recover video modes
    int monitorCount = SDL_GetNumVideoDisplays();

    for (int i = 0; i < monitorCount; i++) {
        SDL_DisplayMode mode;
        if (SDL_GetCurrentDisplayMode(i, &mode) == 0) {
            m_VideoModes.push_back(mode);
        } else {
            FATAL_MSG("Error SDL_GetCurrentDisplayMode: {0}", SDL_GetError());
        }
    }
    // By default, use the primary monitor (index = 0)
    const auto primaryVideoMode = m_VideoModes[0];

    if (automatic) {
        constexpr float scaleFactor = 0.9f;
        m_Properties.width = primaryVideoMode.w * scaleFactor;
        m_Properties.height = primaryVideoMode.h * scaleFactor;
    }

    // Create the window handler
    m_Handler = SDL_CreateWindow(m_Properties.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                 m_Properties.width, m_Properties.height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!m_Handler) {
        FATAL_MSG("Failed to create SDL2 window");
    }

    m_EventDispatcher = EventDispatcher::Create();
    m_GraphicContext = GraphicContext::Create(m_Handler);
    m_GraphicContext->Init();

    // Disable VSync
    SDL_GL_SetSwapInterval(0);
}

void Window::Update() {
    while (SDL_PollEvent(&m_Event)) {
        Event* tmpEvent = nullptr;
        switch (m_Event.type) {
            case SDL_QUIT:
                /* code */
                break;

            case SDL_WINDOWEVENT:
                if (m_Event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    tmpEvent = new WindowResizeEvent(m_Event.window.data1, m_Event.window.data2);
                    m_EventDispatcher->Dispatch(*tmpEvent);
                } else if (m_Event.window.event == SDL_WINDOWEVENT_MOVED) {
                    tmpEvent = new WindowMovedEvent(m_Event.window.data1, m_Event.window.data2);
                    m_EventDispatcher->Dispatch(*tmpEvent);
                }

                break;

            case SDL_KEYDOWN:
                if (m_Event.key.repeat == 0) {
                    tmpEvent = new KeyPressedEvent(m_Event.key.keysym.sym);
                    m_EventDispatcher->Dispatch(*tmpEvent);
                } else {
                    tmpEvent = new KeyPressedEvent(m_Event.key.keysym.sym, true);
                    m_EventDispatcher->Dispatch(*tmpEvent);
                }
                break;

            case SDL_KEYUP:
                tmpEvent = new KeyReleasedEvent(m_Event.key.keysym.sym);
                m_EventDispatcher->Dispatch(*tmpEvent);
                break;

            case SDL_MOUSEMOTION:
                tmpEvent = new MouseMotionEvent(m_Event.motion.x, m_Event.motion.y);
                m_EventDispatcher->Dispatch(*tmpEvent);
                break;

            case SDL_MOUSEBUTTONDOWN:
                tmpEvent = new MouseButtonPressedEvent(m_Event.button.button);
                m_EventDispatcher->Dispatch(*tmpEvent);
                break;

            case SDL_MOUSEBUTTONUP:
                tmpEvent = new MouseButtonReleasedEvent(m_Event.button.button);
                m_EventDispatcher->Dispatch(*tmpEvent);
                break;

            default:
                break;
        }

        if (tmpEvent != nullptr) {
            delete tmpEvent;
        }
    }
}

void Window::SwapBuffers() const { SDL_GL_SwapWindow(m_Handler); }

void Window::Close() { m_IsRunning = false; }

void Window::Shutdown() const {
    m_GraphicContext->Destroy();
    SDL_DestroyWindow(m_Handler);
    SDL_Quit();
    INFO_MSG("Engine exit successful");
}

bool Window::ShouldClose() const { return !m_IsRunning; }

std::shared_ptr<Window> Window::Create(const WindowProps& props) { return std::make_shared<Window>(props); }
