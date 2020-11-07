#include "Texture/image.hpp"
#include <array>

//////////////////////////////////////////////////////////////////////
/// Useful Aliases
using mini::Image;
using mini::vec2;

//////////////////////////////////////////////////////////////////////
/// Custom Constructor
//////////////////////////////////////////////////////////////////////

Image::Image(const std::vector<float>& pixelData, const vec2& size)
    : m_pixelData(std::make_unique<float[]>(pixelData.size())), m_size(size) {
    std::copy(&pixelData[0], &pixelData[pixelData.size() - 1ULL], &m_pixelData[0]);
}

//////////////////////////////////////////////////////////////////////
/// fill
//////////////////////////////////////////////////////////////////////

void Image::fill(const Fill_Policy& fillPolicy, const vec4& primaryColor, const vec4& secondaryColor) {
    (*this) = generate(m_size, fillPolicy, primaryColor, secondaryColor);
}

//////////////////////////////////////////////////////////////////////
/// generate
//////////////////////////////////////////////////////////////////////

Image Image::generate(
    const vec2& size, const Fill_Policy& fillPolicy, const vec4& primaryColor, const vec4& secondaryColor) {
    const auto pixelCount = static_cast<size_t>(size.x()) * static_cast<size_t>(size.y());
    const auto componentCount = pixelCount * 4ULL;
    std::vector<float> pixelData(componentCount);
    if (fillPolicy == Fill_Policy::SOLID) {
        size_t pxComponent(0ULL);
        std::generate(pixelData.begin(), pixelData.begin() + componentCount, [&]() noexcept {
            return primaryColor[(pxComponent++) % 4];
        });
    } else if (fillPolicy == Fill_Policy::CHECKERED) {
        // How many pixels wide and tall the checkers should be
        constexpr auto checkerSize = 32ULL;
        const auto rowWidth = static_cast<size_t>(size.x());
        const std::array<std::array<float, 4>, 2> colors = {
            std::array<float, 4>{ primaryColor.x(), primaryColor.y(), primaryColor.z(), primaryColor.w() },
            { secondaryColor.x(), secondaryColor.y(), secondaryColor.z(), secondaryColor.w() }
        };
        bool cFlip = false;
        for (size_t pixel = 0, depth = static_cast<size_t>(-1); pixel < pixelCount; ++pixel) {
            // Flip color if we've drawn enough of the checker
            if ((pixel % checkerSize) == 0) {
                cFlip = !cFlip;
            }
            // Increment depth when we finish a row
            if ((pixel % rowWidth) == 0) {
                depth++;
                if (depth % checkerSize == 0) {
                    cFlip = !cFlip;
                }
            }
            // Copy color info into pixel spot
            std::copy(colors[cFlip].begin(), colors[cFlip].end(), &pixelData[pixel * 4]);
        }
    }
    return Image(pixelData, size);
}

//////////////////////////////////////////////////////////////////////
/// data
//////////////////////////////////////////////////////////////////////

const float* Image::data() const noexcept { return m_pixelData.get(); }

//////////////////////////////////////////////////////////////////////
/// size
//////////////////////////////////////////////////////////////////////

vec2 Image::size() const noexcept { return m_size; }