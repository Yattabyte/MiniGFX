#include "Texture/texture1D.hpp"

//////////////////////////////////////////////////////////////////////
/// Use our shared namespace mini
using namespace mini;

//////////////////////////////////////////////////////////////////////
/// Custom Constructor
//////////////////////////////////////////////////////////////////////

Texture1D::Texture1D(
    const float* pixelData, const GLsizei& width, const bool& linear,
    const bool& anisotropy, const bool& mipmap) noexcept {
    // Create Texture & storage
    glCreateTextures(GL_TEXTURE_1D, 1, &m_glTexID);
    glTextureStorage1D(m_glTexID, 1, GL_RGBA16F, width);

    // Load Texture
    glTextureSubImage1D(m_glTexID, 0, 0, width, GL_RGBA, GL_FLOAT, pixelData);

    // Apply texture filters
    glTextureParameteri(
        m_glTexID, GL_TEXTURE_MAG_FILTER, linear ? GL_LINEAR : GL_NEAREST);
    glTextureParameteri(
        m_glTexID, GL_TEXTURE_MIN_FILTER, linear ? GL_LINEAR : GL_NEAREST);

    // Optionally apply anisotropic filtering
    if (anisotropy)
        glTextureParameterf(m_glTexID, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0F);

    // Optionally apply mipmap filtering
    if (mipmap) {
        glTextureParameteri(
            m_glTexID, GL_TEXTURE_MIN_FILTER,
            linear ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_NEAREST);
        glGenerateTextureMipmap(m_glTexID);
    }
}