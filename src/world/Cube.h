//
// Created by Romain on 21/12/2024.
//

#ifndef CUBE_H
#define CUBE_H

#include "pch.h"
#include "utils/Color.h"

class ShaderProgram;

class Cube {
   public:
    Cube(glm::ivec3 chunkPosition = glm::ivec3(0), Color color = Color::Black);
    ~Cube() = default;

    enum Face { Front = 0, Back, Left, Right, Top, Bottom };

    /* Getters */
    inline glm::ivec3 GetChunkPosition() const { return m_ChunkPosition; }
    inline char GetFacesToDraw() const { return m_FacesToDraw; }
    inline bool IsTransparent() const { return m_IsTransparent; }
    static std::array<float, 12> GetCubeVertices(const Face& face) { return m_CommonVertices.at(face); }
    Color GetColor() const { return m_Color; }

    /* Setters */
    void SetFaceVisible(const Face& face);
    void SetFaceInvisible(const Face& face);
    void Transparent(bool isTransparent);
    void SetColor(const Color& color);

   private:
    static const std::unordered_map<Cube::Face, std::array<float, 12>> m_CommonVertices;

    bool m_IsTransparent;
    Color m_Color;
    glm::ivec3 m_ChunkPosition;
    char m_FacesToDraw;
};

#endif  // CUBE_H
