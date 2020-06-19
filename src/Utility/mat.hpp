#pragma once
#ifndef MINIGFX_MAT_HPP
#define MINIGFX_MAT_HPP

#include "Utility/vec.hpp"

namespace mini {
//////////////////////////////////////////////////////////////////////
/// \class  mat4
/// \brief  A 4x4 matrix of floats.
class mat4 {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default destruct this vector.
    ~mat4() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default construct this vector.
    constexpr mat4() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct an explicit matrix of vectors, row major.
    constexpr mat4(
        const vec4& v0, const vec4& v1, const vec4& v2, const vec4& v3) noexcept
        : m_data{ v0, v1, v2, v3 } {}
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default copy constructor.
    constexpr mat4(const mat4& o) = default;
    /// \brief  Default move constructor.
    constexpr mat4(mat4&& o) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Default copy-assignment operator.
    constexpr mat4& operator=(const mat4& p) = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move-assignment operator.
    constexpr mat4& operator=(mat4&& p) noexcept = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the row at the index specified.
    /// \param  index   the row number to retrieve.
    /// \return reference to the row specified.
    constexpr vec4& operator[](const size_t& index) noexcept {
        return m_data[index];
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Compare against another matrix.
    /// \param  o   the other matrix.
    /// \return true if this equals the other matrix, false otherwise.
    constexpr bool operator==(const mat4& o) const noexcept {
        for (int x = 0; x < 4; ++x)
            if (m_data[x] != o.m_data[x])
                return false;
        return true;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Compare against another matrix.
    /// \param  o   the other vector.
    /// \return true if this doesn't equal the other matrix, false otherwise.
    constexpr bool operator!=(const mat4& o) const noexcept {
        return !(*this == o);
    }

    //////////////////////////////////////////////////////////////////////
    /// \brief  Get a pointer to the underlying data container.
    /// \return pointer to the data array.
    constexpr float* data() noexcept { return m_data[0].data(); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get a const pointer to the underlying data container.
    /// \return pointer to the data array.
    constexpr const float* data() const noexcept { return m_data[0].data(); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Create a transform matrix looking at a point.
    /// \param  eye     the eye position.
    /// \param  center  the center of the target to look at.
    /// \param  up      the up direction.
    /// \return a view matrix looking at center from eye.
    static mat4
    lookAt(const vec3& eye, const vec3& center, const vec3& up) noexcept {
        const auto f = (center - eye).normalize();
        auto u = up.normalize();
        const auto s = (f.cross(u)).normalize();
        u = s.cross(f);

        mat4 Result;
        Result[0].x() = s.x();
        Result[1].x() = s.y();
        Result[2].x() = s.z();
        Result[3].x() = -s.dot(eye);
        Result[0].y() = u.x();
        Result[1].y() = u.y();
        Result[2].y() = u.z();
        Result[3].y() = -u.dot(eye);
        Result[0].z() = -f.x();
        Result[1].z() = -f.y();
        Result[2].z() = -f.z();
        Result[3].z() = f.dot(eye);
        return Result;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Create a perspective projection matrix.
    /// \param  fovY    the vertical field of view.
    /// \param  aspect  the aspect ratio to use.
    /// \param  zNear   the near plane.
    /// \param  zFar    the far plane.
    /// \return a perspective projection 4x4 matrix.
    static mat4 perspective(
        const float& fovY, const float& aspect, const float& zNear,
        const float& zFar) noexcept {
        const float rad = fovY;
        const float tanHalfFovy = tanf(rad / static_cast<float>(2));

        mat4 Result;
        Result[0].x() = 1.0F / (aspect * tanHalfFovy);
        Result[1].y() = 1.0F / (tanHalfFovy);
        Result[2].z() = -(zFar + zNear) / (zFar - zNear);
        Result[2].w() = -1.0F;
        Result[3].z() = -(2.0F * zFar * zNear) / (zFar - zNear);
        return Result;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Create an orthographic projection matrix.
    /// \param  left        the left plane.
    /// \param  right       the right plane.
    /// \param  top         the top plane.
    /// \param  bottom      the bottom plane.
    /// \param  zNear       the near plane.
    /// \param  zFar        the far plane.
    /// \return an orthographic projection 4x4 matrix.
    static mat4 orthographic(
        const float& left, const float& right, const float& top,
        const float& bottom, const float& zNear, const float& zFar) noexcept {
        mat4 Result;
        Result[0][0] = 2.0F / (right - left);
        Result[1][1] = 2.0F / (top - bottom);
        Result[2][2] = -2.0F / (zFar - zNear);
        Result[3][0] = -(right + left) / (right - left);
        Result[3][1] = -(top + bottom) / (top - bottom);
        Result[3][2] = -(zFar + zNear) / (zFar - zNear);
        return Result;
    }

    private:
    vec4 m_data[4]{
        { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 }
    }; ///<  Container for the matrix.
};
}; // namespace mini

#endif // MINIGFX_MAT_HPP