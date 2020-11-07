#include "Utility/indirectDraw.hpp"
#include <array>

//////////////////////////////////////////////////////////////////////
/// Useful Aliases
using mini::glStaticBuffer;
using mini::IndirectDraw;

//////////////////////////////////////////////////////////////////////
/// Custom Constructor
//////////////////////////////////////////////////////////////////////

IndirectDraw::IndirectDraw(
    const GLuint& count, const GLuint& primitiveCount, const GLuint& first, const GLbitfield storageFlags)
    : m_count(count), m_primitiveCount(primitiveCount), m_first(first) {
    // Populate Buffer
    const std::array<GLuint, 4> data = { count, primitiveCount, first, 0 };
    m_buffer = glStaticBuffer(sizeof(GLuint) * 4, data.data(), storageFlags);
}

//////////////////////////////////////////////////////////////////////
/// drawCall
//////////////////////////////////////////////////////////////////////

void IndirectDraw::drawCall(const int drawMode, const void* indirect) const noexcept {
    bind();
    glDrawArraysIndirect(drawMode, indirect);
}

//////////////////////////////////////////////////////////////////////
/// setCount
//////////////////////////////////////////////////////////////////////

void IndirectDraw::setCount(const GLuint count) noexcept {
    m_count = count;
    m_buffer.write(0, static_cast<GLsizeiptr>(sizeof(GLuint)), &count);
}

//////////////////////////////////////////////////////////////////////
/// setPrimitiveCount
//////////////////////////////////////////////////////////////////////

void IndirectDraw::setPrimitiveCount(const GLuint primitiveCount) noexcept {
    m_primitiveCount = primitiveCount;
    m_buffer.write(static_cast<GLsizeiptr>(sizeof(GLuint)), static_cast<GLsizeiptr>(sizeof(GLuint)), &primitiveCount);
}

//////////////////////////////////////////////////////////////////////
/// setFirst
//////////////////////////////////////////////////////////////////////

void IndirectDraw::setFirst(const GLuint first) noexcept {
    m_first = first;
    m_buffer.write(static_cast<GLsizeiptr>(sizeof(GLuint)) * 2ULL, static_cast<GLsizeiptr>(sizeof(GLuint)), &first);
}