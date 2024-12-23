
// Created by Romain on 20/12/2024.
//

#include "Application.h"

#include "GLFW/glfw3.h"
#include "Window.h"
#include "events/Event.h"
#include "events/EventDispatcher.h"
#include "events/EventKeyboard.h"
#include "gfx/Renderer.h"
#include "gfx/Shader.h"
#include "gui/GUI.h"
#include "utils/Log.h"
#include "utils/Time.h"
#include "world/World.h"

Application* Application::m_Instance = nullptr;

Application::Application() : m_PauseMode(false) {
    m_Window = Window::Create();
    m_Renderer = Renderer::Create();
    m_GUI = GUI::Create();
}

void Application::Init() {
    m_Window->Init();
    m_Renderer->Init();
    ShaderProgramLibrary::Init(ASSET_DIRECTORY "shaders/shaders.yaml");
    INFO_MSG("Engine initialized");
    m_GUI->Init();

    m_Window->GetEventDispatcher()->Subscribe(EventCategoryKeyboard, BIND_EVENT_FN(Application::OnEvent));
}

void Application::Run() {
    if (m_Window == nullptr || m_Renderer == nullptr) {
        FATAL_MSG("Please, initialize the engine.");
    }

    World world;

    m_Renderer->SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    while (!m_Window->ShouldClose()) {
        Time::Update();
        m_Window->Update();

        m_Renderer->Clear();

        world.Draw();
        if (m_PauseMode) {
            m_GUI->Render();
        }

        m_Window->SwapBuffers();
    }

    m_GUI->Shutdown();
    m_Window->Shutdown();
}

void Application::OnEvent(const Event& event) {
    if (event.GetType() == EventType::KeyPressed) {
        const auto* keyEvent = dynamic_cast<const KeyPressedEvent*>(&event);
        if (keyEvent->GetKeyCode() == GLFW_KEY_ESCAPE) {
            if (m_PauseMode)
                m_PauseMode = false;
            else
                m_PauseMode = true;
        }
    }
}

Application* Application::GetInstance() {
    if (m_Instance == nullptr) {
        Log::Init();
        m_Instance = new Application();
    }
    return m_Instance;
}
