#pragma once
#ifndef GLSTATICBUFFER_HPP
#define GLSTATICBUFFER_HPP

#include "Buffer/glBuffer.hpp"

/** Encapsulates an OpenGL buffer that is fixed in size. */
class glStaticBuffer final : public glBuffer {
    public:
    // Public (De)Constructors
    /** Destroy this buffer. */
    ~glStaticBuffer();
    /** Default Constructor. */
    /** Construct a static buffer. */
    glStaticBuffer() noexcept = default;
    /** Explicit Instantiation. */
    explicit glStaticBuffer(
        const GLsizeiptr& size, const void* data = 0,
        const GLbitfield& storageFlags = GL_DYNAMIC_STORAGE_BIT) noexcept;
    /** Construct and copy another static buffer.
    @param	other	another buffer to copy from. */
    glStaticBuffer(const glStaticBuffer& other) noexcept;
    /** Construct and move from another static buffer.
    @param	other	another buffer to move from. */
    glStaticBuffer(glStaticBuffer&& other) noexcept;

    // Public Operators
    /** Copy OpenGL object from 1 instance to another.
    @param	other	another buffer to copy from.
    @return			reference to this. */
    glStaticBuffer& operator=(const glStaticBuffer& other) noexcept;
    /** Move OpenGL object from 1 instance to another.
    @param	other	another buffer to move from.
    @return			reference to this. */
    glStaticBuffer& operator=(glStaticBuffer&& other) noexcept;

    // Public Methods
    /** Write the supplied data to GPU memory.
    @param	offset	byte offset from the beginning.
    @param	size	the size of the data to write.
    @param	data	the data to write. */
    void write(
        const GLsizeiptr& offset, const GLsizeiptr& size,
        const void* data) noexcept;

    private:
    // Private Attributes
    /** Size of this buffer in bytes. */
    size_t m_size = 0ull;
    /** OpenGL map storage flags. */
    GLbitfield m_storageFlags = GL_DYNAMIC_STORAGE_BIT;
};

#endif // GLSTATICBUFFER_HPP