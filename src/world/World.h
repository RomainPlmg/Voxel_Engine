//
// Created by Romain on 22/12/2024.
//

#ifndef WORLD_H
#define WORLD_H

#include "Chunk.h"
#include "pch.h"
#include "utils/Color.h"

class Player;
class Sun;

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

    /* Getters */
    Color GetAmbiantLightColor() const { return m_AmbiantLightColor; }
    float GetAmbiantLightStrenght() const { return m_AmbiantLightStrenght; }
    std::unordered_map<glm::ivec2, Chunk, ivec2Hash> GetChunks() const { return m_Chunks; }
    std::shared_ptr<Player> GetPlayer() const { return m_Player; }
    std::shared_ptr<Sun> GetSun() const { return m_Sun; }

    /* Setters */
    void SetAmbiantLightColor(const Color& color) { m_AmbiantLightColor = color; }
    void SetAmbiantLightStrenght(float strenght) { m_AmbiantLightStrenght = strenght; }

    static std::shared_ptr<World> Create();

   private:
    uint16_t GetChunkIndex(const glm::ivec2& position) const;

    char m_RenderDistance;
    Color m_AmbiantLightColor;
    float m_AmbiantLightStrenght;
    std::unordered_map<glm::ivec2, Chunk, ivec2Hash> m_Chunks;
    std::shared_ptr<Player> m_Player;
    std::shared_ptr<Sun> m_Sun;
};

#endif  // WORLD_H
