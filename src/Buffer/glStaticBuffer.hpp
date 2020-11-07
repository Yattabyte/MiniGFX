#pragma once
#ifndef MINIGFX_GLSTATICBUFFER_HPP
#define MINIGFX_GLSTATICBUFFER_HPP

#include "Buffer/glBuffer.hpp"
#include <stddef.h>

namespace mini {
//////////////////////////////////////////////////////////////////////
/// \class  glStaticBuffer
/// \brief  Encapsulates an OpenGL buffer that is fixed in size.
class glStaticBuffer final : public glBuffer {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Destroy this buffer.
    ~glStaticBuffer();
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a static buffer.
    glStaticBuffer() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Explicit Instantiation.
    explicit glStaticBuffer(
        const GLsizeiptr& size, const void* data = 0, const GLbitfield& storageFlags = GL_DYNAMIC_STORAGE_BIT);
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct and copy another static buffer.
    /// \param  other       another buffer to copy from.
    glStaticBuffer(const glStaticBuffer& other) noexcept;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct and move from another static buffer.
    /// \param  other       another buffer to move from.
    glStaticBuffer(glStaticBuffer&& other) noexcept;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Copy OpenGL object from 1 instance to another.
    /// \param  other       another buffer to copy from.
    /// \return reference to this.
    glStaticBuffer& operator=(const glStaticBuffer& other) noexcept;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Move OpenGL object from 1 instance to another.
    /// \param  other       another buffer to move from.
    /// \return reference to this.
    glStaticBuffer& operator=(glStaticBuffer&& other) noexcept;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Write the supplied data to GPU memory.
    /// \param  offset      byte offset from the beginning.
    /// \param  size        the size of the data to write.
    /// \param  data        the data to write.
    void write(const GLsizeiptr& offset, const GLsizeiptr& size, const void* data) noexcept;

    private:
    //////////////////////////////////////////////////////////////////////
    /// Private Attributes
    size_t m_size = 0ull;                               ///< Byte-size of this buffer.
    GLbitfield m_storageFlags = GL_DYNAMIC_STORAGE_BIT; ///< OpenGL map storage flags.
};
}; // namespace mini

#endif // MINIGFX_GLSTATICBUFFER_HPP