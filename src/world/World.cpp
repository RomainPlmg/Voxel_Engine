//
// Created by Romain on 22/12/2024.
//

#include "World.h"

#include "spdlog/fmt/bundled/base.h"

World::World() : m_RenderDistance(16) {
    for (int x = -m_RenderDistance / 2; x < m_RenderDistance / 2; x++) {
        for (int y = -m_RenderDistance / 2; y < m_RenderDistance / 2; y++) {
            m_Chunks.emplace_back(glm::ivec2(x, y));
        }
    }
}

void World::Draw() {
    for (auto& chunk : m_Chunks) {
        chunk.Draw();
    }
}
