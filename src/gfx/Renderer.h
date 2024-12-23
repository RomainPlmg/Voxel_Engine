//
// Created by Romain on 20/12/2024.
//

#ifndef RENDERER_H
#define RENDERER_H

class ShaderProgram;
class ElementBuffer;
class Event;
class Camera;

class Renderer {
   public:
    Renderer();
    ~Renderer() = default;

    void Init();
    void Render(const std::shared_ptr<ElementBuffer>& elementBuffer,
                const std::shared_ptr<ShaderProgram>& shader) const;
    void Clear();

    void OnEvent(const Event& event);

    /* Setters */
    void SetViewport(int width, int height);
    void SetClearColor(float r, float g, float b, float a);

    static std::shared_ptr<Renderer> Create();

   private:
    bool m_WireMode;
    glm::mat4 m_ProjMatrix;
    std::shared_ptr<Camera> m_Camera;
};

#endif  // RENDERER_H
