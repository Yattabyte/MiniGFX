#pragma once
#ifndef GLDYNAMICBUFFER_HPP
#define GLDYNAMICBUFFER_HPP

#include "Buffer/glBuffer.hpp"
#include <memory>
#include <utility>

/** An OpenGL memory buffer which can expand in size. */
class glDynamicBuffer final : public glBuffer {
    public:
    // Public (De)Constructors
    /** Wait for all fences to complete, then destroy this buffer. */
    ~glDynamicBuffer();
    /** Construct a new Dynamic buffer.
    @param	capacity	the starting capacity of this buffer.
    @param	data		optional data buffer, must be at least as large.
    @param	mapFlags	bit-field flags. */
    glDynamicBuffer(
        const GLsizeiptr& capacity = 256, const void* data = nullptr,
        const GLbitfield& mapFlags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT |
                                     GL_MAP_COHERENT_BIT) noexcept;
    /** Construct a new Dynamic buffer, from another buffer.
    @param	other		another buffer to copy from. */
    glDynamicBuffer(const glDynamicBuffer& other) noexcept;
    /** Assignment constructor.
    @param	other			another buffer to move from. */
    glDynamicBuffer(glDynamicBuffer&& other) noexcept;

    // Public Operators
    /** Movement operator, for moving another buffer into this one.
    @param	other			another buffer to move the data from, to here. */
    glDynamicBuffer& operator=(glDynamicBuffer&& other) noexcept;
    /** Copy operator, for copying another buffer into this one.
    @param	other			another buffer to copy the data from, to here. */
    glDynamicBuffer& operator=(const glDynamicBuffer& other) noexcept;

    // Public Methods
    /** Expand this buffer to fit the size provided.
    @param	size		the size to expand up to (if not already larger). */
    void setMaxSize(const GLsizeiptr& size) noexcept;
    /** Write the supplied data to GPU memory.
    @param	offset		byte offset from the beginning.
    @param	size		the size of the data to write.
    @param	data		the data to write. */
    void write(
        const GLsizeiptr& offset, const GLsizeiptr& size,
        const void* data) noexcept;
    /** Write the supplied data to GPU memory.
    @param	offset		byte offset from the beginning.
    @param	size		the size of the data to write.
    @param	data		the data to write. */
    void write_immediate(
        const GLsizeiptr& offset, const GLsizeiptr& size,
        const void* data) noexcept;
    /** Expands this buffer's container if it can't fit the specified range to
    write into.
    @note Technically creates a new a new buffer to replace the old one and
    copies the old data.
    @param	offset	byte offset from the beginning.
    @param	size	the size of the data to write. */
    void expandToFit(const GLsizeiptr& offset, const GLsizeiptr& size) noexcept;

    private:
    // Private Attributes
    /** Capacity of this buffer in bytes. */
    GLsizeiptr m_maxCapacity = 256;
    /** OpenGL map read/write/storage flags. */
    GLbitfield m_mapFlags =
        GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
    /** Pointer to underlying buffer data in local memory space. */
    void* m_bufferPtr = nullptr;
};

#endif // GLDYNAMICBUFFER_HPP