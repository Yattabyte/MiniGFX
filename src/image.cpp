#include "image.hpp"
#include <algorithm>

Image::Image(const std::vector<float>& pixelData, const vec2& size)
    : m_pixelData(std::make_unique<float[]>(pixelData.size())), m_size(size) {
    std::copy(
        &pixelData[0], &pixelData[pixelData.size() - 1ULL], &m_pixelData[0]);
}

void Image::fill(
    const Fill_Policy& fillPolicy, const vec4& primaryColor,
    const vec4& secondaryColor) {
    (*this) = generate(m_size, fillPolicy, primaryColor, secondaryColor);
}

Image Image::generate(
    const vec2& size, const Fill_Policy& fillPolicy, const vec4& primaryColor,
    const vec4& secondaryColor) {
    const auto pixelCount =
        static_cast<size_t>(size.x()) * static_cast<size_t>(size.y());
    const auto componentCount = pixelCount * 4ULL;
    std::vector<float> pixelData(componentCount);
    if (fillPolicy == Fill_Policy::SOLID) {
        size_t pxComponent(0ULL);
        std::generate(
            pixelData.begin(), pixelData.begin() + componentCount,
            [&]() noexcept { return primaryColor[(pxComponent++) % 4]; });
    } else if (fillPolicy == Fill_Policy::CHECKERED) {
        // How many pixels wide and tall the checkers should be
        constexpr auto checkerSize = 32ULL;
        const auto rowWidth = static_cast<size_t>(size.x());
        const float colors[2][4] = { { primaryColor.x(), primaryColor.y(),
                                       primaryColor.z(), primaryColor.w() },
                                     { secondaryColor.x(), secondaryColor.y(),
                                       secondaryColor.z(),
                                       secondaryColor.w() } };
        bool cFlip = false;
        for (size_t pixel = 0, depth = static_cast<size_t>(-1);
             pixel < pixelCount; ++pixel) {
            // Flip color if we've drawn enough of the checker
            if ((pixel % checkerSize) == 0)
                cFlip = !cFlip;
            // Increment depth when we finish a row
            if ((pixel % rowWidth) == 0) {
                depth++;
                if (depth % checkerSize == 0)
                    cFlip = !cFlip;
            }
            // Copy color info into pixel spot
            std::copy(
                &colors[cFlip][0], &colors[cFlip][4], &pixelData[pixel * 4]);
        }
    }
    return Image(pixelData, size);
}

const float* Image::data() const noexcept { return m_pixelData.get(); }

vec2 Image::size() const noexcept { return m_size; }