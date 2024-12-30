//
// Created by Romain on 22/12/2024.
//

#include "World.h"

#include "core/Application.h"
#include "gui/GUI.h"

World::World() : m_RenderDistance(16) { m_Player = Player::Create(); }

void World::Init() {
    m_Player->Init();

    for (int x = -m_RenderDistance / 2; x < m_RenderDistance / 2; x++) {
        for (int y = -m_RenderDistance / 2; y < m_RenderDistance / 2; y++) {
            m_Chunks.emplace_back(glm::ivec2(x, y));
        }
    }
}

void World::Update() {
    m_Player->Update();
    Application::GetInstance()->GetGUI()->GetInfoWindow()->SetPlayerPosition(m_Player->GetPosition());
}

void World::Draw() {
    for (auto& chunk : m_Chunks) {
        chunk.Draw();
    }
}

std::shared_ptr<World> World::Create() { return std::make_shared<World>(); }
