#include "Buffer/glStaticBuffer.hpp"
#include <utility>

// Public (de)Constructors

glStaticBuffer::~glStaticBuffer() {
    if (m_bufferID != 0)
        glDeleteBuffers(1, &m_bufferID);
}

glStaticBuffer::glStaticBuffer(
    const GLsizeiptr& size, const void* data,
    const GLbitfield& storageFlags) noexcept
    : m_size(size), m_storageFlags(storageFlags) {
    glCreateBuffers(1, &m_bufferID);
    glNamedBufferStorage(m_bufferID, size, data, storageFlags);
}

glStaticBuffer::glStaticBuffer(const glStaticBuffer& other) noexcept
    : glStaticBuffer(other.m_size, nullptr, other.m_storageFlags) {
    glCopyNamedBufferSubData(other.m_bufferID, m_bufferID, 0, 0, other.m_size);
}

glStaticBuffer::glStaticBuffer(glStaticBuffer&& other) noexcept {
    (*this) = std::move(other);
}

// Public Operators

glStaticBuffer&
glStaticBuffer::operator=(const glStaticBuffer& other) noexcept {
    if (this != &other) {
        m_size = other.m_size;
        m_storageFlags = other.m_storageFlags;
        glCopyNamedBufferSubData(
            other.m_bufferID, m_bufferID, 0, 0, other.m_size);
    }
    return *this;
}

glStaticBuffer& glStaticBuffer::operator=(glStaticBuffer&& other) noexcept {
    if (this != &other) {
        m_bufferID = other.m_bufferID;
        m_size = other.m_size;
        m_storageFlags = other.m_storageFlags;
        other.m_bufferID = 0;
        other.m_size = 0;
        other.m_storageFlags = 0;
    }
    return *this;
}

// Public Methods

void glStaticBuffer::write(
    const GLsizeiptr& offset, const GLsizeiptr& size,
    const void* data) noexcept {
    glNamedBufferSubData(m_bufferID, offset, size, data);
}