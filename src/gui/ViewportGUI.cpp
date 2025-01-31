//
// Created by Romain on 30/01/2025.
//

#include "ViewportGUI.h"

#include "core/Application.h"
#include "gfx/Buffer.h"
#include "gfx/Renderer.h"
#include "imgui.h"
#include "world/World.h"

ViewportGUI::ViewportGUI() {}

void ViewportGUI::Render() {
    ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
    m_ViewportSize = ImGui::GetContentRegionAvail();

    if (m_FrameBuffer == nullptr) {
        m_FrameBuffer = FrameBuffer::Create(static_cast<int>(m_ViewportSize.x), static_cast<int>(m_ViewportSize.y));
    }

    m_FrameBuffer->Bind();
    Application::GetInstance()->GetRenderer()->Clear();
    Application::GetInstance()->GetWorld()->Draw();
    m_FrameBuffer->Unbind();

    ImGui::Image((ImTextureID)(uintptr_t)m_FrameBuffer->GetColorTexture(), m_ViewportSize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
}

std::shared_ptr<ViewportGUI> ViewportGUI::Create() { return std::make_shared<ViewportGUI>(); }