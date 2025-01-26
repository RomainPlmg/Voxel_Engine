//
// Created by Romain on 30/12/2024.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "gfx/Camera.h"
#include "pch.h"

class Player {
   public:
    Player(glm::vec3 position = glm::vec3(0));
    ~Player() = default;

    void Init();
    void Update();

    /* Getters */
    glm::vec3 GetPosition() const { return m_Position; }

    static std::shared_ptr<Player> Create(glm::vec3 position = glm::vec3(0));

   private:
    float m_Speed;
    glm::vec3 m_Position;
    std::shared_ptr<Camera> m_Camera;
};

#endif  // PLAYER_H
