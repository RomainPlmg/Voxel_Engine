//
// Created by Romain on 08/02/2025.
//

#ifndef SUN_H
#define SUN_H

#include "pch.h"

class ShaderProgram;
class Cube;

class Sun {
   public:
    Sun();
    ~Sun() = default;

    void Init();
    void Update();
    void Draw();

    /* Getters */
    float GetAltitude() const { return m_Altitude; }
    float GetAngle() const { return m_Angle; }
    float GetBrightness() const { return m_Brightness; }
    glm::vec3 GetPosition() const { return m_Position; }

    /* Setters */
    void SetAltitude(float altitude) { m_Altitude = altitude; }

    static std::shared_ptr<Sun> Create();

   private:
    float m_Altitude;
    float m_Angle;
    float m_Brightness;

    glm::vec3 m_Position;

    std::shared_ptr<Cube> m_Shape;
    std::array<float, 144> m_Vertices;
    static std::array<uint32_t, 36> m_Indices;

    std::shared_ptr<ShaderProgram> m_Shader;
};

#endif