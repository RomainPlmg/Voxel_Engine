//
// Created by Romain on 30/12/2024.
//

#include "Player.h"

#include "core/Application.h"
#include "gfx/Renderer.h"
#include "gui/GUI.h"

Player::Player(glm::vec3 position) : m_Speed(1), m_Position(position) { m_Camera = Camera::Create(position); }

void Player::Init() {
    m_Camera->Init();
    Application::GetInstance()->GetRenderer()->SetCamera(m_Camera);
}

void Player::Update() {
    m_Camera->Update();
    m_Position = m_Camera->GetPosition();
}

std::shared_ptr<Player> Player::Create(glm::vec3 position) { return std::make_shared<Player>(position); }
