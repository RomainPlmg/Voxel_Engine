//
// Created by Romain on 22/12/2024.
//

#include "World.h"

#include "core/Application.h"
#include "gui/GUI.h"

World::World() : m_RenderDistance(16) { m_Player = Player::Create(glm::vec3(0.0f, CHUNK_HEIGHT + 2, 0.0f)); }

void World::Init() {
    m_Player->Init();

    for (int x = -m_RenderDistance / 2; x < m_RenderDistance / 2; x++) {
        for (int y = -m_RenderDistance / 2; y < m_RenderDistance / 2; y++) {
            m_Chunks[glm::ivec2(x, y)] = Chunk(glm::ivec2(x, y));
            m_Chunks[glm::ivec2(x, y)].GetCubeAtPosition(glm::ivec3(0, CHUNK_HEIGHT - 1, 0))->Transparent(true);
            m_Chunks[glm::ivec2(x, y)].Update();
        }
    }

    for (auto& pair : m_Chunks) {
        UpdateBoundaryFaces(pair.second);
    }
}

void World::Update() {
    m_Player->Update();
    Application::GetInstance()->GetGUI()->GetInfoWindow()->SetPlayerPosition(m_Player->GetPosition());
}

void World::Draw() {
    for (auto& pair : m_Chunks) {
        pair.second.Draw();
    }
}

std::shared_ptr<World> World::Create() { return std::make_shared<World>(); }

void World::UpdateBoundaryFaces(Chunk& chunk) {
    auto rightChunk = m_Chunks.find(glm::ivec2(chunk.GetWorldPosition().x + 1, chunk.GetWorldPosition().y));  // Right
    auto leftChunk = m_Chunks.find(glm::ivec2(chunk.GetWorldPosition().x - 1, chunk.GetWorldPosition().y));   // Left
    auto frontChunk = m_Chunks.find(glm::ivec2(chunk.GetWorldPosition().x, chunk.GetWorldPosition().y + 1));  // Front
    auto backChunk = m_Chunks.find(glm::ivec2(chunk.GetWorldPosition().x, chunk.GetWorldPosition().y - 1));   // Back

    for (const auto& cube : chunk.GetBoundaryCubes()) {
        for (int i = 0; i < 6; i++) {
            auto face = static_cast<Cube::Face>(i);
            if (cube->GetChunkPosition().x == CHUNK_WIDTH - 1 && face == Cube::Face::Right) {
                if (rightChunk != m_Chunks.end() &&
                    rightChunk->second
                        .GetCubeAtPosition(glm::ivec3(0, cube->GetChunkPosition().y, cube->GetChunkPosition().z))
                        ->IsTransparent()) {
                    cube->SetFaceVisible(face);
                }
            }
            if (cube->GetChunkPosition().x == 0 && face == Cube::Face::Left) {
                if (leftChunk != m_Chunks.end() &&
                    leftChunk->second
                        .GetCubeAtPosition(
                            glm::ivec3(CHUNK_WIDTH - 1, cube->GetChunkPosition().y, cube->GetChunkPosition().z))
                        ->IsTransparent()) {
                    cube->SetFaceVisible(face);
                }
            }
            if (cube->GetChunkPosition().z == CHUNK_WIDTH - 1 && face == Cube::Face::Front) {
                if (frontChunk != m_Chunks.end() &&
                    frontChunk->second
                        .GetCubeAtPosition(glm::ivec3(cube->GetChunkPosition().x, cube->GetChunkPosition().y, 0))
                        ->IsTransparent()) {
                    cube->SetFaceVisible(face);
                }
            }
            if (cube->GetChunkPosition().z == 0 && face == Cube::Face::Back) {
                if (backChunk != m_Chunks.end() &&
                    backChunk->second
                        .GetCubeAtPosition(
                            glm::ivec3(cube->GetChunkPosition().x, cube->GetChunkPosition().y, CHUNK_WIDTH - 1))
                        ->IsTransparent()) {
                    cube->SetFaceVisible(face);
                }
            }
        }
    }

    chunk.Update();
}

uint16_t World::GetChunkIndex(const glm::ivec2& position) const {
    int chunkX = position.x / CHUNK_WIDTH;
    int chunkY = position.y / CHUNK_WIDTH;
    return chunkY * (position.x / CHUNK_WIDTH) + chunkX;
}
