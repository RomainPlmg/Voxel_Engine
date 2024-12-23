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

Window::Window(const WindowProps& props) : m_Properties(props), m_Handler(nullptr) {}

void Window::Init(const bool automatic) {
    // GLFW initialization
    if (!glfwInit()) {
        FATAL_MSG("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Recover video modes
    int monitorCount = 0;
    GLFWmonitor** monitor = glfwGetMonitors(&monitorCount);

    for (int i = 0; i < monitorCount; i++) {
        m_VideoModes.push_back(glfwGetVideoMode(monitor[i]));
    }
    // By default, use the primary monitor (index = 0)
    const auto primaryVideoMode = m_VideoModes[0];

    if (automatic) {
        constexpr float scaleFactor = 0.9f;
        m_Properties.width = primaryVideoMode->width * scaleFactor;
        m_Properties.height = primaryVideoMode->height * scaleFactor;
    }

    // Create the window handler
    m_Handler = glfwCreateWindow(m_Properties.width, m_Properties.height, m_Properties.title.c_str(), nullptr, nullptr);

    glfwSetWindowPos(m_Handler, primaryVideoMode->width / 2 - m_Properties.width / 2,
                     primaryVideoMode->height / 2 - m_Properties.height / 2);

    if (!m_Handler) {
        FATAL_MSG("Failed to create GLFW window");
    }

    glfwSetWindowUserPointer(m_Handler, this);

    // Disable cursor
    glfwSetInputMode(m_Handler, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /* Set callback functions */
    glfwSetFramebufferSizeCallback(m_Handler, framebuffer_size_callback);
    glfwSetKeyCallback(m_Handler, key_callback);
    glfwSetCursorPosCallback(m_Handler, mouse_cursor_pos_callback);
    glfwSetMouseButtonCallback(m_Handler, mouse_button_callback);
    glfwSetWindowPosCallback(m_Handler, window_pos_callback);

    m_EventDispatcher = EventDispatcher::Create();
    m_GraphicContext = GraphicContext::Create(m_Handler);
    m_GraphicContext->Init();
}

void Window::Update() const {
    glfwPollEvents();
    if (Application::GetInstance()->IsPaused()) {
        // Enable cursor
        glfwSetInputMode(m_Handler, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    } else {
        // Disable cursor
        glfwSetInputMode(m_Handler, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

void Window::SwapBuffers() const { glfwSwapBuffers(m_Handler); }

void Window::Close() const { glfwSetWindowShouldClose(m_Handler, 1); }

void Window::Shutdown() const {
    glfwDestroyWindow(m_Handler);
    glfwTerminate();
    INFO_MSG("Engine exit successful");
}

int Window::ShouldClose() const { return glfwWindowShouldClose(m_Handler); }

std::shared_ptr<Window> Window::Create(const WindowProps& props) { return std::make_shared<Window>(props); }

/* Callback functions */
void Window::framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
    const auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    WindowResizeEvent event(width, height);
    self->m_EventDispatcher->Dispatch(event);
}

void Window::key_callback(GLFWwindow* window, const int key, int scancode, const int action, int mods) {
    const auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    KeyEvent* event = nullptr;
    switch (action) {
        case GLFW_PRESS:
            event = new KeyPressedEvent(key);
            self->m_EventDispatcher->Dispatch(*event);
            break;
        case GLFW_REPEAT:
            event = new KeyPressedEvent(key, true);
            self->m_EventDispatcher->Dispatch(*event);
            break;
        case GLFW_RELEASE:
            event = new KeyReleasedEvent(key);
            self->m_EventDispatcher->Dispatch(*event);
            break;
        default:
            break;
    }
    if (event != nullptr) {
        delete event;
    }
}

void Window::mouse_cursor_pos_callback(GLFWwindow* window, const double xpos, const double ypos) {
    const auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    MouseMotionEvent event(xpos, ypos);
    auto blabla4 = self->m_EventDispatcher;
    self->m_EventDispatcher->Dispatch(event);
}

void Window::mouse_button_callback(GLFWwindow* window, const int button, const int action, int mods) {
    const auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    MouseEvent* event = nullptr;
    switch (action) {
        case GLFW_PRESS:
            event = new MouseButtonPressedEvent(button);
            self->m_EventDispatcher->Dispatch(*event);
            break;
        case GLFW_RELEASE:
            event = new MouseButtonReleasedEvent(button);
            self->m_EventDispatcher->Dispatch(*event);
            break;
        default:
            break;
    }
    if (event != nullptr) {
        delete event;
    }
}

void Window::window_pos_callback(GLFWwindow* window, const int xpos, const int ypos) {
    const auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    WindowMovedEvent event(xpos, ypos);
    self->m_EventDispatcher->Dispatch(event);
}
