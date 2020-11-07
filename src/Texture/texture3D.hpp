#pragma once
#ifndef MINIGFX_TEXTURE3D_HPP
#define MINIGFX_TEXTURE3D_HPP

#include <glad/glad.h>

namespace mini {
//////////////////////////////////////////////////////////////////////
/// \class  Texture3D
/// \brief  A wrapper around an OpenGL texture object.
class Texture3D {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Destroy the Texture.
    ~Texture3D() { glDeleteTextures(1, &m_glTexID); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a Texture with a given size and data.
    /// \param  pixelData       the image pixels.
    /// \param  width           the image width.
    /// \param  height          the image height.
    /// \param  depth           the image  depth.
    /// \param  linear          whether to apply linear filtering.
    /// \param  anisotropy      whether to use anisotropic filtering.
    /// \param  mipmap          whether to apply mipmapping.
    Texture3D(
        const float* pixelData, const GLsizei& width, const GLsizei& depth, const GLsizei& height, const bool& linear,
        const bool& anisotropy, const bool& mipmap);
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default asset move constructor.
    Texture3D(Texture3D&&) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Default asset move assignment.
    Texture3D& operator=(Texture3D&&) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Makes this texture active at a specific texture unit.
    /// \param  textureUnit     the texture unit to make this texture active at.
    void bind(const unsigned int& textureUnit) const noexcept { glBindTextureUnit(textureUnit, m_glTexID); }

    private:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Deleted asset copy constructor.
    Texture3D(const Texture3D&) noexcept = delete;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Deleted asset copy assignment.
    Texture3D& operator=(const Texture3D&) noexcept = delete;

    //////////////////////////////////////////////////////////////////////
    /// Private Attributes
    GLuint m_glTexID = 0; ///< OpenGL texture object ID.
};
}; // namespace mini

#endif // MINIGFX_TEXTURE3D_HPP