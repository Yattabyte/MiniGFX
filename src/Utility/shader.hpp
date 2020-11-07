#pragma once
#ifndef MINIGFX_SHADER_HPP
#define MINIGFX_SHADER_HPP

#include "Utility/mat.hpp"
#include "Utility/vec.hpp"
#include <glad/glad.h>
#include <string>

namespace mini {
//////////////////////////////////////////////////////////////////////
/// \class  Shader
/// \brief  A representation of a full OpenGL shader program.
class Shader {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Destroy this shader program.
    ~Shader();
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct am empty shader.
    Shader() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a shader program.
    /// \param  vertexSource    the source code for the vertex shader.
    /// \param  fragmentSource  the source code for the fragment shader.
    Shader(const std::string& vertexSource, const std::string& fragmentSource);
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move constructor.
    Shader(Shader&& o) noexcept = default;

    /// \brief  Default move-assignment operator.
    Shader& operator=(Shader&& p) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Check whether or not this program is valid.
    /// \return true on success, false otherwise.
    bool valid() const noexcept;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Attempt to retrieve any error log for this program.
    /// \return an error log if present.
    std::string errorLog() const { return m_log; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Bind this shader to the currently active context for rendering.
    void bind() const noexcept { glUseProgram(m_programID); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Copy data to a specific uniform location.
    /// \param  location    the location in - shader to copy to.
    /// \param  vector      the data to copy - in.
    void uniformLocation(const int& location, const vec3& vector) const noexcept;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Copy data to a specific uniform location.
    /// \param  location    the location in - shader to copy to.
    /// \param  vector      the data to copy - in.
    void uniformLocation(const int& location, const vec4& vector) const noexcept;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Copy data to a specific uniform location.
    /// \param  location    the location in - shader to copy to.
    /// \param  matrix      the data to copy - in.
    void uniformLocation(const int& location, const mat4& matrix) const noexcept;

    private:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Deleted copy constructor.
    Shader(const Shader& o) = delete;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Deleted copy-assignment operator.
    Shader& operator=(const Shader& p) = delete;

    //////////////////////////////////////////////////////////////////////
    /// Private Attributes
    std::string m_log;                                           ///< Error log.
    GLuint m_vertexID = 0U, m_fragmentID = 0U, m_programID = 0U; ///< OpenGL object ID's.
};
}; // namespace mini

#endif // MINIGFX_SHADER_HPP