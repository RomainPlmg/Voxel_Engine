//
// Created by Romain on 22/12/2024.
//

#include "World.h"

#include "Chunk.h"
#include "Player.h"
#include "Sun.h"
#include "core/Application.h"
#include "gui/GUI.h"

World::World() : m_RenderDistance(8), m_AmbiantLightStrenght(1.0f) {
    m_Player = Player::Create(glm::vec3(0.0f, CHUNK_HEIGHT + 2, 0.0f));
    m_Sun = Sun::Create();
}

void World::Init() {
    m_Player->Init();
    m_Sun->Init();

    int radius = m_RenderDistance / 2;

    for (int x = -radius; x < radius; x++) {
        for (int y = -radius; y < radius; y++) {
            auto position = glm::ivec2(x, y);
            m_Chunks[position] = Chunk(position);
            m_Chunks[position].Update();
        }
    }
}

void World::Update() {
    m_Player->Update();
    m_Sun->Update();
    Application::GetInstance()->GetGUI()->GetDebugGUI()->SetPlayerPosition(m_Player->GetPosition());

    glm::ivec2 playerChunk = glm::ivec2(std::floor((m_Player->GetPosition().x + CHUNK_WIDTH / 2.0f) / CHUNK_WIDTH),
                                        std::floor((m_Player->GetPosition().z + CHUNK_WIDTH / 2.0f) / CHUNK_WIDTH));

    int radius = m_RenderDistance / 2;
    for (int x = -radius; x <= radius; ++x) {
        for (int y = -radius; y <= radius; ++y) {
            glm::ivec2 chunkPos = glm::ivec2(playerChunk.x + x, playerChunk.y + y);
            if (m_Chunks.find(chunkPos) == m_Chunks.end()) {
                m_Chunks[chunkPos] = Chunk(chunkPos);
                m_Chunks[chunkPos].Update();
            }
        }
    }

    for (auto it = m_Chunks.begin(); it != m_Chunks.end();) {
        const glm::ivec2 chunkPos = it->first;
        if (std::abs(chunkPos.x - playerChunk.x) > radius || std::abs(chunkPos.y - playerChunk.y) > radius) {
            it = m_Chunks.erase(it);
        } else {
            it++;
        }
    }
}

void World::Draw() {
    m_Sun->Draw();
    for (auto& pair : m_Chunks) {
        pair.second.Draw();
    }
}

std::shared_ptr<World> World::Create() { return std::make_shared<World>(); }

uint16_t World::GetChunkIndex(const glm::ivec2& position) const {
    int chunkX = position.x / CHUNK_WIDTH;
    int chunkY = position.y / CHUNK_WIDTH;
    return chunkY * (position.x / CHUNK_WIDTH) + chunkX;
}
