//
// Created by Romain on 21/12/2024.
//

#ifndef CUBE_H
#define CUBE_H

#include "pch.h"

class ShaderProgram;

class Cube {
   public:
    explicit Cube(glm::ivec3 chunkPosition = glm::ivec3(0));
    ~Cube() = default;

    enum Face { Front = 0, Back, Left, Right, Top, Bottom };

    /* Getters */
    inline glm::ivec3 GetChunkPosition() const { return m_ChunkPosition; }
    inline bool IsTransparent() const { return m_IsTransparent; }
    static std::array<float, 24> GetCubeVertices(const Face& face) { return m_CommonVertices.at(face); }

    /* Setters */
    void SetFaceVisible(const Face& face);
    void SetFaceInvisible(const Face& face);

   private:
    static const std::unordered_map<Cube::Face, std::array<float, 24>> m_CommonVertices;

    bool m_IsTransparent;
    glm::ivec3 m_ChunkPosition;
    char m_FacesToDraw;
};

#endif  // CUBE_H
