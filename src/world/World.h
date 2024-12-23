//
// Created by Romain on 22/12/2024.
//

#ifndef WORLD_H
#define WORLD_H

#include "Chunk.h"

class World {
   public:
    World();
    ~World() = default;

    void Draw();

   private:
    char m_RenderDistance;
    std::vector<Chunk> m_Chunks;
};

#endif  // WORLD_H
