//
// Created by Romain on 22/12/2024.
//

#ifndef WORLD_H
#define WORLD_H

#include "Chunk.h"
#include "Player.h"
#include "pch.h"

class World {
   public:
    World();
    ~World() = default;

    void Init();
    void Update();
    void Draw();

    static std::shared_ptr<World> Create();

   private:
    char m_RenderDistance;
    std::vector<Chunk> m_Chunks;
    std::shared_ptr<Player> m_Player;
};

#endif  // WORLD_H
