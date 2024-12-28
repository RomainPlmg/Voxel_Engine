//
// Created by Romain on 20/12/2024.
//

#ifndef WINDOW_H
#define WINDOW_H

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
struct GLFWwindow;
struct GLFWvidmode;

class Window {
   public:
    explicit Window(const WindowProps& props);
    ~Window() = default;

    void Init(const bool automatic = true);
    void Update() const;
    void SwapBuffers() const;
    void Close() const;
    void Shutdown() const;
    [[nodiscard]] int ShouldClose() const;

    /* Getters */
    [[nodiscard]] std::string GetTitle() const { return m_Properties.title; }
    [[nodiscard]] uint32_t GetWidth() const { return m_Properties.width; }
    [[nodiscard]] uint32_t GetHeight() const { return m_Properties.height; }
    [[nodiscard]] bool IsVSync() const { return m_Properties.vsync; }
    [[nodiscard]] GLFWwindow* GetHandler() const { return m_Handler; }
    [[nodiscard]] std::shared_ptr<EventDispatcher> GetEventDispatcher() const { return m_EventDispatcher; }

    static std::shared_ptr<Window> Create(const WindowProps& props = WindowProps());

   private:
    WindowProps m_Properties;
    GLFWwindow* m_Handler;
    std::shared_ptr<GraphicContext> m_GraphicContext;
    std::shared_ptr<EventDispatcher> m_EventDispatcher;
    std::vector<const GLFWvidmode*> m_VideoModes;

    /* Callback functions */
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void window_pos_callback(GLFWwindow* window, int xpos, int ypos);
};

#endif  // WINDOW_H
