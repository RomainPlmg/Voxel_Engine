//
// Created by Romain on 20/12/2024.
//

#ifndef WINDOW_H
#define WINDOW_H

#include "gfx/GraphicContext.h"
#include "pch.h"

struct WindowProps {
    std::string title;
    int width;
    int height;
    bool vsync{};

    /* Default window props */
    explicit WindowProps(std::string title = "Voxel-Engine", const int width = 1280, const int height = 720)
        : title(std::move(title)), width(width), height(height), vsync(true) {}
};

class GraphicContext;
class EventDispatcher;
class Event;

class Window {
   public:
    explicit Window(const WindowProps& props);
    ~Window() = default;

    void Init(const bool automatic = true);
    void Update();
    void SwapBuffers() const;
    void Close();
    void Shutdown() const;
    [[nodiscard]] bool ShouldClose() const;

    /* Getters */
    [[nodiscard]] std::string GetTitle() const { return m_Properties.title; }
    [[nodiscard]] uint32_t GetWidth() const { return m_Properties.width; }
    [[nodiscard]] uint32_t GetHeight() const { return m_Properties.height; }
    [[nodiscard]] bool IsVSync() const { return m_Properties.vsync; }
    [[nodiscard]] SDL_Window* GetHandler() const { return m_Handler; }
    [[nodiscard]] std::shared_ptr<EventDispatcher> GetEventDispatcher() const { return m_EventDispatcher; }
    [[nodiscard]] std::shared_ptr<GraphicContext> GetGraphicContext() const { return m_GraphicContext; }

    static std::shared_ptr<Window> Create(const WindowProps& props = WindowProps());

   private:
    WindowProps m_Properties;
    SDL_Window* m_Handler;
    SDL_Event m_Event;
    std::shared_ptr<GraphicContext> m_GraphicContext;
    std::shared_ptr<EventDispatcher> m_EventDispatcher;
    std::vector<SDL_DisplayMode> m_VideoModes;
    bool m_IsRunning;

    /* Callback functions */
    void framebuffer_size_callback(int width, int height);
    void key_callback(int key, int scancode, int action, int mods);
    void mouse_cursor_pos_callback(double xpos, double ypos);
    void mouse_button_callback(int button, int action, int mods);
    void window_pos_callback(int xpos, int ypos);
};

#endif  // WINDOW_H
