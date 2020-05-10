#pragma once
#ifndef MINIGFX_GLVECTOR_HPP
#define MINIGFX_GLVECTOR_HPP

#include "Buffer/glBuffer.hpp"
#include <algorithm>

namespace mini {
//////////////////////////////////////////////////////////////////////
/// \class  glVector
/// \brief  An STL-like vector for OpenGL buffered data.
/// \tparam T   the type of element to construct an array of.
template <typename T> class glVector final : public glBuffer {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Destroy this GL Vector.
    ~glVector() {
        // Safely destroy each buffer this class owns
        WaitForFence(m_writeFence);
        WaitForFence(m_readFence);
        if (m_bufferID) {
            glUnmapNamedBuffer(m_bufferID);
            glDeleteBuffers(1, &m_bufferID);
        }
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a GL Vector.
    /// \param  capacity    the starting capacity (1 or more).
    glVector(const size_t& capacity = 1) noexcept
        : m_capacity(std::max(1ull, capacity)) {
        const auto bufferSize = sizeof(T) * m_capacity;
        glCreateBuffers(1, &m_bufferID);
        glNamedBufferStorage(
            m_bufferID, bufferSize, nullptr,
            GL_DYNAMIC_STORAGE_BIT | BufferFlags);
        m_bufferPtr = static_cast<T*>(
            glMapNamedBufferRange(m_bufferID, 0, bufferSize, BufferFlags));
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Move constructor.
    /// \param  other   another buffer to move the data from,
    to here.glVector(glVector&& other) noexcept { (*this) = std::move(other); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Copy constructor.
    /// \param  other   another buffer to move the data from, to here.
    glVector(const glVector& other) noexcept : glVector(other.m_capacity) {
        glCopyNamedBufferSubData(
            other.m_bufferID, m_bufferID, 0, 0, m_capacity);
    }

    //////////////////////////////////////////////////////////////////////
    /// \brief  Movement operator, for moving another buffer into this one.
    /// \param  other   another buffer to move the data from, to here.
    glVector& operator=(glVector&& other) noexcept {
        m_bufferID = std::move(other.m_bufferID);
        m_bufferPtr = std::move(other.m_bufferPtr);
        m_writeFence = std::move(other.m_writeFence);
        m_readFence = std::move(other.m_readFence);
        m_capacity = std::move(other.m_capacity);
        m_index = std::move(other.m_index);
        other.m_bufferID = 0;
        other.m_bufferPtr = nullptr;
        other.m_writeFence = nullptr;
        other.m_readFence = nullptr;
        other.m_capacity = 0;
        other.m_index = 0;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Copy operator, for copying another buffer into this one.
    /// \param  other   another buffer to copy the data from, to here.
    glVector& operator=(const glVector& other) noexcept {
        m_capacity = other.m_capacity;
        glCopyNamedBufferSubData(
            other.m_bufferID, m_bufferID, 0, 0, m_capacity);
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief Retrieve a reference to the element at the index specified.
    /// \param  index   an index to the element desired.
    /// \return reference to the element desired.
    T& operator[](const size_t& index) noexcept { return m_bufferPtr[index]; }

    //////////////////////////////////////////////////////////////////////
    /// \brief  Resizes the internal capacity of this vector.
    /// \note   Does nothing if the capacity is the same.
    /// \note   Currently, only grows, never shrinks.
    /// \note   May stall waiting for old buffers to finish, invalidate them.
    /// \param	newCapacity		the new desired capacity.
    void resize(const size_t& newCapacity) noexcept {
        // See if we must expand this container
        if (newCapacity > m_capacity) {
            // Calculate old and new byte sizes
            const auto oldByteSize = sizeof(T) * m_capacity;
            const auto newByteSize = sizeof(T) * newCapacity;
            m_capacity = newCapacity;

            // Wait for and transfer data from old buffers into new buffers
            // of the new size
            WaitForFence(m_writeFence);
            WaitForFence(m_readFence);

            // Create new buffer
            GLuint newBuffer = 0;
            glCreateBuffers(1, &newBuffer);
            glNamedBufferStorage(
                newBuffer, newByteSize, nullptr,
                GL_DYNAMIC_STORAGE_BIT | BufferFlags);

            // Copy old buffer
            if (oldByteSize)
                glCopyNamedBufferSubData(
                    m_bufferID, newBuffer, 0, 0, oldByteSize);

            // Delete old buffer
            glUnmapNamedBuffer(m_bufferID);
            glDeleteBuffers(1, &m_bufferID);

            // Migrate new buffer
            m_bufferID = newBuffer;
            m_bufferPtr = (T*)(glMapNamedBufferRange(
                m_bufferID, 0, newByteSize, BufferFlags));
        }
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the length of this vector (number of elements in it).
    /// \return the number of elements in this array.
    size_t getLength() const noexcept { return m_capacity; }

    private:
    size_t m_capacity = 0; ///< Byte-capacity of this buffer.
    constexpr const static GLbitfield BufferFlags =
        GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT |
        GL_MAP_COHERENT_BIT;  ///< OpenGL map storage flags.
    T* m_bufferPtr = nullptr; ///< Pointer to the underlying data.
};
}; // namespace mini

#endif // MINIGFX_GLVECTOR_HPP