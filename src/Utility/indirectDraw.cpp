#include "Utility/indirectDraw.hpp"

//////////////////////////////////////////////////////////////////////
/// Use our shared namespace mini
using namespace mini;

//////////////////////////////////////////////////////////////////////
/// Custom Constructor
//////////////////////////////////////////////////////////////////////

IndirectDraw::IndirectDraw(
    const GLuint& count, const GLuint& primitiveCount, const GLuint& first,
    const GLbitfield& storageFlags) noexcept
    : m_count(count), m_primitiveCount(primitiveCount), m_first(first) {
    // Populate Buffer
    const GLuint data[4] = { count, primitiveCount, first, 0 };
    m_buffer = glStaticBuffer(sizeof(GLuint) * 4, data, storageFlags);
}

//////////////////////////////////////////////////////////////////////
/// drawCall
//////////////////////////////////////////////////////////////////////

void IndirectDraw::drawCall(const int& drawMode, const void* indirect) const
    noexcept {
    bind();
    glDrawArraysIndirect(drawMode, indirect);
}

//////////////////////////////////////////////////////////////////////
/// setCount
//////////////////////////////////////////////////////////////////////

void IndirectDraw::setCount(const GLuint& count) noexcept {
    m_count = count;
    m_buffer.write(0, (GLsizeiptr)(sizeof(GLuint)), &count);
}

//////////////////////////////////////////////////////////////////////
/// setPrimitiveCount
//////////////////////////////////////////////////////////////////////

void IndirectDraw::setPrimitiveCount(const GLuint& primitiveCount) noexcept {
    m_primitiveCount = primitiveCount;
    m_buffer.write(
        (GLsizeiptr)(sizeof(GLuint)), (GLsizeiptr)(sizeof(GLuint)),
        &primitiveCount);
}

//////////////////////////////////////////////////////////////////////
/// setFirst
//////////////////////////////////////////////////////////////////////

void IndirectDraw::setFirst(const GLuint& first) noexcept {
    m_first = first;
    m_buffer.write(
        (GLsizeiptr)(sizeof(GLuint)) * 2ULL, (GLsizeiptr)(sizeof(GLuint)),
        &first);
}