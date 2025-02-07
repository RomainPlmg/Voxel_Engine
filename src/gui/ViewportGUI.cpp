//
// Created by Romain on 30/01/2025.
//

#include "ViewportGUI.h"

#include <glm/gtc/matrix_transform.hpp>

#include "core/Application.h"
#include "core/Input.h"
#include "core/Window.h"
#include "events/EventDispatcher.h"
#include "gfx/Buffer.h"
#include "gfx/Camera.h"
#include "gfx/GraphicContext.h"
#include "gfx/Renderer.h"
#include "imgui.h"
#include "pch.h"
#include "world/World.h"

ViewportGUI::ViewportGUI() : m_ProjMatrix(glm::mat4(1.0f)) {}

void ViewportGUI::Init() { m_FrameBuffer = FrameBuffer::Create(1, 1); }

void ViewportGUI::Render() {
    ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
    ImVec2 oldViewPortSize = m_ViewportSize;
    m_ViewportSize = ImGui::GetContentRegionAvail();

    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Middle)) {
        Application::GetInstance()->GetRenderer()->GetCamera()->CaptureMouse();
    } else if (ImGui::IsMouseReleased(ImGuiMouseButton_Middle)) {
        Application::GetInstance()->GetRenderer()->GetCamera()->ReleaseMouse();
    }

    if (m_ViewportSize.x > 0 && m_ViewportSize.y > 0 &&
        (oldViewPortSize.x != m_ViewportSize.x || oldViewPortSize.y != m_ViewportSize.y)) {
        Application::GetInstance()->GetRenderer()->SetViewport(m_ViewportSize.x, m_ViewportSize.y);
        m_FrameBuffer->Resize(static_cast<int>(m_ViewportSize.x), static_cast<int>(m_ViewportSize.y));

        float aspectRatio = m_ViewportSize.x / m_ViewportSize.y;

        m_ProjMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 300.0f);
    }

    m_FrameBuffer->Bind();
    Application::GetInstance()->GetRenderer()->Clear();
    Application::GetInstance()->GetWorld()->Draw();
    m_FrameBuffer->Unbind();

    ImGui::Image((ImTextureID)(uintptr_t)m_FrameBuffer->GetColorTexture(), m_ViewportSize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
}

std::shared_ptr<ViewportGUI> ViewportGUI::Create() { return std::make_shared<ViewportGUI>(); }