#pragma once
#ifndef MODELGROUP_HPP
#define MODELGROUP_HPP

#include "Utility/mat.hpp"
#include "Utility/vec.hpp"
#include <glad/glad.h>
#include <vector>

//////////////////////////////////////////////////////////////////////
/// \class  ModelGroup
/// \brief  A vector-like container of models.
class ModelGroup {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Defines an entry position and count within the container.
    struct GroupEntry {
        GLsizei offset = 0; ///< Offset into the container memory.
        GLsizei count = 0;  ///< Number of vertices.
    };

    //////////////////////////////////////////////////////////////////////
    /// \brief  Destroy this model-group.
    ~ModelGroup();
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a model-group container.
    /// \param  count       how many vertices to pre-allocate.
    ModelGroup(const size_t count = 1024) noexcept;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default copy constructor.
    ModelGroup(const ModelGroup& o) = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move constructor.
    ModelGroup(ModelGroup&& o) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Default copy-assignment operator.
    ModelGroup& operator=(const ModelGroup& p) = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move-assignment operator.
    ModelGroup& operator=(ModelGroup&& p) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Bind this model-group to the current context for rendering.
    void bind() const noexcept { glBindVertexArray(m_vaoID); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Draw this model.
    /// \param  drawMode    either GL_TRIANGLES, GL_POINTS, GL_LINES, etc.
    /// \param  entry       range of the container to draw.
    static void draw(const int& drawMode, const GroupEntry& entry) noexcept {
        glDrawArrays(static_cast<GLenum>(drawMode), entry.offset, entry.count);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Expand the container to at least this size.
    /// \param  size        the new size to use(if larger).
    void resize(const size_t& size);
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add a model to the end of the container.
    /// \param  data        the geometric data to use.
    /// \return entry tag corresponding to this model.
    GroupEntry addModel(const std::vector<vec3>& data);

    private:
    size_t m_size = 0ULL;     ///< The number of bytes used.
    size_t m_capacity = 0ULL; ///< The total capacity allocated.
    GLuint m_vaoID = 0U;      ///< The OpenGL vertex array object ID.
    GLuint m_vboID = 0U;      ///< The OpenGL vertex buffer object ID.
    GLsync m_fence = nullptr; ///< A sync fence to avoid race conditions.
};

#endif // MODELGROUP_HPP