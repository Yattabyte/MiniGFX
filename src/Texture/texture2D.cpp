#include "Texture/texture2D.hpp"

//////////////////////////////////////////////////////////////////////
/// Useful Aliases
using mini::Image;
using mini::Texture2D;
constexpr auto MAX_ANISOTROPY = 16.0F;

//////////////////////////////////////////////////////////////////////
/// Custom Constructor
//////////////////////////////////////////////////////////////////////

Texture2D::Texture2D(
    const float* pixelData, const GLsizei width, const GLsizei height, const bool linear, const bool anisotropy,
    const bool mipmap) {
    // Create Texture & storage
    glCreateTextures(GL_TEXTURE_2D, 1, &m_glTexID);
    glTextureStorage2D(m_glTexID, 1, GL_RGBA16F, width, height);

    // Load Texture
    glTextureSubImage2D(m_glTexID, 0, 0, 0, width, height, GL_RGBA, GL_FLOAT, pixelData);

    // Apply texture filters
    glTextureParameteri(m_glTexID, GL_TEXTURE_MAG_FILTER, linear ? GL_LINEAR : GL_NEAREST);
    glTextureParameteri(m_glTexID, GL_TEXTURE_MIN_FILTER, linear ? GL_LINEAR : GL_NEAREST);

    // Optionally apply anisotropic filtering
    if (anisotropy) {
        glTextureParameterf(m_glTexID, GL_TEXTURE_MAX_ANISOTROPY_EXT, MAX_ANISOTROPY);
    }

    // Optionally apply mipmap filtering
    if (mipmap) {
        glTextureParameteri(
            m_glTexID, GL_TEXTURE_MIN_FILTER, linear ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_NEAREST);
        glGenerateTextureMipmap(m_glTexID);
    }
}

//////////////////////////////////////////////////////////////////////

Texture2D::Texture2D(const Image& image, const bool linear, const bool anisotropy, const bool mipmap)
    : Texture2D(
          image.data(), static_cast<GLsizei>(image.size().x()), static_cast<GLsizei>(image.size().y()), linear,
          anisotropy, mipmap) {}