#pragma once
#ifndef GLBUFFER_HPP
#define GLBUFFER_HPP

#include <glad/glad.h>

/** An encapsulation of an OpenGL GPU-backed memory buffer. */
class glBuffer {
    public:
    // Public (De)Constructors
    /** Virtual Destructor. */
    virtual ~glBuffer() = default;
    /** Default constructor. */
    glBuffer() noexcept = default;
    /** Move constructor. */
    glBuffer(glBuffer&&) noexcept = default;
    /** Copy constructor. */
    glBuffer(const glBuffer&) noexcept = default;

    // Public Operators
    /** Move assignment. */
    glBuffer& operator=(glBuffer&&) noexcept = default;
    /** Copy assignment. */
    glBuffer& operator=(const glBuffer&) noexcept = default;

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
        WaitForFence(m_writeFence);
        WaitForFence(m_readFence);
    }
    /** Signal that this multi-buffer is finished being written to. */
    void endWriting() const noexcept {
        if (!m_writeFence)
            m_writeFence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
    }
    /** Signal that this multi-buffer is finished being read from. */
    void endReading() noexcept {
        if (!m_readFence)
            m_readFence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
    }
    /** Bind this buffer to the target specified.
    @param	target			the target type of this buffer. */
    void bindBuffer(const GLenum& target) const noexcept {
        glBindBuffer(target, m_bufferID);
    }
    /** Bind this buffer to a particular shader binding point.
    @param	target			the target type of this buffer.
    @param	index			the binding point index to use. */
    void bindBufferBase(const GLenum& target, const GLuint& index) const
        noexcept {
        glBindBufferBase(target, index, m_bufferID);
    }

    protected:
    // Protected Attributes
    /** Fence for safely writing data. */
    mutable GLsync m_writeFence = nullptr;
    /** Fence for safely reading data. */
    mutable GLsync m_readFence = nullptr;
    /** OpenGL object ID for this buffer. */
    GLuint m_bufferID = 0;
};

#endif // GLBUFFER_HPP