//
// Created by Romain on 21/12/2024.
//

#include "Buffer.h"

#include "GraphicContext.h"

/* Vertex buffer */
VertexBuffer::VertexBuffer(const uint32_t size) {
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(const float* vertices, const uint32_t size) {
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_RendererID); }

void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); }

void VertexBuffer::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size) { return std::make_shared<VertexBuffer>(size); }

std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, const uint32_t size) {
    return std::make_shared<VertexBuffer>(vertices, size);
}

/* Element buffer */
ElementBuffer::ElementBuffer(const uint32_t* indices, const uint32_t count) {
    m_Count = count;
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, indices, GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer() { glDeleteBuffers(1, &m_RendererID); }

void ElementBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); }

void ElementBuffer::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

std::shared_ptr<ElementBuffer> ElementBuffer::Create(uint32_t* indices, uint32_t count) {
    return std::make_shared<ElementBuffer>(indices, count);
}

/* Buffer Layout */
BufferLayout::BufferLayout(const std::vector<BufferElement>& elements) : m_Elements{elements} {
    uint32_t offset = 0;
    for (auto& element : m_Elements) {
        element.Offset = offset;
        offset += static_cast<uint32_t>(element.Size);
        m_Stride += static_cast<uint32_t>(element.Size);
    }
}

std::shared_ptr<BufferLayout> BufferLayout::Create(std::initializer_list<BufferElement> elements) {
    return std::make_shared<BufferLayout>(elements);
}
