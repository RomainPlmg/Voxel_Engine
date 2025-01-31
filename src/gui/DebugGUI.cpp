//
// Created by Romain on 30/12/2024.
//

#include "DebugGUI.h"

#include "imgui.h"
#include "utils/Log.h"
#include "utils/Monitor.h"
#include "utils/Time.h"

DebugGUI::DebugGUI() : m_PlayerPos(glm::vec3(0)) {}

void DebugGUI::Render() {
    ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    // Print FPS
    ImGui::Text("FPS: %d", Time::GetFPS());

    // Print RAM consumption
    ImGui::Text("RAM: %d MB", Monitor::GetRAMConsumption() / 1000);

    // Print player position
    ImGui::Text("X: %f", m_PlayerPos.x);
    ImGui::Text("Y: %f", m_PlayerPos.y);
    ImGui::Text("Z: %f", m_PlayerPos.z);

    ImVec2 contentSize = ImGui::GetContentRegionAvail();
    contentSize.x = 200.0f;

    ImGui::SetWindowSize(contentSize, ImGuiCond_Once);

    ImGui::End();
}

void DebugGUI::SetPlayerPosition(glm::vec3 position) { m_PlayerPos = position; }

std::shared_ptr<DebugGUI> DebugGUI::Create() { return std::make_shared<DebugGUI>(); }
