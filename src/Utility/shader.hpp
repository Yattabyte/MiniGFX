#pragma once
#ifndef SHADER_HPP
#define SHADER_HPP

#include "Utility/mat.hpp"
#include "Utility/vec.hpp"
#include <string>

/** A representation of a full OpenGL shader program. */
class Shader {
    public:
    // Public (De)Constructors
    /** Destroy this shader program. */
    ~Shader();
    /** Construct am empty shader. */
    Shader() = default;
    /** Construct a shader program.
    @param  vertexSource    the source code for the vertex shader.
    @param  fragmentSource  the source code for the fragment shader.*/
    Shader(
        const std::string& vertexSource,
        const std::string& fragmentSource) noexcept;
    /** Default copy constructor. */
    Shader(const Shader& o) = delete;
    /** Default move constructor. */
    Shader(Shader&& o) noexcept = default;

    // Public Operators
    /** Default copy-assignment operator. */
    Shader& operator=(const Shader& p) = delete;
    /** Default move-assignment operator. */
    Shader& operator=(Shader&& p) noexcept = default;

    // Public Methods
    /** Check whether or not this program is valid.
    @return     true on success, false otherwise. */
    bool valid() const noexcept;
    /** Attempt to retrieve any error log for this program.
    @return     an error log if present. */
    std::string errorLog() const;
    /** Bind this shader to the currently active context for rendering. */
    void bind() const noexcept;
    /** Copy data to a specific uniform location.
    @param  location    the location in-shader to copy to.
    @param  vector      the data to copy-in. */
    void uniformLocation(const int& location, const vec3& vector) const
        noexcept;
    /** Copy data to a specific uniform location.
    @param  location    the location in-shader to copy to.
    @param  vector      the data to copy-in. */
    void uniformLocation(const int& location, const vec4& vector) const
        noexcept;
    /** Copy data to a specific uniform location.
    @param  location    the location in-shader to copy to.
    @param  matrix      the data to copy-in. */
    void uniformLocation(const int& location, const mat4& matrix) const
        noexcept;

    private:
    // Private Attributes
    /** A log populated with errors if they occur. */
    std::string m_log;
    /** OpenGL object ID's for the shader program. */
    unsigned int m_vertexID = 0U, m_fragmentID = 0U, m_programID = 0U;
};

#endif // SHADER_HPP