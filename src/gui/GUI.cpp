//
// Created by Romain on 23/12/2024.
//

#include "GUI.h"

#include "core/Application.h"
#include "core/Window.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

GUI::GUI() { m_InfoWindow = InfoWindow::Create(); }

void GUI::Init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    const ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF(ASSET_DIRECTORY "fonts/JetBrainsMono-Regular.ttf", 24.0f);
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(Application::GetInstance()->GetWindow()->GetHandler(), true);
    ImGui_ImplOpenGL3_Init("#version 450");
}

void GUI::Render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    m_InfoWindow->Render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

std::shared_ptr<GUI> GUI::Create() { return std::make_shared<GUI>(); }
