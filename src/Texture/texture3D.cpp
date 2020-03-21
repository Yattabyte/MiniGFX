#include "Texture/texture3D.hpp"

Texture3D::~Texture3D() { glDeleteTextures(1, &m_glTexID); }

Texture3D::Texture3D(
    const float* pixelData, const GLsizei& width, const GLsizei& depth,
    const GLsizei& height, const bool& linear, const bool& anisotropy,
    const bool& mipmap) noexcept {
    // Create Texture & storage
    glCreateTextures(GL_TEXTURE_3D, 1, &m_glTexID);
    glTextureStorage3D(m_glTexID, 1, GL_RGBA16F, width, height, depth);

    // Load Texture
    glTextureSubImage3D(
        m_glTexID, 0, 0, 0, 0, width, height, depth, GL_RGBA, GL_FLOAT,
        pixelData);

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

void Texture3D::bind(const unsigned int& textureUnit) noexcept {
    glBindTextureUnit(textureUnit, m_glTexID);
}