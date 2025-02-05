//
// Created by Romain on 23/12/2024.
//

#include "GUI.h"

#include "IconsMaterialSymbols.h"
#include "core/Application.h"
#include "core/Window.h"
#include "gfx/Buffer.h"
#include "gfx/GraphicContext.h"
#include "gfx/Renderer.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"

bool GUI::m_Open = true;

GUI::GUI() {
    m_FontSize = 15.0f;
    m_IconFontSize = m_FontSize * 1.2f;

    m_DebugGUI = DebugGUI::Create();
    m_ViewportGUI = ViewportGUI::Create();
}

void GUI::Init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF(ASSET_DIRECTORY "fonts/JetBrainsMono-Regular.ttf", m_FontSize);

    static const ImWchar icons_ranges[] = {ICON_MIN_MS, ICON_MAX_16_MS, 0};
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.GlyphMinAdvanceX = m_IconFontSize;

    io.Fonts->AddFontFromFileTTF(ASSET_DIRECTORY "fonts/" FONT_ICON_FILE_NAME_MSS, m_IconFontSize, &icons_config,
                                 icons_ranges);

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(Application::GetInstance()->GetWindow()->GetHandler(),
                                 Application::GetInstance()->GetWindow()->GetGraphicContext()->GetGLContext());
    ImGui_ImplOpenGL3_Init("#version 450");

    m_ViewportGUI->Init();
}

void GUI::Render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
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
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

std::shared_ptr<GUI> GUI::Create() { return std::make_shared<GUI>(); }
