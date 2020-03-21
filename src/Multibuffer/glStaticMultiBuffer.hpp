#pragma once
#ifndef GLSTATICMULTIBUFFER_HPP
#define GLSTATICMULTIBUFFER_HPP

#include "Multibuffer/glMultiBuffer.hpp"
#include <stddef.h>
#include <utility>

/** Encapsulates an OpenGL multi-buffer that is fixed in size. */
template <int BufferCount = 3>
class StaticMultiBuffer final : public glMultiBuffer<BufferCount> {
    public:
    // Public (De)Constructors
    /** Wait on this buffers fences, then destroy it. */
    ~StaticMultiBuffer() {
        for (int x = 0; x < BufferCount; ++x) {
            WaitForFence(m_writeFence[x]);
            WaitForFence(m_readFence[x]);
            if (m_bufferID[x]) {
                glUnmapNamedBuffer(m_bufferID[x]);
                glDeleteBuffers(1, &m_bufferID[x]);
            }
        }
    }
    /** Default Constructor. */
    StaticMultiBuffer() noexcept {
        // Zero-initialize our starting variables
        for (int x = 0; x < BufferCount; ++x) {
            m_bufferID[x] = 0;
            m_bufferPtr[x] = nullptr;
            m_writeFence[x] = nullptr;
            m_readFence[x] = nullptr;
        }
    }
    /** Construct a new Static Multi-Buffer.
    @param	size			the starting size of this buffer.
    @param	data			optional data buffer, must be at least as large.
    @param	storageFlags	optional bit-field flags. */
    explicit StaticMultiBuffer(
        const GLsizeiptr& size, const void* data = nullptr,
        const GLbitfield& storageFlags = GL_DYNAMIC_STORAGE_BIT) noexcept
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
            glNamedBufferStorage(
                m_bufferID[x], m_size, data, storageFlags | m_mapFlags);
            m_bufferPtr[x] =
                glMapNamedBufferRange(m_bufferID[x], 0, m_size, m_mapFlags);
            if (data)
                std::memcpy(
                    static_cast<unsigned char*>(m_bufferPtr[x]), data, size);
        }
    }
    /** Construct a new Static Multi-Buffer, from another buffer. */
    StaticMultiBuffer(const StaticMultiBuffer& other) noexcept
        : StaticMultiBuffer(other.m_size, 0) {
        // Zero-initialize our starting variables
        for (int x = 0; x < BufferCount; ++x) {
            m_bufferID[x] = 0;
            m_bufferPtr[x] = nullptr;
            m_writeFence[x] = nullptr;
            m_readFence[x] = nullptr;
        }

        for (int x = 0; x < BufferCount; ++x)
            glCopyNamedBufferSubData(
                other.m_bufferID[x], m_bufferID[x], 0, 0, m_size);
    }
    /** Move Constructor. */
    StaticMultiBuffer(StaticMultiBuffer&& other) noexcept {
        (*this) = std::move(other);
    }

    // Public Operators
    /** Copy GL object from 1 instance in to another. */
    StaticMultiBuffer& operator=(const StaticMultiBuffer& other) noexcept {
        if (this != &other) {
            m_size = other.m_size;
            m_mapFlags = other.m_mapFlags;
            for (int x = 0; x < BufferCount; ++x)
                glCopyNamedBufferSubData(
                    other.m_bufferID[x], m_bufferID[x], 0, 0, other.m_size);
        }
        return *this;
    }
    /** Move GL object from 1 instance to another. */
    StaticMultiBuffer& operator=(StaticMultiBuffer&& other) noexcept {
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

    // Public Methods
    /** Write the supplied data to GPU memory.
    @param	offset			byte offset from the beginning.
    @param	size			the size of the data to write.
    @param	data			the data to write. */
    void write(
        const GLsizeiptr& offset, const GLsizeiptr& size,
        const void* data) noexcept {
        std::memcpy(
            static_cast<unsigned char*>(m_bufferPtr[m_index]) + offset, data,
            size);
    }

    private:
    // Private Attributes
    /** Size of this buffer in bytes. */
    size_t m_size = 0ull;
    /** OpenGL map read/write/storage flags. */
    GLbitfield m_mapFlags =
        GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
    /** Pointer to underlying buffer data in local memory space. */
    void* m_bufferPtr[BufferCount]{};
};

#endif // GLSTATICMULTIBUFFER_HPP