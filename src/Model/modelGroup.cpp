#include "Model/modelGroup.hpp"

//////////////////////////////////////////////////////////////////////
/// Forward Declarations
static void wait_on_fence(GLsync& fence) noexcept;

//////////////////////////////////////////////////////////////////////
/// Custom Destructor
//////////////////////////////////////////////////////////////////////

ModelGroup::~ModelGroup() {
    // Delete all objects created
    glDeleteBuffers(1, &m_vboID);
    glDeleteVertexArrays(1, &m_vaoID);
    glDeleteSync(m_fence);
}

//////////////////////////////////////////////////////////////////////
/// Custom Constructor
//////////////////////////////////////////////////////////////////////

ModelGroup::ModelGroup(const size_t count) noexcept : m_capacity(count) {
    // Create GL Objects
    glCreateVertexArrays(1, &m_vaoID);
    glCreateBuffers(1, &m_vboID);

    // Load geometry into vertex buffer object
    glNamedBufferStorage(
        m_vboID, sizeof(vec3) * count, nullptr, GL_DYNAMIC_STORAGE_BIT);

    // Connect and set-up the vertex array object
    glEnableVertexArrayAttrib(m_vaoID, 0);
    glVertexArrayAttribBinding(m_vaoID, 0, 0);
    glVertexArrayAttribFormat(m_vaoID, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(m_vaoID, 0, m_vboID, 0, sizeof(vec3));
}

//////////////////////////////////////////////////////////////////////
/// resize
//////////////////////////////////////////////////////////////////////

void ModelGroup::resize(const size_t& size) {
    if (size > m_capacity) {
        // Create new set of VBO's large enough to fit old data + desired data
        const auto delta = size - m_size;
        m_capacity += delta * 2ULL;

        // Create the new VBO's
        GLuint newVBOID = 0;
        glCreateBuffers(1, &newVBOID);
        glNamedBufferStorage(
            newVBOID, m_capacity, nullptr, GL_DYNAMIC_STORAGE_BIT);

        // Copy old VBO's
        m_fence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
        glCopyNamedBufferSubData(m_vboID, newVBOID, 0, 0, m_size);

        // Delete the old VBO's
        wait_on_fence(m_fence);
        glDeleteBuffers(1, &m_vboID);

        // Overwrite old VBO ID's
        m_vboID = newVBOID;

        // Assign VAO to new VBO's
        glVertexArrayVertexBuffer(m_vaoID, 0, m_vboID, 0, sizeof(vec3));
    }
}

//////////////////////////////////////////////////////////////////////
/// addModel
//////////////////////////////////////////////////////////////////////

ModelGroup::GroupEntry ModelGroup::addModel(const std::vector<vec3>& data) {
    // Expand container and ensure data is safe to manipulate
    resize(m_size + data.size());
    wait_on_fence(m_fence);

    // Upload vertex data
    const auto offset = static_cast<GLsizei>(m_size);
    const auto count = static_cast<GLsizei>(data.size());
    m_size += count;
    glNamedBufferSubData(m_vboID, offset, count * sizeof(vec3), data.data());

    // Prepare fence
    m_fence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

    // Return entry position
    return ModelGroup::GroupEntry{ offset, count };
}

//////////////////////////////////////////////////////////////////////
/// wait_on_fence
//////////////////////////////////////////////////////////////////////

static void wait_on_fence(GLsync& fence) noexcept {
    // Do nothing if unassigned
    if (fence == nullptr)
        return;

    // Wait for data fence to be passed
    GLenum state = GL_UNSIGNALED;
    while (state != GL_SIGNALED && state != GL_ALREADY_SIGNALED &&
           state != GL_CONDITION_SATISFIED)
        state = glClientWaitSync(fence, GL_SYNC_FLUSH_COMMANDS_BIT, 1);
    glDeleteSync(fence);
    fence = nullptr;
}