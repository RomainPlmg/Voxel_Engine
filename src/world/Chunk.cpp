//
// Created by Romain on 21/12/2024.
//

#include "Chunk.h"

#include "Sun.h"
#include "World.h"
#include "core/Application.h"
#include "gfx/Renderer.h"
#include "gfx/Shader.h"
#include "gfx/VertexArray.h"
#include "glm/ext/matrix_transform.hpp"
#include "gui/GUI.h"

Chunk::Chunk(const glm::ivec2 position) : m_WorldPosition(position) {
    m_Shader = ShaderProgramLibrary::GetShaderProgram("BASIC");

    for (int y = 0; y < CHUNK_HEIGHT; y++) {
        for (int z = 0; z < CHUNK_WIDTH; z++) {
            for (int x = 0; x < CHUNK_WIDTH; x++) {
                const int i = x + CHUNK_WIDTH * (y + CHUNK_HEIGHT * z);
                m_Cubes[i] = std::make_shared<Cube>(glm::ivec3(x, y, z), Color::White);
            }
        }
    }
}

void Chunk::Update() {
    m_Vertices.clear();
    m_Indices.clear();

    for (const auto& cube : m_Cubes) {
        for (int i = 0; i < 6; i++) {
            auto face = static_cast<Cube::Face>(i);
            if ((cube->GetChunkPosition().y == CHUNK_HEIGHT - 1 && face == Cube::Face::Top)) {
                cube->SetFaceVisible(face);
            }
        }
        if (!cube->IsTransparent()) {
            for (int i = 0; i < 6; i++) {
                auto face = static_cast<Cube::Face>(i);
                if (!FaceIsBoundary(cube, face) && !FaceHasNeighbor(cube, face)) {
                    cube->SetFaceVisible(face);
                }
                if (cube->GetFacesToDraw() & (1 << i)) {
                    AddFaceToVertices(cube, face);
                    AddFaceToIndices();
                }
            }
        }
    }

    auto world = Application::GetInstance()->GetWorld();
    UpdateBoundaryFaces(world);
}

void Chunk::Draw() {
    if (m_Vertices.empty()) {
        return;
    }

    m_Shader->Bind();
    m_Shader->SetUniformMat4(
        "modelMatrix",
        glm::translate(glm::mat4(1.0f), glm::vec3(static_cast<float>(m_WorldPosition.x * CHUNK_WIDTH), 0.0f,
                                                  static_cast<float>(m_WorldPosition.y * CHUNK_WIDTH))));
    m_Shader->SetUniformFloat3("ambientLightColor",
                               Application::GetInstance()->GetWorld()->GetAmbiantLightColor().ToVec3());
    m_Shader->SetUniformFloat("ambiantLightStrength",
                              Application::GetInstance()->GetWorld()->GetAmbiantLightStrenght());

    // Set the sun position in the shader
    auto sun = Application::GetInstance()->GetWorld()->GetSun();
    m_Shader->SetUniformFloat3("lightPos", sun->GetPosition());

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

std::shared_ptr<Cube> Chunk::GetCubeAtPosition(const glm::ivec3& cubePosition) const {
    int i = cubePosition.x + CHUNK_WIDTH * (cubePosition.y + CHUNK_HEIGHT * cubePosition.z);
    if (i > CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT) {
        WARN_MSG("Index {} is out of bounds of the this->", i);
        return nullptr;
    }
    return m_Cubes[i];
}

void Chunk::UpdateBoundaryFaces(std::shared_ptr<World> world) {
    auto chunks = world->GetChunks();

    auto rightChunk = chunks.find(glm::ivec2(this->GetWorldPosition().x + 1, this->GetWorldPosition().y));  // Right
    auto leftChunk = chunks.find(glm::ivec2(this->GetWorldPosition().x - 1, this->GetWorldPosition().y));   // Left
    auto frontChunk = chunks.find(glm::ivec2(this->GetWorldPosition().x, this->GetWorldPosition().y + 1));  // Front
    auto backChunk = chunks.find(glm::ivec2(this->GetWorldPosition().x, this->GetWorldPosition().y - 1));   // Back

    for (const auto& cube : this->GetBoundaryCubes()) {  // Recover all boundary cubes
        for (int i = 0; i < 6; i++) {
            auto face = static_cast<Cube::Face>(i);
            if (cube->GetChunkPosition().x == CHUNK_WIDTH - 1 && face == Cube::Face::Right) {
                if (rightChunk != chunks.end() &&
                    rightChunk->second
                        .GetCubeAtPosition(glm::ivec3(0, cube->GetChunkPosition().y, cube->GetChunkPosition().z))
                        ->IsTransparent()) {
                    cube->SetFaceVisible(face);
                }
            }
            if (cube->GetChunkPosition().x == 0 && face == Cube::Face::Left) {
                if (leftChunk != chunks.end() &&
                    leftChunk->second
                        .GetCubeAtPosition(
                            glm::ivec3(CHUNK_WIDTH - 1, cube->GetChunkPosition().y, cube->GetChunkPosition().z))
                        ->IsTransparent()) {
                    cube->SetFaceVisible(face);
                }
            }
            if (cube->GetChunkPosition().z == CHUNK_WIDTH - 1 && face == Cube::Face::Front) {
                if (frontChunk != chunks.end() &&
                    frontChunk->second
                        .GetCubeAtPosition(glm::ivec3(cube->GetChunkPosition().x, cube->GetChunkPosition().y, 0))
                        ->IsTransparent()) {
                    cube->SetFaceVisible(face);
                }
            }
            if (cube->GetChunkPosition().z == 0 && face == Cube::Face::Back) {
                if (backChunk != chunks.end() &&
                    backChunk->second
                        .GetCubeAtPosition(
                            glm::ivec3(cube->GetChunkPosition().x, cube->GetChunkPosition().y, CHUNK_WIDTH - 1))
                        ->IsTransparent()) {
                    cube->SetFaceVisible(face);
                }
            }
        }
    }
}

bool Chunk::FaceHasNeighbor(const std::shared_ptr<Cube>& cube, const Cube::Face& face) const {
    const auto cubePos = cube->GetChunkPosition();
    std::shared_ptr<Cube> neighborCube;

    switch (face) {
        case Cube::Face::Front:
            neighborCube = GetCubeAtPosition(glm::ivec3(cubePos.x, cubePos.y, cubePos.z + 1));
            if (neighborCube != nullptr && !neighborCube->IsTransparent()) {
                return true;
            }
            break;
        case Cube::Face::Back:
            neighborCube = GetCubeAtPosition(glm::ivec3(cubePos.x, cubePos.y, cubePos.z - 1));
            if (neighborCube != nullptr && !neighborCube->IsTransparent()) {
                return true;
            }
            break;
        case Cube::Face::Left:
            neighborCube = GetCubeAtPosition(glm::ivec3(cubePos.x - 1, cubePos.y, cubePos.z));
            if (neighborCube != nullptr && !neighborCube->IsTransparent()) {
                return true;
            }
            break;
        case Cube::Face::Right:
            neighborCube = GetCubeAtPosition(glm::ivec3(cubePos.x + 1, cubePos.y, cubePos.z));
            if (neighborCube != nullptr && !neighborCube->IsTransparent()) {
                return true;
            }
            break;
        case Cube::Face::Top:
            neighborCube = GetCubeAtPosition(glm::ivec3(cubePos.x, cubePos.y + 1, cubePos.z));
            if (neighborCube != nullptr && !neighborCube->IsTransparent()) {
                return true;
            }
            break;
        case Cube::Face::Bottom:
            neighborCube = GetCubeAtPosition(glm::ivec3(cubePos.x, cubePos.y - 1, cubePos.z));
            if (neighborCube != nullptr && !neighborCube->IsTransparent()) {
                return true;
            }
            break;
        default:
            break;
    }

    return false;
}

bool Chunk::FaceIsBoundary(const std::shared_ptr<Cube>& cube, const Cube::Face& face) {
    switch (face) {
        case Cube::Face::Front:
            if (cube->GetChunkPosition().z == CHUNK_WIDTH - 1) {
                m_BoundaryCubes.push_back(cube);
                return true;
            }
            break;
        case Cube::Face::Back:
            if (cube->GetChunkPosition().z == 0) {
                m_BoundaryCubes.push_back(cube);
                return true;
            }
            break;
        case Cube::Face::Left:
            if (cube->GetChunkPosition().x == 0) {
                m_BoundaryCubes.push_back(cube);
                return true;
            }
            break;
        case Cube::Face::Right:
            if (cube->GetChunkPosition().x == CHUNK_WIDTH - 1) {
                m_BoundaryCubes.push_back(cube);
                return true;
            }
            break;
        case Cube::Face::Top:
            if (cube->GetChunkPosition().y == CHUNK_HEIGHT - 1) {
                m_BoundaryCubes.push_back(cube);
                return true;
            }
            break;
        case Cube::Face::Bottom:
            if (cube->GetChunkPosition().y == 0) {
                m_BoundaryCubes.push_back(cube);
                return true;
            }
            break;
        default:
            break;
    }

    return false;
}

void Chunk::AddFaceToVertices(const std::shared_ptr<Cube>& cube, const Cube::Face& face) {
    const auto vertices = Cube::GetCubeVertices(face);
    for (int i = 0; i < Cube::GetCubeVertices(face).size(); i = i + 6) {
        // Vertex coordinates
        m_Vertices.push_back(vertices[i] + cube->GetChunkPosition().x);      // X
        m_Vertices.push_back(vertices[i + 1] + cube->GetChunkPosition().y);  // Y
        m_Vertices.push_back(vertices[i + 2] + cube->GetChunkPosition().z);  // Z

        // Normals
        m_Vertices.push_back(vertices[i + 3] + cube->GetChunkPosition().x);  // X
        m_Vertices.push_back(vertices[i + 4] + cube->GetChunkPosition().y);  // Y
        m_Vertices.push_back(vertices[i + 5] + cube->GetChunkPosition().z);  // Z

        // Vertex colors
        Color color = cube->GetColor().ToGLColor();
        m_Vertices.push_back(color.r);  // R
        m_Vertices.push_back(color.g);  // G
        m_Vertices.push_back(color.b);  // B
    }
}

void Chunk::AddFaceToIndices() {
    int indexStart = 0;

    if (m_Indices.size() != 0) {
        indexStart = m_Indices.back() + 1;
    }

    m_Indices.push_back(indexStart);
    m_Indices.push_back(indexStart + 1);
    m_Indices.push_back(indexStart + 3);

    m_Indices.push_back(indexStart + 1);
    m_Indices.push_back(indexStart + 2);
    m_Indices.push_back(indexStart + 3);
}
