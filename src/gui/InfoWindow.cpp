//
// Created by Romain on 30/12/2024.
//

#include "InfoWindow.h"

#include "imgui.h"
#include "utils/Log.h"
#include "utils/Monitor.h"
#include "utils/Time.h"

InfoWindow::InfoWindow() : m_PlayerPos(glm::vec3(0)) {}

void InfoWindow::Render() {
    ImGui::Begin("Info", nullptr,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse |
                     ImGuiWindowFlags_NoCollapse);

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

void InfoWindow::SetPlayerPosition(glm::vec3 position) { m_PlayerPos = position; }

std::shared_ptr<InfoWindow> InfoWindow::Create() { return std::make_shared<InfoWindow>(); }
