#pragma once
#ifndef GLDYNAMICBUFFER_HPP
#define GLDYNAMICBUFFER_HPP

#include "Buffer/glBuffer.hpp"
#include <memory>
#include <utility>

//////////////////////////////////////////////////////////////////////
/// \class  glDynamicBuffer
/// \brief  An OpenGL memory buffer which can expand in size.
class glDynamicBuffer final : public glBuffer {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Wait for all fences to complete, then destroy this buffer.
    ~glDynamicBuffer();
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a new Dynamic buffer.
    /// \param  capacity    the starting capacity of this buffer.
    /// \param  data        optional data buffer, must be at least as large.
    /// \param  mapFlags    bit-field flags.
    glDynamicBuffer(
        const GLsizeiptr& capacity = 256, const void* data = nullptr,
        const GLbitfield& mapFlags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT |
                                     GL_MAP_COHERENT_BIT) noexcept;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a new Dynamic buffer, from another buffer.
    /// \param  other   another buffer to copy from.
    glDynamicBuffer(const glDynamicBuffer& other) noexcept;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Assignment constructor.
    /// \param  other   another buffer to move from.
    glDynamicBuffer(glDynamicBuffer&& other) noexcept {
        (*this) = std::move(other);
    }

    //////////////////////////////////////////////////////////////////////
    /// \brief  Movement operator, for moving another buffer into this one.
    /// \param  other       another buffer to move the data from, to here.
    glDynamicBuffer& operator=(glDynamicBuffer&& other) noexcept;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Copy operator, for copying another buffer into this one.
    /// \param  other       another buffer to copy the data from, to here.
    glDynamicBuffer& operator=(const glDynamicBuffer& other) noexcept;

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
        const void* data) noexcept;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Write the supplied data to GPU memory.
    /// \param  offset      byte offset from the beginning.
    /// \param  size        the size of the data to write.
    /// \param  data        the data to write.
    void write_immediate(
        const GLsizeiptr& offset, const GLsizeiptr& size,
        const void* data) noexcept;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Expands this buffer's container to fit the desired range.
    /// \note   May invalidate the previous underlying data range.
    /// \param  offset      byte offset from the  beginning.
    /// \param  size        the size of the data to write.
    void expandToFit(const GLsizeiptr& offset, const GLsizeiptr& size) noexcept;

    private:
    GLsizeiptr m_maxCapacity = 256; ///< Byte-capacity of this buffer.
    GLbitfield m_mapFlags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT |
                            GL_MAP_COHERENT_BIT; ///< OpenGL map storage flags.
    void* m_bufferPtr = nullptr; ///< Pointer to underlying buffer data.
};

#endif // GLDYNAMICBUFFER_HPP