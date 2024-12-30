//
// Created by Romain on 30/12/2024.
//

#include "Player.h"

#include "core/Application.h"
#include "gfx/Renderer.h"

Player::Player() : m_Speed(1), m_Position(glm::vec3(0)) { m_Camera = Camera::Create(); }

void Player::Init() {
    m_Camera->Init();
    Application::GetInstance()->GetRenderer()->SetCamera(m_Camera);
}

void Player::Update() {
    m_Camera->Update();
    m_Position = m_Camera->GetPosition();
}

std::shared_ptr<Player> Player::Create() { return std::make_shared<Player>(); }
