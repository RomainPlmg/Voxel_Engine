//
// Created by Romain on 23/12/2024.
//

#include "GUI.h"

#include "core/Application.h"
#include "core/Window.h"
#include "gfx/Buffer.h"
#include "gfx/Renderer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

bool GUI::m_Open = true;

GUI::GUI() {
    m_DebugGUI = DebugGUI::Create();
    m_ViewportGUI = ViewportGUI::Create();
}

void GUI::Init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF(ASSET_DIRECTORY "fonts/JetBrainsMono-Regular.ttf", 24.0f);
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(Application::GetInstance()->GetWindow()->GetHandler(), true);
    ImGui_ImplOpenGL3_Init("#version 450");

    m_ViewportGUI->Init();
}

void GUI::Render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

    m_ViewportGUI->Render();
    m_DebugGUI->Render();

    ImGui::Render();
    Application::GetInstance()->GetRenderer()->Clear();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

std::shared_ptr<GUI> GUI::Create() { return std::make_shared<GUI>(); }
