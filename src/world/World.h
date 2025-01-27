//
// Created by Romain on 22/12/2024.
//

#ifndef WORLD_H
#define WORLD_H

#include "Chunk.h"
#include "Player.h"
#include "pch.h"

struct ivec2Hash {
    size_t operator()(const glm::ivec2& v) const { return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1); }
};

class World {
   public:
    World();
    ~World() = default;

    void Init();
    void Update();
    void Draw();

    static std::shared_ptr<World> Create();

   private:
    void UpdateBoundaryFaces(Chunk& chunk, bool recursive = true);
    uint16_t GetChunkIndex(const glm::ivec2& position) const;

    char m_RenderDistance;
    std::unordered_map<glm::ivec2, Chunk, ivec2Hash> m_Chunks;
    std::shared_ptr<Player> m_Player;
};

#endif  // WORLD_H
