#pragma once
#ifndef MINIGFX_MODEL_HPP
#define MINIGFX_MODEL_HPP

#include "Utility/vec.hpp"
#include <glad/glad.h>
#include <vector>

namespace mini {
//////////////////////////////////////////////////////////////////////
/// \class  Model
/// \brief  A representation of an OpenGL model.
class Model {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Destroy this model.
    ~Model();
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a model given a vertex set.
    /// \param  vertices    the vertices to use(as triangles).
    explicit Model(const std::vector<vec3>& vertices);
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move constructor.
    Model(Model&& o) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move-assignment operator.
    Model& operator=(Model&& p) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Bind this model to the current context for rendering.
    void bind() const noexcept { glBindVertexArray(m_vaoID); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Draw this model.
    /// \param  drawMode    either GL_TRIANGLES, GL_POINTS, GL_LINES, etc.
    void draw(const int drawMode) const noexcept;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve this model's vertex count.
    /// \return the model's vertex count.
    size_t vertexCount() const noexcept { return m_vertexCount; }

    private:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Deleted copy constructor.
    Model(const Model& o) = delete;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default copy-assignment operator.
    Model& operator=(const Model& p) = delete;

    //////////////////////////////////////////////////////////////////////
    /// Private Attributes
    size_t m_vertexCount = 0ULL; ///< The number of vertices in this model.
    GLuint m_vaoID = 0U;         ///< The OpenGL vertex array object ID.
    GLuint m_vboID = 0U;         ///< The OpenGL vertex buffer object ID.
};
}; // namespace mini

#endif // MINIGFX_MODEL_HPP