//
// Created by Romain on 21/12/2024.
//

#ifndef SHADER_H
#define SHADER_H

#include "pch.h"

typedef unsigned int GLenum;
class BufferLayout;
struct BufferElement;

struct Shader {
    GLenum type;
    std::string file;
};

class ShaderProgram {
   public:
    ShaderProgram(const std::string& name, const std::vector<Shader>& shaders,
                  const std::vector<BufferElement>& bufferElements);
    ~ShaderProgram();

    void Bind() const;
    void Unbind() const;

    /* Utility uniform functions */
    void SetUniformInt(const std::string& name, int value) const;
    void SetUniformIntArray(const std::string& name, int* values, uint32_t count) const;
    void SetUniformFloat(const std::string& name, float value) const;
    void SetUniformFloat2(const std::string& name, const glm::vec2& value) const;
    void SetUniformFloat3(const std::string& name, const glm::vec3& value) const;
    void SetUniformFloat4(const std::string& name, const glm::vec4& value) const;
    void SetUniformMat4(const std::string& name, const glm::mat4& value) const;

    /* Getters */
    inline const std::string& GetName() const { return m_Name; }
    inline std::shared_ptr<BufferLayout> GetBufferLayout() const { return m_BufferLayout; }

    static GLenum ShaderTypeFromString(const std::string& typeStr);
    static std::shared_ptr<ShaderProgram> Create(const std::string& name, const std::vector<Shader>& shaders,
                                                 const std::vector<BufferElement>& bufferElements);

   private:
    uint32_t m_RendererID;
    std::string m_Name;
    std::shared_ptr<BufferLayout> m_BufferLayout;

    static uint32_t CompileShader(const Shader& shader);
};

class ShaderProgramLibrary {
   public:
    ShaderProgramLibrary() = default;
    ~ShaderProgramLibrary() = default;

    static void Init(const std::string& YamlPath);
    static std::shared_ptr<ShaderProgram> GetShaderProgram(const std::string& name);

   private:
    static std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> m_Shaders;
};

#endif  // SHADER_H
