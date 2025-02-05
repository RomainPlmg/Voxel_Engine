//
// Created by Romain on 20/12/2024.
//

#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Buffer.h"
#include "Camera.h"
#include "Shader.h"
#include "core/Application.h"
#include "core/Window.h"
#include "events/EventApplication.h"
#include "events/EventDispatcher.h"
#include "events/EventKeyboard.h"
#include "gfx/GraphicContext.h"
#include "utils/Log.h"
#include "world/World.h"

// Define the message callback function
static void OpenGLMessageCallback(unsigned source, unsigned type, unsigned id, unsigned severity, int length,
                                  const char* message, const void* userParam) {
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            FATAL_MSG(message);
        case GL_DEBUG_SEVERITY_MEDIUM:
            ERROR_MSG(message);
            return;
        case GL_DEBUG_SEVERITY_LOW:
            WARN_MSG(message);
            return;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            TRACE_MSG(message);
            return;
        default:
            break;
    }

    FATAL_MSG("Unknown severity level");
}

Renderer::Renderer() : m_ProjMatrix(glm::mat4(1.0f)), m_PolygonMode(GL_FILL), m_TriangleCount(0) {}

void Renderer::Init() {
    Application::GetInstance()->GetWindow()->GetEventDispatcher()->Subscribe(EventCategoryApplication,
                                                                             BIND_EVENT_FN(Renderer::OnEvent));
    Application::GetInstance()->GetWindow()->GetEventDispatcher()->Subscribe(EventCategoryKeyboard,
                                                                             BIND_EVENT_FN(Renderer::OnEvent));

    m_ProjMatrix = glm::perspective(glm::radians(45.0f),
                                    static_cast<float>(Application::GetInstance()->GetWindow()->GetWidth()) /
                                        static_cast<float>(Application::GetInstance()->GetWindow()->GetHeight()),
                                    0.1f, 300.0f);

#ifndef _NDEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(OpenGLMessageCallback, nullptr);  // Activate debug messages from OpenGL
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

    glEnable(GL_BLEND);  // Activate blending for object transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);  // Activate the depth buffer
    glEnable(GL_LINE_SMOOTH);

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
}

void Renderer::Render(const std::shared_ptr<ElementBuffer>& elementBuffer,
                      const std::shared_ptr<ShaderProgram>& shader) {
    if (elementBuffer->GetCount() == 0) {
        WARN_MSG("You are trying to draw an object with an empty ebo.")
    }

    m_TriangleCount += elementBuffer->GetCount() / 3;

    if (m_Camera == nullptr) {
        ERROR_MSG("You are trying to render without camera.")
        return;
    }

    shader->SetUniformMat4("projMatrix", m_ProjMatrix);
    shader->SetUniformMat4("viewMatrix", m_Camera->GetViewMatrix());
    shader->SetUniformFloat3("ambientLightColor",
                             Application::GetInstance()->GetWorld()->GetAmbiantLightColor().ToVec3());
    shader->SetUniformFloat("ambiantLightStrength", Application::GetInstance()->GetWorld()->GetAmbiantLightStrenght());

    m_DrawCallCount++;
    glDrawElements(GL_TRIANGLES, elementBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() {
    m_TriangleCount = 0;
    m_DrawCallCount = 0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::OnEvent(const Event& event) {
    if (event.GetType() == EventType::WindowResize) {
        const auto* wrEvent = dynamic_cast<const WindowResizeEvent*>(&event);
        SetViewport(wrEvent->width, wrEvent->height);

        const float matrixWidth = wrEvent->width <= 0 ? 1.0f : static_cast<float>(wrEvent->width);
        const float matrixHeight = wrEvent->height <= 0 ? 1.0f : static_cast<float>(wrEvent->height);
        m_ProjMatrix = glm::perspective(glm::radians(45.0f), matrixWidth / matrixHeight, 0.1f, 300.0f);
    }
    if (event.GetType() == EventType::KeyPressed) {
        const auto* keyEvent = dynamic_cast<const KeyPressedEvent*>(&event);
        if (keyEvent->GetKeyCode() == SDLK_F3) {
            if (m_PolygonMode == GL_FILL) {
                SetPolygonMode(GL_LINE);
            } else {
                SetPolygonMode(GL_FILL);
            }
        }
    }
}

void Renderer::SetPolygonMode(GLenum polygonMode) {
    if (m_PolygonMode == polygonMode) {
        return;
    }
    m_PolygonMode = polygonMode;
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
}

void Renderer::SetViewport(const int width, const int height) { glViewport(0, 0, width, height); }

void Renderer::SetClearColor(const float r, const float g, const float b, const float a) { glClearColor(r, g, b, a); }

void Renderer::SetCamera(const std::shared_ptr<Camera>& camera) { m_Camera = camera; }

void Renderer::SetBackfaceCulling(bool bfculling) {
    if (bfculling) {
        glEnable(GL_CULL_FACE);
    } else {
        glDisable(GL_CULL_FACE);
    }
}

std::shared_ptr<Renderer> Renderer::Create() { return std::make_shared<Renderer>(); }
