//
// Created by Romain on 08/02/2025.
//

#include "Sun.h"

#include "Player.h"
#include "World.h"
#include "core/Application.h"
#include "gfx/Buffer.h"
#include "gfx/Renderer.h"
#include "gfx/Shader.h"
#include "gfx/VertexArray.h"
#include "glm/ext/matrix_transform.hpp"

// clang-format off
std::array<uint32_t, 36> Sun::m_Indices = {
    0, 1, 3,
    1, 2, 3,
    4, 5, 7,
    5, 6, 7,
    8, 9, 11,
    9, 10, 11,
    12, 13, 15,
    13, 14, 15,
    16, 17, 19,
    17, 18, 19,
    20, 21, 23,
    21, 22, 23
};
// clang-format on

Sun::Sun() : m_Altitude(20.0f), m_Angle(0.0f), m_Brightness(0.0f), m_Position(glm::vec3(0.0f)) {
    m_Position = glm::vec3(0.0f, m_Altitude, 0.0f);
    m_Shape = std::make_shared<Cube>(m_Position);

    for (int i = 0; i < 6; i++) {
        auto face = static_cast<Cube::Face>(i);
        for (int v = 0; v < 24; v = v + 6) {
            m_Vertices[i * 24 + v] = m_Shape->GetCubeVertices(face)[v];
            m_Vertices[i * 24 + v + 1] = m_Shape->GetCubeVertices(face)[v + 1];
            m_Vertices[i * 24 + v + 2] = m_Shape->GetCubeVertices(face)[v + 2];

            // Colors
            m_Vertices[i * 24 + v + 3] = Color::White.r;
            m_Vertices[i * 24 + v + 4] = Color::White.g;
            m_Vertices[i * 24 + v + 5] = Color::White.b;
        }
    }
}

void Sun::Init() { m_Shader = ShaderProgramLibrary::GetShaderProgram("LIGHT_SOURCE"); }

void Sun::Update() {
    auto playerPosition = Application::GetInstance()->GetWorld()->GetPlayer()->GetPosition();
    m_Position = glm::vec3(playerPosition.x, m_Altitude, playerPosition.z);
}

void Sun::Draw() {
    m_Shader->Bind();
    m_Shader->SetUniformMat4("modelMatrix",
                             glm::translate(glm::mat4(1.0f), glm::vec3(m_Position.x, m_Position.y, m_Position.z)));

    const auto vbo = VertexBuffer::Create(m_Vertices.data(), m_Vertices.size() * sizeof(m_Vertices[0]));
    vbo->SetLayout(m_Shader->GetBufferLayout());

    const auto ebo = ElementBuffer::Create(m_Indices.data(), m_Indices.size());

    const auto vao = VertexArray::Create();
    vao->AddVertexBuffer(vbo);
    vao->AddElementBuffer(ebo);

    Application::GetInstance()->GetRenderer()->Render(ebo, m_Shader);

    vao->Unbind();
    ebo->Unbind();
    vbo->Unbind();
    m_Shader->Unbind();
}

std::shared_ptr<Sun> Sun::Create() { return std::make_shared<Sun>(); }
