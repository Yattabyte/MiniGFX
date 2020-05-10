#pragma once
#ifndef MINIGFX_TEXTURE2D_HPP
#define MINIGFX_TEXTURE2D_HPP

#include "Texture/image.hpp"
#include <glad/glad.h>

namespace mini {
//////////////////////////////////////////////////////////////////////
/// \class  Texture2D
/// \brief  A wrapper around an OpenGL texture object.
class Texture2D {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Destroy the Texture.
    ~Texture2D() { glDeleteTextures(1, &m_glTexID); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a Texture with a given size and data.
    /// \param  pixelData       the image pixels.
    /// \param  width           the image width.
    /// \param  height          the image height.
    /// \param  linear          whether to apply linear filtering.
    /// \param  anisotropy      whether to use anisotropic filtering.
    /// \param  mipmap          whether to apply mipmapping.
    Texture2D(
        const float* pixelData, const GLsizei& width, const GLsizei& height,
        const bool& linear, const bool& anisotropy,
        const bool& mipmap) noexcept;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a Texture using an Image object.
    /// \param  image           the image to use.
    /// \param  linear          whether to apply linear filtering.
    /// \param  anisotropy      whether to use anisotropic filtering.
    /// \param  mipmap          whether to apply mipmapping.
    Texture2D(
        const Image& image, const bool& linear, const bool& anisotropy,
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
    Texture2D(Texture2D&&) noexcept = delete;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Disallow asset copy constructor.
    Texture2D(const Texture2D&) noexcept = delete;

    // Private Deleted Operators
    //////////////////////////////////////////////////////////////////////
    /// \brief  Disallow asset move assignment.
    Texture2D& operator=(Texture2D&&) noexcept = delete;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Disallow asset copy assignment.
    Texture2D& operator=(const Texture2D&) noexcept = delete;

    GLuint m_glTexID = 0; ///< OpenGL texture object ID.
};
}; // namespace mini

#endif // MINIGFX_TEXTURE2D_HPP