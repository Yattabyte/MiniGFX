#pragma once
#ifndef TEXTURE3D_HPP
#define TEXTURE3D_HPP

#include <glad/glad.h>

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
        const float* pixelData, const GLsizei& width, const GLsizei& depth,
        const GLsizei& height, const bool& linear, const bool& anisotropy,
        const bool& mipmap) noexcept;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Makes this texture active at a specific texture unit.
    /// \param  textureUnit     the texture unit to make this texture active at.
    void bind(const unsigned int& textureUnit) const noexcept {
        glBindTextureUnit(textureUnit, m_glTexID);
    }

    private:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Disallow asset move constructor.
    Texture3D(Texture3D&&) noexcept = delete;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Disallow asset copy constructor.
    Texture3D(const Texture3D&) noexcept = delete;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Disallow asset move assignment.
    Texture3D& operator=(Texture3D&&) noexcept = delete;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Disallow asset copy assignment.
    Texture3D& operator=(const Texture3D&) noexcept = delete;

    GLuint m_glTexID = 0; ///< OpenGL texture object ID.
};

#endif // TEXTURE3D_HPP