#pragma once
#ifndef GLMULTIVECTOR_HPP
#define GLMULTIVECTOR_HPP

#include "Multibuffer/glMultiBuffer.hpp"
#include <algorithm>

//////////////////////////////////////////////////////////////////////
/// \class  glMultiVector
/// \brief  An STL-like vector for OpenGL multi-buffered data.
/// \tparam T   the type of element to construct an array of.
template <typename T, int BufferCount = 3>
class glMultiVector final : public glMultiBuffer<BufferCount> {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Destroy this GL Vector.
    ~glMultiVector() {
        // Safely destroy each buffer this class owns
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
    /// \brief  Construct a GL Vector.
    /// \param  capacity    the starting capacity(1 or more).
    glMultiVector(const size_t& capacity = 1) noexcept
        : m_capacity(std::max(1ull, capacity)) {
        // Zero-initialize our starting variables
        for (int x = 0; x < BufferCount; ++x) {
            m_bufferID[x] = 0;
            m_bufferPtr[x] = nullptr;
            m_writeFence[x] = nullptr;
            m_readFence[x] = nullptr;
        }

        // Create 'BufferCount' number of buffers & map them
        const auto bufferSize = sizeof(T) * m_capacity;
        glCreateBuffers(BufferCount, m_bufferID);
        for (int x = 0; x < BufferCount; ++x) {
            glNamedBufferStorage(
                m_bufferID[x], bufferSize, nullptr,
                GL_DYNAMIC_STORAGE_BIT | BufferFlags);
            m_bufferPtr[x] = static_cast<T*>(glMapNamedBufferRange(
                m_bufferID[x], 0, bufferSize, BufferFlags));
        }
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Move constructor.
    /// \param  other   another buffer to move the data from, to here.
    glMultiVector(glMultiVector&& other) noexcept {
        (*this) = std::move(other);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Copy constructor.
    /// \param  other   another buffer to move the data from, to here.
    glMultiVector(const glMultiVector& other) noexcept
        : glMultiVector(other.m_capacity) {
        for (int x = 0; x < BufferCount; ++x)
            glCopyNamedBufferSubData(
                other.m_bufferID[x], m_bufferID[x], 0, 0, m_capacity);
    }

    //////////////////////////////////////////////////////////////////////
    /// \brief  Movement operator, for moving another buffer into this one.
    /// \param  other   another buffer to move the data from, to here.
    glMultiVector& operator=(glMultiVector&& other) noexcept {
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

        m_capacity = std::move(other.m_capacity);
        m_index = std::move(other.m_index);
        other.m_capacity = 0;
        other.m_index = 0;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Copy operator, for copying another buffer into this one.
    /// \param  other   another buffer to copy the data from, to here.
    glMultiVector& operator=(const glMultiVector& other) noexcept {
        m_capacity = other.m_capacity;
        for (int x = 0; x < BufferCount; ++x)
            glCopyNamedBufferSubData(
                other.m_bufferID[x], m_bufferID[x], 0, 0, m_capacity);
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve a reference to the element at the index specified.
    /// \param  index   an index to the element desired.
    /// \return reference to the element desired.
    T& operator[](const size_t& index) noexcept {
        return m_bufferPtr[m_index][index];
    }

    //////////////////////////////////////////////////////////////////////
    /// \brief  Resizes the internal capacity of this vector.
    /// \note   Does nothing if the capacity is the same
    /// \note   Currently, only grows, never shrinks
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
            for (int x = 0; x < BufferCount; ++x) {
                WaitForFence(m_writeFence[x]);
                WaitForFence(m_readFence[x]);

                // Create new buffer
                GLuint newBuffer = 0;
                glCreateBuffers(1, &newBuffer);
                glNamedBufferStorage(
                    newBuffer, newByteSize, nullptr,
                    GL_DYNAMIC_STORAGE_BIT | BufferFlags);

                // Copy old buffer
                if (oldByteSize)
                    glCopyNamedBufferSubData(
                        m_bufferID[x], newBuffer, 0, 0, oldByteSize);

                // Delete old buffer
                glUnmapNamedBuffer(m_bufferID[x]);
                glDeleteBuffers(1, &m_bufferID[x]);

                // Migrate new buffer
                m_bufferID[x] = newBuffer;
                m_bufferPtr[x] = (T*)(glMapNamedBufferRange(
                    m_bufferID[x], 0, newByteSize, BufferFlags));
            }
        }
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the length of this vector (number of elements in it).
    /// \return the number of elements in this array.
    size_t getLength() const noexcept { return m_capacity; }

    private:
    size_t m_capacity = 0; ///< Byte-Capacity of this buffer.
    constexpr const static GLbitfield BufferFlags =
        GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT |
        GL_MAP_COHERENT_BIT;       ///< OpenGL map storage flags.
    T* m_bufferPtr[BufferCount]{}; /// < Pointer to buffer data.
};

#endif // GLMULTIVECTOR_HPP