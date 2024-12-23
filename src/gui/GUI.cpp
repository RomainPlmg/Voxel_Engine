//
// Created by Romain on 23/12/2024.
//

#include "GUI.h"

#include "core/Application.h"
#include "core/Window.h"
#include "gfx/GraphicContext.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void GUI::Init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    const ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF(ASSET_DIRECTORY "fonts/JetBrainsMono-Regular.ttf", 24.0f);
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(Application::GetInstance()->GetWindow()->GetHandler(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void GUI::Render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Créer un menu de base
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open")) {
                // Code pour ouvrir un fichier
            }
            if (ImGui::MenuItem("Save")) {
                // Code pour sauvegarder un fichier
            }
            if (ImGui::MenuItem("Exit")) {
                // Code pour quitter l'application
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo")) {
                // Code pour annuler
            }
            if (ImGui::MenuItem("Redo")) {
                // Code pour refaire
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

std::shared_ptr<GUI> GUI::Create() { return std::make_shared<GUI>(); }
