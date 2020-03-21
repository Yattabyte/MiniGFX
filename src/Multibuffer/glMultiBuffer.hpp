#pragma once
#ifndef GLMULTIBUFFER_HPP
#define GLMULTIBUFFER_HPP

#include <glad/glad.h>

/** An encapsulation of an OpenGL GPU-backed memory multi-buffer. */
template <int BufferCount = 3> class glMultiBuffer {
    public:
    // Public (De)Constructors
    /** Virtual Destructor. */
    virtual ~glMultiBuffer() = default;
    /** Default constructor. */
    glMultiBuffer() noexcept = default;
    /** Move constructor. */
    glMultiBuffer(glMultiBuffer&&) noexcept = default;
    /** Copy constructor. */
    glMultiBuffer(const glMultiBuffer&) noexcept = default;

    // Public Operators
    /** Move assignment. */
    glMultiBuffer& operator=(glMultiBuffer&&) noexcept = default;
    /** Copy assignment. */
    glMultiBuffer& operator=(const glMultiBuffer&) noexcept = default;

    // Public Methods
    /** Wait for the fence at the supplied index to pass.
    @param	fence			the fence belonging to a particular internal
    buffer. */
    static void WaitForFence(GLsync& fence) noexcept {
        while (fence) {
            GLbitfield waitFlags = 0;
            if (const auto waitReturn = glClientWaitSync(fence, waitFlags, 1);
                waitReturn == GL_SIGNALED ||
                waitReturn == GL_ALREADY_SIGNALED ||
                waitReturn == GL_CONDITION_SATISFIED) {
                glDeleteSync(fence);
                fence = nullptr;
                return;
            }
            waitFlags = GL_SYNC_FLUSH_COMMANDS_BIT;
        }
    }
    /** Prepare this buffer for writing, waiting on any unfinished reads. */
    void beginWriting() const noexcept {
        // Ensure all reads and writes at this index have finished.
        WaitForFence(m_writeFence[m_index]);
        WaitForFence(m_readFence[m_index]);
    }
    /** Signal that this multi-buffer is finished being written to. */
    void endWriting() const noexcept {
        if (!m_writeFence[m_index])
            m_writeFence[m_index] =
                glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
    }
    /** Signal that this multi-buffer is finished being read from. */
    void endReading() noexcept {
        if (!m_readFence[m_index])
            m_readFence[m_index] =
                glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
        m_index = (m_index + 1) % BufferCount;
    }
    /** Bind this buffer to the target specified.
    @param	target			the target type of this buffer. */
    void bindBuffer(const GLenum& target) const noexcept {
        glBindBuffer(target, m_bufferID[m_index]);
    }
    /** Bind this buffer to a particular shader binding point.
    @param	target			the target type of this buffer.
    @param	index			the binding point index to use. */
    void bindBufferBase(const GLenum& target, const GLuint& index) const
        noexcept {
        glBindBufferBase(target, index, m_bufferID[m_index]);
    }

    protected:
    // Protected Attributes
    /** Fence for safely writing data. */
    mutable GLsync m_writeFence[BufferCount]{};
    /** Fence for safely reading data. */
    mutable GLsync m_readFence[BufferCount]{};
    /** OpenGL object IDs for this multi-buffer. */
    GLuint m_bufferID[BufferCount]{};
    /** Index into the multi-buffer. */
    int m_index = 0;
};

#endif // GLMULTIBUFFER_HPP