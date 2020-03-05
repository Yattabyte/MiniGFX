#pragma once
#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include "image.hpp"
#include <glad/glad.h>

/** A wrapper around an OpenGL texture object. */
class Texture2D {
    public:
    // Public (De)Constructors
    /** Destroy the Texture. */
    ~Texture2D();
    /** Construct a Texture with a given size and data.
    @param  pixelData   the image pixels.
    @param  width       the image width.
    @param  height      the image height.
    @param  linear      whether to apply linear filtering.
    @param  anisotropy  whether to use anisotropic filtering.
    @param  mipmap      whether to apply mipmapping. */
    Texture2D(
        const float* pixelData, const GLsizei& width, const GLsizei& height,
        const bool& linear, const bool& anisotropy,
        const bool& mipmap) noexcept;
    /** Construct a Texture using an Image object.
    @param	image		the image to use.
    @param  linear      whether to apply linear filtering.
    @param  anisotropy  whether to use anisotropic filtering.
    @param  mipmap      whether to apply mipmapping. */
    explicit Texture2D(
        const Image& image, const bool& linear, const bool& anisotropy,
        const bool& mipmap) noexcept;

    // Public Methods
    /** Makes this texture active at a specific texture unit.
    @param	textureUnit	the texture unit to make this texture active at. */
    void bind(const unsigned int& textureUnit) noexcept;

    private:
    // Private Deleted Constructors
    /** Disallow asset move constructor. */
    inline Texture2D(Texture2D&&) noexcept = delete;
    /** Disallow asset copy constructor. */
    inline Texture2D(const Texture2D&) noexcept = delete;

    // Private Deleted Operators
    /** Disallow asset move assignment. */
    inline Texture2D& operator=(Texture2D&&) noexcept = delete;
    /** Disallow asset copy assignment. */
    inline Texture2D& operator=(const Texture2D&) noexcept = delete;

    // Private Attributes
    GLuint m_glTexID = 0;
};

#endif // TEXTURE2D_HPP