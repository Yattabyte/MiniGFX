#pragma once
#ifndef MINIGFX_IMAGE_HPP
#define MINIGFX_IMAGE_HPP

#include "Utility/vec.hpp"
#include <memory>
#include <vector>

namespace mini {
//////////////////////////////////////////////////////////////////////
/// \class  Image
/// \brief  A way of expressing and manipulating image data.
class Image {
    public:
    //////////////////////////////////////////////////////////////////////
    /// Public Enumerations
    enum class Fill_Policy {
        SOLID,
        CHECKERED,
    };

    //////////////////////////////////////////////////////////////////////
    /// \brief  Default Destructor
    ~Image() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default Constructor.
    Image() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct an image with a specific size and pixels.
    /// \param  pixelData   the image pixels.
    /// \param  size the    image size.
    Image(const std::vector<float>& pixelData, const vec2& size);
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move constructor.
    Image(Image&& o) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move-assignment operator.
    Image& operator=(Image&& p) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Fill this image with pixels of the supplied policy.
    /// \param  fillPolicy      directive to fill solid, checkered, etc.
    /// \param  primaryColor    the primary color to use.
    /// \param  secondaryColor  the secondary color to use.
    void fill(const Fill_Policy fillPolicy, const vec4& primaryColor, const vec4& secondaryColor);
    //////////////////////////////////////////////////////////////////////
    /// \brief  Generate an image with pixels of the supplied policy.
    /// \param  size            the size to make the image.
    /// \param  fillPolicy      directive to fill solid, checkered, etc.
    /// \param  primaryColor    the primary color to use.
    /// \param  secondaryColor  the secondary color to use.
    /// \return an image using  the supplied directives.
    static Image
    generate(const vec2& size, const Fill_Policy fillPolicy, const vec4& primaryColor, const vec4& secondaryColor);
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve a pointer to the underlying pixel data.
    /// \return pointer to underlying pixel data.
    const float* data() const noexcept;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the image size.
    /// \return the size of the image.
    vec2 size() const noexcept;

    private:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Deleted copy constructor.
    Image(const Image& o) = delete;
    /// \brief  Deleted copy-assignment operator.
    Image& operator=(const Image& p) = delete;

    //////////////////////////////////////////////////////////////////////
    /// Private Attributes
    std::unique_ptr<float[]> m_pixelData; ///<  Pointer to the underlying pixel data.
    vec2 m_size;                          ///< Dimensions of the image.
};
}; // namespace mini

#endif // MINIGFX_IMAGE_HPP