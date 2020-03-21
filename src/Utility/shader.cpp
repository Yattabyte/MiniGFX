#include "Utility/shader.hpp"
#include <glad/glad.h>
#include <vector>

Shader::~Shader() {
    glDeleteShader(m_vertexID);
    glDeleteShader(m_fragmentID);
    glDeleteProgram(m_programID);
}

Shader::Shader(
    const std::string& vertexSource, const std::string& fragmentSource) noexcept
    : m_vertexID(glCreateShader(GL_VERTEX_SHADER)),
      m_fragmentID(glCreateShader(GL_FRAGMENT_SHADER)),
      m_programID(glCreateProgram()) {
    // Make vertex shader
    const auto v_cstr = vertexSource.c_str();
    glShaderSource(m_vertexID, 1, &v_cstr, nullptr);
    glCompileShader(m_vertexID);

    // Make fragment shader
    const auto f_cstr = fragmentSource.c_str();
    glShaderSource(m_fragmentID, 1, &f_cstr, nullptr);
    glCompileShader(m_fragmentID);

    // Create program
    glAttachShader(m_programID, m_vertexID);
    glAttachShader(m_programID, m_fragmentID);

    // Link program
    glLinkProgram(m_programID);

    // Validate program
    GLint param(0);
    if (glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &param); param != 0) {
        std::vector<GLchar> infoLog(param);
        glGetProgramInfoLog(
            m_programID, static_cast<GLsizei>(param), nullptr, &infoLog[0]);
        m_log = infoLog.data();
    }
    glValidateProgram(m_programID);
    glDetachShader(m_programID, m_vertexID);
    glDetachShader(m_programID, m_fragmentID);
}

bool Shader::valid() const noexcept {
    if (m_vertexID == 0 || m_fragmentID == 0 || m_programID == 0)
        return false;

    GLint param(0);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &param);
    return param != 0;
}

std::string Shader::errorLog() const { return m_log; }

void Shader::bind() const noexcept { glUseProgram(m_programID); }

void Shader::uniformLocation(const int& location, const vec3& vector) const
    noexcept {
    glProgramUniform3fv(m_programID, location, 1U, vector.data());
}

void Shader::uniformLocation(const int& location, const vec4& vector) const
    noexcept {
    glProgramUniform4fv(m_programID, location, 1U, vector.data());
}

void Shader::uniformLocation(const int& location, const mat4& matrix) const
    noexcept {
    glProgramUniformMatrix4fv(
        m_programID, location, 1, GL_FALSE, matrix.data());
}