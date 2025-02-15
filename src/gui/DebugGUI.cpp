//
// Created by Romain on 30/12/2024.
//

#include "DebugGUI.h"

#include "IconsMaterialSymbols.h"
#include "core/Application.h"
#include "gfx/Renderer.h"
#include "imgui.h"
#include "utils/Log.h"
#include "utils/Monitor.h"
#include "utils/Time.h"
#include "world/Sun.h"
#include "world/World.h"

DebugGUI::DebugGUI() : m_PlayerPos(glm::vec3(0)), m_DebugLastFrameTime(0), m_DebugFPS(0.0), m_DebugDeltaTime(0.0) {}

void DebugGUI::Render() {
    ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    // Light color
    static float col[3] = {1.0f, 1.0f, 1.0f};
    ImGui::ColorEdit3(ICON_MS_PALETTE " Light color", col);
    Application::GetInstance()->GetWorld()->SetAmbiantLightColor(
        Color(col[0] * 255.0f, col[1] * 255.0f, col[2] * 255.0f));

    // Light strenght
    static float lightStrenght = 0.8f;
    ImGui::SliderFloat(ICON_MS_LIGHT_MODE " Light strenght", &lightStrenght, 0, 1, "%.3f");
    Application::GetInstance()->GetWorld()->SetAmbiantLightStrenght(lightStrenght);

    // Sun altitude
    static float altitude = 20.0f;
    ImGui::SliderFloat(ICON_MS_ALTITUDE " Sun altitude", &altitude, 0, 100, "%.2f");
    Application::GetInstance()->GetWorld()->GetSun()->SetAltitude(altitude);

    // Enable wireframe view
    static bool wireframe = false;
    ImGui::Checkbox("Wireframe", &wireframe);
    if (wireframe) {
        Application::GetInstance()->GetRenderer()->SetPolygonMode(GL_LINE);
    } else {
        Application::GetInstance()->GetRenderer()->SetPolygonMode(GL_FILL);
    }

    // Enable back face culling
    static bool backfaceCulling = true;
    ImGui::Checkbox("Backface Culling", &backfaceCulling);
    if (backfaceCulling) {
        Application::GetInstance()->GetRenderer()->SetBackfaceCulling(true);
    } else {
        Application::GetInstance()->GetRenderer()->SetBackfaceCulling(false);
    }

    // Print FPS
    if (static_cast<double>(Time::GetCurrentTime() - m_DebugLastFrameTime) /
            static_cast<double>(Time::GetCounterFreq()) >
        DEBUG_GUI_REFRESH_RATE) {
        m_DebugDeltaTime = static_cast<double>(Time::GetDeltaTime()) * 1000.0;
        m_DebugFPS = Time::GetFPS();

        m_DebugLastFrameTime = Time::GetCurrentTime();
    }
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", m_DebugDeltaTime, m_DebugFPS);

    // Print RAM consumption
    ImGui::Text("RAM: %d MB", Monitor::GetRAMConsumption() / 1000);

    // Print player position
    ImGui::Text("X: %f", m_PlayerPos.x);
    ImGui::Text("Y: %f", m_PlayerPos.y);
    ImGui::Text("Z: %f", m_PlayerPos.z);

    ImGui::Text("Triangle count: %.3fK",
                static_cast<double>(Application::GetInstance()->GetRenderer()->GetTriangleCount()) / 1000.0);

    ImGui::Text("Draw calls: %d", Application::GetInstance()->GetRenderer()->GetDrawCallCount());

    ImVec2 contentSize = ImGui::GetContentRegionAvail();
    contentSize.x = 200.0f;

    ImGui::SetWindowSize(contentSize, ImGuiCond_Once);

    ImGui::End();
}

void DebugGUI::SetPlayerPosition(glm::vec3 position) { m_PlayerPos = position; }

std::shared_ptr<DebugGUI> DebugGUI::Create() { return std::make_shared<DebugGUI>(); }
