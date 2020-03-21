#pragma once
#ifndef MODEL_HPP
#define MODEL_HPP

#include "Utility/mat.hpp"
#include "Utility/vec.hpp"
#include <glad/glad.h>
#include <vector>

/** A representation of an OpenGL model. */
class Model {
    public:
    // Public (De)Constructors
    /** Destroy this model. */
    ~Model();
    /** Construct a model given a vertex set.
    @param  vertices   the vertices to use (as triangles). */
    explicit Model(const std::vector<vec3>& vertices) noexcept;
    /** Default copy constructor. */
    Model(const Model& o) = default;
    /** Default move constructor. */
    Model(Model&& o) noexcept = default;

    // Public Operators
    /** Default copy-assignment operator. */
    Model& operator=(const Model& p) = default;
    /** Default move-assignment operator. */
    Model& operator=(Model&& p) noexcept = default;

    // Public Methods
    /** Bind this model to the current context for rendering. */
    void bind() const noexcept;
    /** Draw this model.
    @param  drawMode    either GL_TRIANGLES, GL_POINTS, GL_LINES, etc. */
    void draw(const int& drawMode) const noexcept;

    private:
    // Private Attributes
    /** The number of vertices in this model. */
    size_t m_vertexCount = 0ULL;
    /** The OpenGL vertex array object ID. */
    GLuint m_vaoID = 0U;
    /** The OpenGL vertex buffer object ID. */
    GLuint m_vboID = 0U;
};

#endif // MODEL_HPP