//
// Created by Romain on 20/12/2024.
//

#ifndef RENDERER_H
#define RENDERER_H

#include "pch.h"

class ShaderProgram;
class ElementBuffer;
class Event;
class Camera;
typedef unsigned int GLenum;

class Renderer {
   public:
    Renderer();
    ~Renderer() = default;

    void Init();
    void Render(const std::shared_ptr<ElementBuffer>& elementBuffer, const std::shared_ptr<ShaderProgram>& shader);
    void Clear();

    void OnEvent(const Event& event);

    /* Getters */
    std::shared_ptr<Camera> GetCamera() const { return m_Camera; }
    unsigned long GetTriangleCount() const { return m_TriangleCount; }

    /* Setters */
    void SetPolygonMode(GLenum polygonMode);
    void SetViewport(int width, int height);
    void SetClearColor(float r, float g, float b, float a);
    void SetCamera(const std::shared_ptr<Camera>& camera);

    static std::shared_ptr<Renderer> Create();

   private:
    GLenum m_PolygonMode;
    glm::mat4 m_ProjMatrix;
    std::shared_ptr<Camera> m_Camera;
    unsigned long m_TriangleCount;
};

#endif  // RENDERER_H
