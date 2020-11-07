#pragma once
#ifndef MINIGFX_GLMULTIBUFFER_HPP
#define MINIGFX_GLMULTIBUFFER_HPP

#include <glad/glad.h>

namespace mini {
//////////////////////////////////////////////////////////////////////
/// \class  glMultiBuffer
/// \brief  An encapsulation of an OpenGL GPU-backed memory multi-buffer.
template <int BufferCount = 3> class glMultiBuffer {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Virtual Destructor.
    virtual ~glMultiBuffer() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default constructor.
    glMultiBuffer() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Move constructor.
    glMultiBuffer(glMultiBuffer&&) noexcept = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Copy constructor.
    glMultiBuffer(const glMultiBuffer&) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Move assignment.
    glMultiBuffer& operator=(glMultiBuffer&&) noexcept = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Copy assignment.
    glMultiBuffer& operator=(const glMultiBuffer&) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Wait for the fence at the supplied index to pass.
    /// \param fence the fence belonging to a particular internal buffer.
    static void WaitForFence(GLsync& fence) noexcept {
        while (fence) {
            GLbitfield waitFlags = 0;
            if (const auto waitReturn = glClientWaitSync(fence, waitFlags, 1); waitReturn == GL_SIGNALED ||
                                                                               waitReturn == GL_ALREADY_SIGNALED ||
                                                                               waitReturn == GL_CONDITION_SATISFIED) {
                glDeleteSync(fence);
                fence = nullptr;
                return;
            }
            waitFlags = GL_SYNC_FLUSH_COMMANDS_BIT;
        }
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Prepare this buffer for writing, waiting on any reads.
    void beginWriting() const noexcept {
        // Ensure all reads and writes at this index have finished.
        WaitForFence(m_writeFence[m_index]);
        WaitForFence(m_readFence[m_index]);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Signal that this multi-buffer is finished being written to.
    void endWriting() const noexcept {
        if (!m_writeFence[m_index])
            m_writeFence[m_index] = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Signal that this multi-buffer is finished being read from.
    void endReading() noexcept {
        if (!m_readFence[m_index])
            m_readFence[m_index] = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
        m_index = (m_index + 1) % BufferCount;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Bind this buffer to the target specified.
    /// \param  target  the target type of this buffer.
    void bindBuffer(const GLenum& target) const noexcept { glBindBuffer(target, m_bufferID[m_index]); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Bind this buffer to a particular shader binding point.
    /// \param  target  the target type of this buffer.
    /// \param  index   the binding point index to use.
    void bindBufferBase(const GLenum& target, const GLuint& index) const noexcept {
        glBindBufferBase(target, index, m_bufferID[m_index]);
    }

    protected:
    //////////////////////////////////////////////////////////////////////
    /// Protected Attributes
    mutable GLsync m_writeFence[BufferCount]{}; ///< Fence for writing data.
    mutable GLsync m_readFence[BufferCount]{};  ///< Fence for reading data.
    GLuint m_bufferID[BufferCount]{};           ///< OpenGL object IDs.
    int m_index = 0;                            ///< Multi-buffer index.
};
}; // namespace mini

#endif // MINIGFX_GLMULTIBUFFER_HPP