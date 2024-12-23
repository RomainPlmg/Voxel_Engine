//
// Created by Romain on 21/12/2024.
//

#ifndef CHUNK_H
#define CHUNK_H

#include "world/Cube.h"

constexpr auto CHUNK_WIDTH = 8;
constexpr auto CHUNK_HEIGHT = 16;

class Chunk {
   public:
    explicit Chunk(glm::ivec2 position = glm::ivec2(0));
    ~Chunk() = default;

    void Update();
    void Draw();

    /* Getters */
    [[nodiscard]] std::shared_ptr<Cube> GetCubeAtPosition(const glm::ivec3& cubePosition) const;

   private:
    bool FaceHasNeighbor(const std::shared_ptr<Cube>& cube, const Cube::Face& face);
    bool FaceIsBoundary(const std::shared_ptr<Cube>& cube, const Cube::Face& face);
    void AddFaceToVertices(const std::shared_ptr<Cube>& cube, const Cube::Face& face);
    void AddFaceToIndices();

    glm::ivec2 m_WorldPosition;
    std::array<std::shared_ptr<Cube>, CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT> m_Cubes;
    std::shared_ptr<ShaderProgram> m_Shader;
    std::vector<float> m_Vertices;
    std::vector<uint32_t> m_Indices;
};

#endif  // CHUNK_H
