#pragma once
#ifndef TEXTURE1D_HPP
#define TEXTURE1D_HPP

#include <glad/glad.h>

/** A wrapper around an OpenGL texture object. */
class Texture1D {
    public:
    // Public (De)Constructors
    /** Destroy the Texture. */
    ~Texture1D();
    /** Construct a Texture with a given size and data.
    @param  pixelData   the image pixels.
    @param  width       the image width.
    @param  linear      whether to apply linear filtering.
    @param  anisotropy  whether to use anisotropic filtering.
    @param  mipmap      whether to apply mipmapping. */
    Texture1D(
        const float* pixelData, const GLsizei& width, const bool& linear,
        const bool& anisotropy, const bool& mipmap) noexcept;

    // Public Methods
    /** Makes this texture active at a specific texture unit.
    @param	textureUnit	the texture unit to make this texture active at. */
    void bind(const unsigned int& textureUnit) noexcept;

    private:
    // Private Deleted Constructors
    /** Disallow asset move constructor. */
    inline Texture1D(Texture1D&&) noexcept = delete;
    /** Disallow asset copy constructor. */
    inline Texture1D(const Texture1D&) noexcept = delete;

    // Private Deleted Operators
    /** Disallow asset move assignment. */
    inline Texture1D& operator=(Texture1D&&) noexcept = delete;
    /** Disallow asset copy assignment. */
    inline Texture1D& operator=(const Texture1D&) noexcept = delete;

    // Private Attributes
    GLuint m_glTexID = 0;
};

#endif // TEXTURE1D_HPP