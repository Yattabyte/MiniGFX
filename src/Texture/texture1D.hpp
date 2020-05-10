#pragma once
#ifndef MINIGFX_TEXTURE1D_HPP
#define MINIGFX_TEXTURE1D_HPP

#include <glad/glad.h>

namespace mini {
//////////////////////////////////////////////////////////////////////
/// \class  Texture1D
/// \brief  A wrapper around an OpenGL texture object.
class Texture1D {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Destroy the Texture.
    ~Texture1D() { glDeleteTextures(1, &m_glTexID); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a Texture with a given size and data.
    /// \param  pixelData       the image pixels.
    /// \param  width           the image width.
    /// \param  linear          whether to apply linear filtering.
    /// \param  anisotropy      whether to use anisotropic filtering.
    /// \param  mipmap          whether to apply mipmapping.
    Texture1D(
        const float* pixelData, const GLsizei& width, const bool& linear,
        const bool& anisotropy, const bool& mipmap) noexcept;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Makes this texture active at a specific texture unit.
    /// \param  textureUnit     the texture unit to make this texture active at.
    void bind(const unsigned int& textureUnit) const noexcept {
        glBindTextureUnit(textureUnit, m_glTexID);
    }

    private:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Disallow asset move constructor.
    Texture1D(Texture1D&&) noexcept = delete;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Disallow asset copy constructor.
    Texture1D(const Texture1D&) noexcept = delete;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Disallow asset move assignment.
    Texture1D& operator=(Texture1D&&) noexcept = delete;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Disallow asset copy assignment.
    Texture1D& operator=(const Texture1D&) noexcept = delete;

    GLuint m_glTexID = 0; ///< OpenGL texture object ID.
};
}; // namespace mini

#endif // MINIGFX_TEXTURE1D_HPP