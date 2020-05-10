#pragma once
#ifndef MINIGFX_GLDYNAMICMULTIBUFFER_HPP
#define MINIGFX_GLDYNAMICMULTIBUFFER_HPP

#include "Multibuffer/glMultiBuffer.hpp"
#include <cstring>
#include <memory>
#include <utility>

namespace mini {
//////////////////////////////////////////////////////////////////////
/// \class  glDynamicMultiBuffer
/// \brief  An OpenGL memory multi-buffer which can expand in size.
template <int BufferCount = 3>
class glDynamicMultiBuffer final : public glMultiBuffer<BufferCount> {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Wait for all fences to complete, then destroy this buffer.
    ~glDynamicMultiBuffer() {
        for (int x = 0; x < BufferCount; ++x) {
            this->WaitForFence(this->m_writeFence[x]);
            this->WaitForFence(this->m_readFence[x]);
            if (this->m_bufferID[x]) {
                glUnmapNamedBuffer(this->m_bufferID[x]);
                glDeleteBuffers(1, &this->m_bufferID[x]);
            }
        }
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a new Dynamic buffer.
    /// \param  capacity    the starting capacity of this buffer.
    /// \param  data        optional data buffer, must be at least as large.
    /// \param  mapFlags    bit-field flags.
    glDynamicMultiBuffer(
        const GLsizeiptr& capacity = 256, const void* data = nullptr,
        const GLbitfield& mapFlags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT |
                                     GL_MAP_COHERENT_BIT) noexcept
        : m_maxCapacity(capacity), m_mapFlags(mapFlags) {
        glCreateBuffers(BufferCount, this->m_bufferID);
        for (int x = 0; x < BufferCount; ++x) {
            glNamedBufferStorage(
                this->m_bufferID[x], m_maxCapacity, data,
                GL_DYNAMIC_STORAGE_BIT | m_mapFlags);
            m_bufferPtr[x] = glMapNamedBufferRange(
                this->m_bufferID[x], 0, m_maxCapacity, m_mapFlags);
        }
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a new Dynamic buffer, from another buffer.
    /// \param  other   another buffer to copy from.
    glDynamicMultiBuffer(const glDynamicMultiBuffer& other) noexcept
        : glDynamicMultiBuffer(other.m_maxCapacity, 0, other.m_mapFlags) {
        for (int x = 0; x < BufferCount; ++x)
            glCopyNamedBufferSubData(
                other.m_bufferID[x], this->m_bufferID[x], 0, 0, m_maxCapacity);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Assignment constructor.
    /// \param  other   another buffer to move from.
    glDynamicMultiBuffer(glDynamicMultiBuffer&& other) noexcept {
        (*this) = std::move(other);
    }

    //////////////////////////////////////////////////////////////////////
    /// \brief  Movement operator, for moving another buffer into this one.
    /// \param  other   another buffer to move the data from, to here.
    glDynamicMultiBuffer& operator=(glDynamicMultiBuffer&& other) noexcept {
        for (int x = 0; x < BufferCount; ++x) {
            this->m_bufferID[x] = std::move(other.m_bufferID[x]);
            m_bufferPtr[x] = std::move(other.m_bufferPtr[x]);
            this->m_writeFence[x] = std::move(other.m_writeFence[x]);
            this->m_readFence[x] = std::move(other.m_readFence[x]);
            other.m_bufferID[x] = 0;
            other.m_bufferPtr[x] = nullptr;
            other.m_writeFence[x] = nullptr;
            other.m_readFence[x] = nullptr;
        }

        m_mapFlags = (std::move(other.m_mapFlags));
        m_maxCapacity = (std::move(other.m_maxCapacity));
        this->m_index = std::move(other.m_index);
        other.m_mapFlags = 0;
        other.m_maxCapacity = 0;
        other.m_index = 0;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Copy operator, for copying another buffer into this one.
    /// \param  other   another buffer to copy the data from, to here.
    glDynamicMultiBuffer&
    operator=(const glDynamicMultiBuffer& other) noexcept {
        m_mapFlags = other.m_mapFlags;
        m_maxCapacity = other.m_maxCapacity;
        for (int x = 0; x < BufferCount; ++x)
            glCopyNamedBufferSubData(
                other.m_bufferID[x], this->m_bufferID[x], 0, 0, m_maxCapacity);
        return *this;
    }

    //////////////////////////////////////////////////////////////////////
    /// \brief  Expand this buffer to fit the size provided.
    /// \param  size        the size to expand up to(if not already larger).
    void setMaxSize(const GLsizeiptr& size) noexcept { expandToFit(0, size); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Write the supplied data to GPU memory.
    /// \param  offset      byte offset from the beginning.
    /// \param  size        the size of the data to write.
    /// \param  data        the data to write.
    void write(
        const GLsizeiptr& offset, const GLsizeiptr& size,
        const void* data) noexcept {
        expandToFit(offset, size);
        std::memcpy(
            static_cast<unsigned char*>(m_bufferPtr[this->m_index]) + offset,
            data, size);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Write the supplied data to GPU memory.
    /// \param  offset      byte offset from the beginning.
    /// \param  size        the size of the data to write.
    /// \param  data        the data to write.
    void write_immediate(
        const GLsizeiptr& offset, const GLsizeiptr& size,
        const void* data) noexcept {
        expandToFit(offset, size);

        for (const auto& buffer : this->m_bufferID)
            glNamedBufferSubData(buffer, offset, size, data);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Expands this buffer's container to fit the desired range.
    /// \note   May invalidate the previous underlying data range.
    /// \param  offset      byte offset from the  beginning.
    /// \param  size        the size of the data to write.
    void
    expandToFit(const GLsizeiptr& offset, const GLsizeiptr& size) noexcept {
        if (offset + size > m_maxCapacity) {
            // Create new buffer large enough to fit old data + new data
            const GLsizeiptr oldSize = m_maxCapacity;
            m_maxCapacity += offset + (size * 2);

            // Wait for and transfer data from old buffers into new buffers of
            // the new size
            for (int x = 0; x < BufferCount; ++x) {
                this->WaitForFence(this->m_writeFence[x]);
                this->WaitForFence(this->m_readFence[x]);

                // Create new buffer
                GLuint newBuffer = 0;
                glCreateBuffers(1, &newBuffer);
                glNamedBufferStorage(
                    newBuffer, m_maxCapacity, nullptr,
                    GL_DYNAMIC_STORAGE_BIT | m_mapFlags);

                // Copy old buffer
                if (oldSize)
                    glCopyNamedBufferSubData(
                        this->m_bufferID[x], newBuffer, 0, 0, oldSize);

                // Delete old buffer
                glUnmapNamedBuffer(this->m_bufferID[x]);
                glDeleteBuffers(1, &this->m_bufferID[x]);

                // Migrate new buffer
                this->m_bufferID[x] = newBuffer;
                m_bufferPtr[x] = glMapNamedBufferRange(
                    this->m_bufferID[x], 0, m_maxCapacity, m_mapFlags);
            }
        }
    }

    private:
    GLsizeiptr m_maxCapacity = 256; ///< Byte-capacity of this buffer/
    GLbitfield m_mapFlags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT |
                            GL_MAP_COHERENT_BIT; ///< OpenGL map storage flags.
    void* m_bufferPtr[BufferCount]{}; ///< Pointer to underlying buffer data.
};
}; // namespace mini

#endif // MINIGFX_GLDYNAMICMULTIBUFFER_HPP