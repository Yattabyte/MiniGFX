#pragma once
#ifndef INDIRECTDRAW_HPP
#define INDIRECTDRAW_HPP

#include "Buffer/glStaticBuffer.hpp"

/** A helper class encapsulating the data needed to perform an indirect draw
 * call in OpenGL. */
class IndirectDraw {
    public:
    // Public (De)Constructors
    /** Default Constructor. */
    IndirectDraw() noexcept;
    /** Construct an Indirect Draw Object.
    @param	count			the number of vertices to draw.
    @param	primitiveCount	the number of times to draw this object.
    @param	first			offset to the first vertex.
    @param	storageFlags	storage type flag. */
    IndirectDraw(
        const GLuint& count, const GLuint& primitiveCount, const GLuint& first,
        const GLbitfield& storageFlags = GL_DYNAMIC_STORAGE_BIT) noexcept;

    // Public Methods
    /** Bind this draw call to the OpenGL indirect buffer target. */
    void bind() const noexcept;
    /** Bind this buffer and also perform an indirect draw call.
    @param  drawMode        either GL_TRIANGLES, GL_POINTS, GL_LINES, etc.
    @param	indirect		an indirect pointer. */
    void drawCall(const int& drawMode, const void* indirect = nullptr) const
        noexcept;
    /** Prepare this buffer for writing, waiting on its sync fence. */
    void beginWriting() const noexcept;
    /** Signal that this buffer has finished being written to. */
    void endWriting() const noexcept;
    /** Signal that this buffer has finished being read from. */
    void endReading() noexcept;
    /** Specify how many vertices will be rendered.
    @param	count			the vertex count. */
    void setCount(const GLuint& count) noexcept;
    /** Specify how many primitives will be rendered.
    @param	primitiveCount	the number of primitives to be rendered. */
    void setPrimitiveCount(const GLuint& primitiveCount) noexcept;
    /** Specify the offset to the first vertex to be rendered.
    @param	first			the offset to the first rendered vertex. */
    void setFirst(const GLuint& first) noexcept;

    private:
    // Private Attributes
    /** The container for draw call data. */
    glStaticBuffer m_buffer;
    /** Attributes corresponding to an OpenGL draw call. */
    GLuint m_count = 0, m_primitiveCount = 0, m_first = 0;
};

#endif // INDIRECTDRAW_HPP