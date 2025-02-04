//
// Created by Romain on 30/01/2025.
//

#include "ViewportGUI.h"

#include "core/Application.h"
#include "core/Input.h"
#include "core/Window.h"
#include "events/EventDispatcher.h"
#include "gfx/Buffer.h"
#include "gfx/GraphicContext.h"
#include "gfx/Renderer.h"
#include "imgui.h"
#include "pch.h"
#include "world/World.h"

void ViewportGUI::Init() {
    Application::GetInstance()->GetWindow()->GetEventDispatcher()->Subscribe(EventCategory::EventCategoryMouse,
                                                                             BIND_EVENT_FN(ViewportGUI::OnEvent));
    m_FrameBuffer = FrameBuffer::Create(1, 1);
}

void ViewportGUI::Render() {
    ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
    ImVec2 oldViewPortSize = m_ViewportSize;
    m_ViewportSize = ImGui::GetContentRegionAvail();
    m_ViewportPos = ImGui::GetWindowPos();

    m_FrameBuffer->Bind();
    if (m_ViewportSize.x > 0 && m_ViewportSize.y > 0 &&
        (oldViewPortSize.x != m_ViewportSize.x || oldViewPortSize.y != m_ViewportSize.y)) {
        m_FrameBuffer->Resize(static_cast<int>(m_ViewportSize.x), static_cast<int>(m_ViewportSize.y));
    }
    Application::GetInstance()->GetRenderer()->Clear();
    Application::GetInstance()->GetWorld()->Draw();
    m_FrameBuffer->Unbind();

    ImGui::Image((ImTextureID)(uintptr_t)m_FrameBuffer->GetColorTexture(), m_ViewportSize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
}

void ViewportGUI::OnEvent(const Event& event) {
    auto window = Application::GetInstance()->GetWindow();

    if (event.GetType() == EventType::MouseButtonPressed) {
        glm::dvec2 mousePos = Input::GetMousePosition();
        if (mousePos.x > m_ViewportPos.x && mousePos.x < m_ViewportSize.x - m_ViewportPos.x) {
            if (mousePos.y > m_ViewportPos.y && mousePos.y < m_ViewportSize.y - m_ViewportPos.y) {
                glfwSetInputMode(window->GetHandler(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                Application::GetInstance()->GetRenderer()->GetCamera()->CaptureMouse();
            }
        }
    }

    if (event.GetType() == EventType::MouseButtonReleased) {
        glfwSetInputMode(window->GetHandler(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        Application::GetInstance()->GetRenderer()->GetCamera()->ReleaseMouse();
    }
}

std::shared_ptr<ViewportGUI> ViewportGUI::Create() { return std::make_shared<ViewportGUI>(); }