
// Created by Romain on 20/12/2024.
//

#include "Application.h"

#include "ThreadPool.h"
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
    m_World = World::Create();
    m_ThreadPool = ThreadPool::Create(8);
}

void Application::Init() {
    m_Window->Init();
    m_Renderer->Init();
    ShaderProgramLibrary::Init(ASSET_DIRECTORY "shaders/shaders.yaml");

    // To initialize AFTER shaders
    m_GUI->Init();

    INFO_MSG("Engine initialized");
    m_World->Init();

    m_Window->GetEventDispatcher()->Subscribe(EventCategoryKeyboard, BIND_EVENT_FN(Application::OnEvent));
}

void Application::Run() {
    if (m_Window == nullptr || m_Renderer == nullptr) {
        FATAL_MSG("Please, initialize the engine.");
    }

    m_Renderer->SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    while (!m_Window->ShouldClose()) {
        Time::Update();
        m_Window->Update();
        m_World->Update();

        m_GUI->Render();

        m_Window->SwapBuffers();
    }

    m_GUI->Shutdown();
    m_Window->Shutdown();
}

void Application::OnEvent(const Event& event) {}

Application* Application::GetInstance() {
    if (m_Instance == nullptr) {
        Log::Init();
        m_Instance = new Application();
    }
    return m_Instance;
}
