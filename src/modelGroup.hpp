#pragma once
#ifndef MODELGROUP_HPP
#define MODELGROUP_HPP

#include "mat.hpp"
#include "vec.hpp"
#include <glad/glad.h>
#include <vector>

/** A vector-like container of models. */
class ModelGroup {
    public:
    // Public Structures
    /** Defines an entry position and count within the container. */
    struct GroupEntry {
        /** Offset into the container memory. */
        GLsizei offset = 0;
        /** Number of vertices. */
        GLsizei count = 0;
    };

    // Public (De)Constructors
    /** Destroy this model-group. */
    ~ModelGroup();
    /** Construct a model-group container.
    @param  count   how many vertices to pre-allocate. */
    ModelGroup(const size_t count = 1024) noexcept;
    /** Default copy constructor. */
    ModelGroup(const ModelGroup& o) = default;
    /** Default move constructor. */
    ModelGroup(ModelGroup&& o) noexcept = default;

    // Public Operators
    /** Default copy-assignment operator. */
    ModelGroup& operator=(const ModelGroup& p) = default;
    /** Default move-assignment operator. */
    ModelGroup& operator=(ModelGroup&& p) noexcept = default;

    // Public Methods
    /** Bind this model-group to the current context for rendering. */
    void bind() const noexcept;
    /** Draw this model.
    @param  drawMode    either GL_TRIANGLES, GL_POINTS, GL_LINES, etc.
    @param  entry       range of the container to draw. */
    static void draw(const int& drawMode, const GroupEntry& entry) noexcept;
    /** Expand the container to at least this size.
    @param  size        the new size to use (if larger). */
    void resize(const size_t& size);
    /** Add a model to the end of the container.
    @param  data        the geometric data to use.
    @return             entry tag corresponding to this model. */
    GroupEntry addModel(const std::vector<vec3>& data);

    private:
    // Private Attributes
    GLsync m_fence = nullptr;
    GLuint m_vaoID = 0U;
    GLuint m_vboID = 0U;
    size_t m_size = 0ULL;
    size_t m_capacity = 0ULL;
};

#endif // MODELGROUP_HPP