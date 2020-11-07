#pragma once
#ifndef MINIGFX_INDIRECTDRAW_HPP
#define MINIGFX_INDIRECTDRAW_HPP

#include "Buffer/glStaticBuffer.hpp"

namespace mini {
//////////////////////////////////////////////////////////////////////
/// \class  IndirectDraw
/// \brief  A helper class for performing an indirect-draw-call.
class IndirectDraw {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default Destructor
    ~IndirectDraw() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default Constructor.
    IndirectDraw() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct an Indirect Draw Object.
    /// \param  count           the number of vertices to draw.
    /// \param  primitiveCount  the number of times to draw this object.
    /// \param  first           offset to the first vertex.
    /// \param  storageFlags    storage type flag.
    IndirectDraw(
        const GLuint& count, const GLuint& primitiveCount, const GLuint& first,
        const GLbitfield storageFlags = GL_DYNAMIC_STORAGE_BIT);
    //////////////////////////////////////////////////////////////////////
    /// \brief  Move constructor.
    IndirectDraw(IndirectDraw&&) noexcept = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Move assignment.
    IndirectDraw& operator=(IndirectDraw&&) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Bind this draw call to the OpenGL indirect buffer target.
    void bind() const noexcept { m_buffer.bindBuffer(GL_DRAW_INDIRECT_BUFFER); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Bind this buffer and also perform an indirect draw call.
    /// \param  drawMode    either GL_TRIANGLES, GL_POINTS, GL_LINES, etc.
    /// \param  indirect    an indirect pointer.
    void drawCall(const int drawMode, const void* indirect = nullptr) const noexcept;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Prepare this buffer for writing, waiting on its sync fence.
    void beginWriting() const noexcept { m_buffer.beginWriting(); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Signal that this buffer has finished being written to.
    void endWriting() const noexcept { m_buffer.endWriting(); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Signal that this buffer has finished being read from.
    void endReading() noexcept { m_buffer.endReading(); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Specify how many vertices will be rendered.
    /// \param  count   the vertex count.
    void setCount(const GLuint count) noexcept;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Specify how many primitives will be rendered.
    /// \param  primitiveCount  the number of primitives to be rendered.
    void setPrimitiveCount(const GLuint primitiveCount) noexcept;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Specify the offset to the first vertex to be rendered.
    /// \param  first   the offset to the first rendered vertex.
    void setFirst(const GLuint first) noexcept;

    private:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Deleted copy constructor.
    IndirectDraw(const IndirectDraw&) noexcept = delete;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Deleted assignment operator.
    IndirectDraw& operator=(const IndirectDraw&) noexcept = delete;

    //////////////////////////////////////////////////////////////////////
    /// Private Attributes
    glStaticBuffer m_buffer;                               ///< The container for draw call data.
    GLuint m_count = 0, m_primitiveCount = 0, m_first = 0; ///< Open GL Attributes
};
}; // namespace mini

#endif // MINIGFX_INDIRECTDRAW_HPP