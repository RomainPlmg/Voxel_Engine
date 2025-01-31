//
// Created by Romain on 21/12/2024.
//

#ifndef BUFFER_H
#define BUFFER_H

#include "pch.h"
#include "utils/Log.h"

enum class ShaderDataType {
    None = 0,
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
    Bool
};  // Define the type of the data pushed into the buffer

/* Return the size (int bytes) of the pushed data */
static size_t SizeOfShaderDateType(const ShaderDataType type) {
    switch (type) {
        case ShaderDataType::None:
            return 0;
        case ShaderDataType::Float:
            return 4;
        case ShaderDataType::Float2:
            return 8;
        case ShaderDataType::Float3:
            return 12;
        case ShaderDataType::Float4:
            return 16;
        case ShaderDataType::Mat3:
            return 32;
        case ShaderDataType::Mat4:
            return 64;
        case ShaderDataType::Int:
            return 4;
        case ShaderDataType::Int2:
            return 8;
        case ShaderDataType::Int3:
            return 12;
        case ShaderDataType::Int4:
            return 16;
        case ShaderDataType::Bool:
            return 1;
        default:
            break;
    }
    FATAL_MSG("Unknown shader data type");
}

/* Represent the bundle of pushed data. Example: Vertices, UVs coordinates, Normal, Color, etc. */
struct BufferElement {
    std::string Name;
    ShaderDataType Type;
    size_t Size;
    uint32_t Offset = 0;
    bool Normalized;

    BufferElement() : Type(ShaderDataType::None), Size(0), Normalized(false) {}
    BufferElement(const ShaderDataType type, const std::string& name, const bool normalized = false)
        : Name(name), Type(type), Size(SizeOfShaderDateType(type)), Offset(0), Normalized(normalized) {}

    uint32_t GetComponentCount() const {
        switch (Type) {
            case ShaderDataType::None:
                return 0;
            case ShaderDataType::Float:
                return 1;
            case ShaderDataType::Float2:
                return 2;
            case ShaderDataType::Float3:
                return 3;
            case ShaderDataType::Float4:
                return 4;
            case ShaderDataType::Mat3:
                return 9;
            case ShaderDataType::Mat4:
                return 16;
            case ShaderDataType::Int:
                return 1;
            case ShaderDataType::Int2:
                return 2;
            case ShaderDataType::Int3:
                return 3;
            case ShaderDataType::Int4:
                return 4;
            case ShaderDataType::Bool:
                return 1;
            default:
                break;
        }

        FATAL_MSG("Unknown shader data type");
    }
};

class BufferLayout {
   public:
    BufferLayout() = default;
    BufferLayout(const std::vector<BufferElement>& elements);

    inline uint32_t GetStride() const { return m_Stride; }
    inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

    static std::shared_ptr<BufferLayout> Create(std::initializer_list<BufferElement> elements);

   private:
    std::vector<BufferElement> m_Elements;
    uint32_t m_Stride = 0;
};

class VertexBuffer {
   public:
    explicit VertexBuffer(uint32_t size);
    VertexBuffer(const float* vertices, uint32_t size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind();

    inline std::shared_ptr<BufferLayout> GetLayout() const { return m_Layout; }
    inline void SetLayout(const std::shared_ptr<BufferLayout>& layout) { m_Layout = layout; }

    static std::shared_ptr<VertexBuffer> Create(uint32_t size);
    static std::shared_ptr<VertexBuffer> Create(float* vertices, uint32_t size);

   private:
    uint32_t m_RendererID;
    std::shared_ptr<BufferLayout> m_Layout;
};

class ElementBuffer {
   public:
    ElementBuffer(const uint32_t* indices, uint32_t count);
    ~ElementBuffer();

    void Bind() const;
    void Unbind();
    [[nodiscard]] inline int GetCount() const { return m_Count; };

    static std::shared_ptr<ElementBuffer> Create(uint32_t* indices, uint32_t count);

   private:
    uint32_t m_RendererID;
    int m_Count = 0;
};

class FrameBuffer {
   public:
    FrameBuffer(int width, int height);
    ~FrameBuffer();

    void Resize(int width, int height);
    void Bind() const;
    void Unbind();

    static std::shared_ptr<FrameBuffer> Create(int width, int height);

    /* Getters */
    [[nodiscard]] inline uint32_t GetColorTexture() const { return m_ColorTexture; };
    [[nodiscard]] inline uint32_t GetDepthBuffer() const { return m_DepthBuffer; };

   private:
    uint32_t m_RendererID;
    uint32_t m_ColorTexture;
    uint32_t m_DepthBuffer;
};

#endif  // BUFFER_H
