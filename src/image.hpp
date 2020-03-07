#pragma once
#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "vec.hpp"
#include <memory>
#include <vector>

/** Policies for filling in images when data is missing. */
enum class Fill_Policy {
    SOLID,
    CHECKERED,
};

/** A way of expressing and manipulating image data. */
class Image {
    public:
    // Public (De)Constructors
    /** Default Destructor */
    ~Image() = default;
    /** Default Constructor. */
    Image() = default;
    /** Construct an image with a specific size and pixels.
    @param  pixelData       the image pixels.
    @param  size            the image size. */
    Image(const std::vector<float>& pixelData, const vec2& size);
    /** Default move constructor. */
    Image(Image&& o) noexcept = default;

    // Operators
    /** Default move-assignment operator. */
    Image& operator=(Image&& p) noexcept = default;

    // Methods
    /** Fill this image with pixels of the supplied policy.
    @param  fillPolicy      directive to fill solid, checkered, etc.
    @param	primaryColor	the primary color to use.
    @param	secondaryColor	the secondary color to use. */
    void fill(
        const Fill_Policy& fillPolicy, const vec4& primaryColor,
        const vec4& secondaryColor);
    /** Generate an image with pixels of the supplied policy.
    @param  size            the size to make the image.
    @param  fillPolicy      directive to fill solid, checkered, etc.
    @param	primaryColor	the primary color to use.
    @param	secondaryColor	the secondary color to use.
    @return                 an image using the supplied directives. */
    static Image generate(
        const vec2& size, const Fill_Policy& fillPolicy,
        const vec4& primaryColor, const vec4& secondaryColor);
    /** Retrieve a pointer to the underlying pixel data.
    @return     pointer to underlying pixel data. */
    const float* data() const noexcept;
    /** Retrieve the image size.
    @return     the size of the image. */
    vec2 size() const noexcept;

    private:
    // Private Deleted
    /** Default copy constructor. */
    Image(const Image& o) = delete;
    /** Default copy-assignment operator. */
    Image& operator=(const Image& p) = delete;

    // Private Attributes
    std::unique_ptr<float[]> m_pixelData;
    vec2 m_size;
};

#endif // IMAGE_HPP