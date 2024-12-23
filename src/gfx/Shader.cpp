//
// Created by Romain on 21/12/2024.
//

#include "Shader.h"

#include <yaml-cpp/yaml.h>

#include <glm/gtc/type_ptr.hpp>

#include "Buffer.h"
#include "GraphicContext.h"
#include "utils/File.h"
#include "utils/Log.h"

/* Shader */
ShaderProgram::ShaderProgram(const std::string& name, const std::vector<Shader>& shaders,
                             const std::vector<BufferElement>& bufferElements)
    : m_Name(name) {
    m_RendererID = glCreateProgram();

    const auto shaderIDs = new uint32_t[shaders.size()];
    for (int i = 0; i < shaders.size(); i++) {
        shaderIDs[i] = CompileShader(shaders[i]);
        glAttachShader(m_RendererID, shaderIDs[i]);
    }

    glLinkProgram(m_RendererID);
    glValidateProgram(m_RendererID);

    for (int i = 0; i < shaders.size(); i++) {
        glDeleteShader(shaderIDs[i]);
    }

    m_BufferLayout = std::make_shared<BufferLayout>(bufferElements);

    delete[] shaderIDs;
}

ShaderProgram::~ShaderProgram() { glDeleteProgram(m_RendererID); }

void ShaderProgram::Bind() const { glUseProgram(m_RendererID); }

void ShaderProgram::Unbind() const { glUseProgram(0); }

void ShaderProgram::SetUniformInt(const std::string& name, const int value) const {
    const GLint uniformLoc = glGetUniformLocation(m_RendererID, name.c_str());
    if (uniformLoc == -1) {
        WARN_MSG("Warning: Unable to find the uniform \'{0}\'", name);
    }
    glUniform1i(uniformLoc, value);
}

void ShaderProgram::SetUniformIntArray(const std::string& name, int* values, uint32_t count) const {}

void ShaderProgram::SetUniformFloat(const std::string& name, const float value) const {
    const GLint uniformLoc = glGetUniformLocation(m_RendererID, name.c_str());
    if (uniformLoc == -1) {
        WARN_MSG("Warning: Unable to find the uniform \'{0}\'", name);
    }
    glUniform1f(uniformLoc, value);
}

void ShaderProgram::SetUniformFloat2(const std::string& name, const glm::vec2& value) const {}

void ShaderProgram::SetUniformFloat3(const std::string& name, const glm::vec3& value) const {}

void ShaderProgram::SetUniformFloat4(const std::string& name, const glm::vec4& value) const {}

void ShaderProgram::SetUniformMat4(const std::string& name, const glm::mat4& value) const {
    const GLint uniformLoc = glGetUniformLocation(m_RendererID, name.c_str());
    if (uniformLoc == -1) {
        WARN_MSG("Warning: Unable to find the uniform \'{0}\'", name);
    }
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(value));
}

GLenum ShaderProgram::ShaderTypeFromString(const std::string& typeStr) {
    if (typeStr == "vertex") return GL_VERTEX_SHADER;
    if (typeStr == "fragment") return GL_FRAGMENT_SHADER;
    if (typeStr == "geometry") return GL_GEOMETRY_SHADER;
    if (typeStr == "compute") return GL_COMPUTE_SHADER;
    ERROR_MSG("Unknown shader type '{0}'", typeStr);
    return GL_NONE;
}

std::shared_ptr<ShaderProgram> ShaderProgram::Create(const std::string& name, const std::vector<Shader>& shaders,
                                                     const std::vector<BufferElement>& bufferElements) {
    return std::make_shared<ShaderProgram>(name, shaders, bufferElements);
}

uint32_t ShaderProgram::CompileShader(const Shader& shader) {
    const uint32_t id = glCreateShader(shader.type);
    const std::string srcString = File::ReadFromFile(shader.file);
    const char* src = srcString.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Print compile errors if any
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        auto message = new char[length];
        glGetShaderInfoLog(id, length, nullptr, message);
        std::string glType;
        switch (shader.type) {
            case GL_VERTEX_SHADER:
                glType = "VERTEX";
                break;
            case GL_FRAGMENT_SHADER:
                glType = "FRAGMENT";
                break;
            case GL_GEOMETRY_SHADER:
                glType = "GEOMETRY";
                break;
            case GL_COMPUTE_SHADER:
                glType = "COMPUTE";
                break;
            default:
                glType = "UNKNOWN";
                break;
        }
        FATAL_MSG("ERROR::Shader::{0}::COMPILATION_FAILED\n {1}", glType, message);
        glDeleteShader(id);

        delete[] message;
        return 0;
    }
    return id;
}

/* ShaderLibrary */

std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> ShaderProgramLibrary::m_Shaders;

void ShaderProgramLibrary::Init(const std::string& YamlPath) {
    const std::filesystem::path yamlSysPath = YamlPath;
    const std::string shadersDir = yamlSysPath.parent_path().string() + '/';

    const std::string yamlStr = File::ReadFromFile(YamlPath);
    YAML::Node config = YAML::Load(yamlStr);

    if (!config["shader_programs"].IsDefined()) {
        ERROR_MSG("Failed to load shader programs from YAML file");
    }

    for (const auto& shaderProgram : config["shader_programs"]) {
        auto name = shaderProgram["name"].as<std::string>();
        INFO_MSG("Loading shader program: '{0}'", name);

        std::vector<Shader> shaders;

        for (const auto& shader : shaderProgram["shaders"]) {
            Shader sh;
            sh.type = ShaderProgram::ShaderTypeFromString(shader["type"].as<std::string>());
            sh.file = shadersDir + shader["file"].as<std::string>();

            if (sh.type == GL_NONE || sh.file.empty()) {
                ERROR_MSG("Failed to load shader program from YAML file");
            } else {
                shaders.push_back(sh);
            }
        }
        std::vector<BufferElement> bufferElements;
        for (const auto& bufferElement : shaderProgram["layout"]) {
            const auto typeStr = bufferElement["type"].as<std::string>();
            const auto elementName = bufferElement["name"].as<std::string>();
            const auto normalized = bufferElement["normalized"].as<bool>();

            ShaderDataType dataType;
            if (typeStr == "float3") {
                dataType = ShaderDataType::Float3;
            } else {
                FATAL_MSG("Unknown shader data type '{0}'", typeStr);
            }

            bufferElements.emplace_back(BufferElement(dataType, elementName, normalized));
        }

        m_Shaders[name] = ShaderProgram::Create(name, shaders, bufferElements);
    }
}

std::shared_ptr<ShaderProgram> ShaderProgramLibrary::GetShaderProgram(const std::string& name) {
    if (m_Shaders.contains(name)) {
        return m_Shaders[name];
    }
    FATAL_MSG("Shader program '{0}' not found", name);
}
