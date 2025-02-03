//
// Created by Romain on 21/12/2024.
//

#include "Cube.h"

#include "gfx/Buffer.h"

// clang-format off
const std::unordered_map<Cube::Face, std::array<float, 12>> Cube::m_CommonVertices = {
        //--- Position ---//
    {Front, {
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
    }},
    {Back, {
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
    }},
    {Left, {
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    }},
    {Right, {
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
    }},
    {Top, {
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
    }},
    {Bottom, {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f
    }}
};
// clang-format on

Cube::Cube(const glm::ivec3 chunkPosition, Color color)
    : m_IsTransparent(false), m_ChunkPosition(chunkPosition), m_FacesToDraw(0b00000000), m_Color(color) {}

void Cube::SetFaceVisible(const Face& face) {
    const char mask = 1 << face;
    m_FacesToDraw = m_FacesToDraw | mask;  // Set the selected bit to 1 (Draw)
}

void Cube::SetFaceInvisible(const Face& face) {
    const char mask = ~(1 << face);
    m_FacesToDraw = m_FacesToDraw & mask;  // Set the selected bit to 0 (No draw)
}

void Cube::Transparent(bool isTransparent) { m_IsTransparent = isTransparent; }

void Cube::SetColor(const Color& color) { m_Color = color; }
