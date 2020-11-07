#include "Buffer/glDynamicBuffer.hpp"

//////////////////////////////////////////////////////////////////////
/// Useful Aliases
using mini::glDynamicBuffer;

//////////////////////////////////////////////////////////////////////
/// Custom Destructor
//////////////////////////////////////////////////////////////////////

glDynamicBuffer::~glDynamicBuffer() {
    WaitForFence(m_writeFence);
    WaitForFence(m_readFence);
    if (m_bufferID != 0U) {
        glUnmapNamedBuffer(m_bufferID);
        glDeleteBuffers(1, &m_bufferID);
    }
}

//////////////////////////////////////////////////////////////////////
/// Custom Constructor
//////////////////////////////////////////////////////////////////////

glDynamicBuffer::glDynamicBuffer(const GLsizeiptr& capacity, const void* data, const GLbitfield& mapFlags)
    : m_maxCapacity(capacity), m_mapFlags(mapFlags) {
    glCreateBuffers(1, &m_bufferID);
    glNamedBufferStorage(m_bufferID, m_maxCapacity, data, GL_DYNAMIC_STORAGE_BIT | m_mapFlags);
    m_bufferPtr = glMapNamedBufferRange(m_bufferID, 0, m_maxCapacity, m_mapFlags);
}

//////////////////////////////////////////////////////////////////////

glDynamicBuffer::glDynamicBuffer(const glDynamicBuffer& other) noexcept
    : glDynamicBuffer(other.m_maxCapacity, nullptr, other.m_mapFlags) {
    glCopyNamedBufferSubData(other.m_bufferID, m_bufferID, 0, 0, m_maxCapacity);
}

//////////////////////////////////////////////////////////////////////
/// operator=
//////////////////////////////////////////////////////////////////////

glDynamicBuffer& glDynamicBuffer::operator=(glDynamicBuffer&& other) noexcept {
    if (&other != this) {
        m_bufferID = other.m_bufferID;
        m_bufferPtr = other.m_bufferPtr;
        m_writeFence = other.m_writeFence;
        m_readFence = other.m_readFence;
        m_mapFlags = (other.m_mapFlags);
        m_maxCapacity = (other.m_maxCapacity);
        other.m_bufferID = 0;
        other.m_bufferPtr = nullptr;
        other.m_writeFence = nullptr;
        other.m_readFence = nullptr;
        other.m_mapFlags = 0;
        other.m_maxCapacity = 0;
    }
    return *this;
}

//////////////////////////////////////////////////////////////////////

glDynamicBuffer& glDynamicBuffer::operator=(const glDynamicBuffer& other) noexcept {
    if (&other != this) {
        m_mapFlags = other.m_mapFlags;
        m_maxCapacity = other.m_maxCapacity;
        glCopyNamedBufferSubData(other.m_bufferID, m_bufferID, 0, 0, m_maxCapacity);
    }
    return *this;
}

//////////////////////////////////////////////////////////////////////
/// write
//////////////////////////////////////////////////////////////////////

void glDynamicBuffer::write(const GLsizeiptr& offset, const GLsizeiptr& size, const void* data) noexcept {
    expandToFit(offset, size);
    std::memcpy(static_cast<unsigned char*>(m_bufferPtr) + offset, data, size);
}

//////////////////////////////////////////////////////////////////////
/// write_immediate
//////////////////////////////////////////////////////////////////////

void glDynamicBuffer::write_immediate(const GLsizeiptr& offset, const GLsizeiptr& size, const void* data) noexcept {
    expandToFit(offset, size);
    glNamedBufferSubData(m_bufferID, offset, size, data);
}

//////////////////////////////////////////////////////////////////////
/// expandToFit
//////////////////////////////////////////////////////////////////////

void glDynamicBuffer::expandToFit(const GLsizeiptr& offset, const GLsizeiptr& size) noexcept {
    if (offset + size > m_maxCapacity) {
        // Create new buffer large enough to fit old data + new data
        const GLsizeiptr oldSize = m_maxCapacity;
        m_maxCapacity += offset + (size * 2);

        // Wait for and transfer data from old buffers into new buffers of
        // the new size
        WaitForFence(m_writeFence);
        WaitForFence(m_readFence);

        // Create new buffer
        GLuint newBuffer = 0;
        glCreateBuffers(1, &newBuffer);
        glNamedBufferStorage(newBuffer, m_maxCapacity, nullptr, GL_DYNAMIC_STORAGE_BIT | m_mapFlags);

        // Copy old buffer
        if (oldSize != 0) {
            glCopyNamedBufferSubData(m_bufferID, newBuffer, 0, 0, oldSize);
        }

        // Delete old buffer
        glUnmapNamedBuffer(m_bufferID);
        glDeleteBuffers(1, &m_bufferID);

        // Migrate new buffer
        m_bufferID = newBuffer;
        m_bufferPtr = glMapNamedBufferRange(m_bufferID, 0, m_maxCapacity, m_mapFlags);
    }
}