#pragma once
#ifndef MINIGFX_GLSTATICMULTIBUFFER_HPP
#define MINIGFX_GLSTATICMULTIBUFFER_HPP

#include "Multibuffer/glMultiBuffer.hpp"
#include <cstring>
#include <stddef.h>
#include <utility>

namespace mini {
//////////////////////////////////////////////////////////////////////
/// \class  glStaticMultiBuffer
/// \brief  Encapsulates an OpenGL multi-buffer that is fixed in size.
template <int BufferCount = 3> class glStaticMultiBuffer final : public glMultiBuffer<BufferCount> {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Wait on this buffers fences, then destroy it.
    ~glStaticMultiBuffer() {
        for (int x = 0; x < BufferCount; ++x) {
            WaitForFence(m_writeFence[x]);
            WaitForFence(m_readFence[x]);
            if (m_bufferID[x]) {
                glUnmapNamedBuffer(m_bufferID[x]);
                glDeleteBuffers(1, &m_bufferID[x]);
            }
        }
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default Constructor.
    glStaticMultiBuffer() {
        // Zero-initialize our starting variables
        for (int x = 0; x < BufferCount; ++x) {
            m_bufferID[x] = 0;
            m_bufferPtr[x] = nullptr;
            m_writeFence[x] = nullptr;
            m_readFence[x] = nullptr;
        }
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a new Static Multi-Buffer.
    /// \param  size            the starting size of this buffer.
    /// \param  data            optional data buffer, must be at least as large.
    /// \param  storageFlags    optional bit - field flags.
    explicit glStaticMultiBuffer(
        const GLsizeiptr& size, const void* data = nullptr, const GLbitfield storageFlags = GL_DYNAMIC_STORAGE_BIT)
        : m_size(size) {
        // Zero-initialize our starting variables
        for (int x = 0; x < BufferCount; ++x) {
            m_bufferID[x] = 0;
            m_bufferPtr[x] = nullptr;
            m_writeFence[x] = nullptr;
            m_readFence[x] = nullptr;
        }

        glCreateBuffers(BufferCount, m_bufferID);
        for (int x = 0; x < BufferCount; ++x) {
            glNamedBufferStorage(m_bufferID[x], m_size, data, storageFlags | m_mapFlags);
            m_bufferPtr[x] = glMapNamedBufferRange(m_bufferID[x], 0, m_size, m_mapFlags);
            if (data)
                std::memcpy(static_cast<unsigned char*>(m_bufferPtr[x]), data, size);
        }
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a new Static Multi-Buffer, from another buffer.
    glStaticMultiBuffer(const glStaticMultiBuffer& other) noexcept : glStaticMultiBuffer(other.m_size, 0) {
        // Zero-initialize our starting variables
        for (int x = 0; x < BufferCount; ++x) {
            m_bufferID[x] = 0;
            m_bufferPtr[x] = nullptr;
            m_writeFence[x] = nullptr;
            m_readFence[x] = nullptr;
        }

        for (int x = 0; x < BufferCount; ++x)
            glCopyNamedBufferSubData(other.m_bufferID[x], m_bufferID[x], 0, 0, m_size);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Move Constructor.
    glStaticMultiBuffer(glStaticMultiBuffer&& other) noexcept { (*this) = std::move(other); }

    //////////////////////////////////////////////////////////////////////
    /// \brief  Copy GL object from 1 instance in to another.
    glStaticMultiBuffer& operator=(const glStaticMultiBuffer& other) noexcept {
        if (this != &other) {
            m_size = other.m_size;
            m_mapFlags = other.m_mapFlags;
            for (int x = 0; x < BufferCount; ++x)
                glCopyNamedBufferSubData(other.m_bufferID[x], m_bufferID[x], 0, 0, other.m_size);
        }
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Move GL object from 1 instance to another.
    glStaticMultiBuffer& operator=(glStaticMultiBuffer&& other) noexcept {
        if (this != &other) {
            for (int x = 0; x < BufferCount; ++x) {
                m_bufferID[x] = std::move(other.m_bufferID[x]);
                m_bufferPtr[x] = std::move(other.m_bufferPtr[x]);
                m_writeFence[x] = std::move(other.m_writeFence[x]);
                m_readFence[x] = std::move(other.m_readFence[x]);
                other.m_bufferID[x] = 0;
                other.m_bufferPtr[x] = nullptr;
                other.m_writeFence[x] = nullptr;
                other.m_readFence[x] = nullptr;
            }
            m_mapFlags = (std::move(other.m_mapFlags));
            m_index = std::move(other.m_index);
            m_size = (std::move(other.m_size));
            other.m_mapFlags = 0;
            other.m_index = 0;
            other.m_size = 0;
        }
        return *this;
    }

    //////////////////////////////////////////////////////////////////////
    /// \brief  Write the supplied data to GPU memory.
    /// \param  offset      byte offset from the beginning.
    /// \param  size        the size of the data to write.
    /// \param  data        the data to write.
    void write(const GLsizeiptr offset, const GLsizeiptr size, const void* data) noexcept {
        std::memcpy(static_cast<unsigned char*>(m_bufferPtr[m_index]) + offset, data, size);
    }

    private:
    //////////////////////////////////////////////////////////////////////
    /// Private Attributes
    size_t m_size = 0ull; ///< Byte-size of this buffer.
    GLbitfield m_mapFlags =
        GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT; ///< OpenGL map storage flags.
    void* m_bufferPtr[BufferCount]{};                                   ///< Pointer to buffer data.
};
}; // namespace mini

#endif // MINIGFX_GLSTATICMULTIBUFFER_HPP