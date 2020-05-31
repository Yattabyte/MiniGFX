#pragma once
#ifndef MINIGFX_VEC_HPP
#define MINIGFX_VEC_HPP

#include <algorithm>
#include <cmath>

namespace mini {
//////////////////////////////////////////////////////////////////////
/// \class  vec2
/// \brief  A vector of 2 floats.
class vec2 {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default destruct this vector.
    ~vec2() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default construct this vector.
    constexpr vec2() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a vector using 1 specific value.
    constexpr explicit vec2(const float& value) noexcept
        : m_data{ value, value } {}
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a vector using 2 specific attributes.
    /// \param  _x      the x value to use./// \param _y the y value to use.
    constexpr vec2(const float& _x, const float& _y) noexcept
        : m_data{ _x, _y } {}
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default copy constructor.
    constexpr vec2(const vec2& o) = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move constructor.
    constexpr vec2(vec2&& o) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Default copy-assignment operator.
    constexpr vec2& operator=(const vec2& p) = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move-assignment operator.
    constexpr vec2& operator=(vec2&& p) noexcept = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add another vector to this one.
    /// \param  o       the other vector.
    /// \return this vector plus the other vector.
    constexpr vec2 operator+(const vec2& o) const noexcept {
        return vec2{ x() + o.x(), y() + o.y() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add a scalar to this vector
    /// \param  o       the scalar to add.
    /// \return this vector plus the scalar.
    constexpr vec2 operator+(const float& o) const noexcept {
        return vec2{ x() + o, y() + o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add another vector to this one.
    /// \param  o       the other vector.
    /// \return this vector plus the other vector.
    constexpr vec2& operator+=(const vec2& o) noexcept {
        m_data[0] += o.m_data[0];
        m_data[1] += o.m_data[1];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add a scalar to this one.
    /// \param  o       the scalar to add.
    /// \return this vector plus the scalar.
    constexpr vec2& operator+=(const float& o) noexcept {
        m_data[0] += o;
        m_data[1] += o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract another vector from this one.
    /// \param  o       the other vector.
    /// \return this vector minus the other vector.
    constexpr vec2 operator-(const vec2& o) const noexcept {
        return vec2{ x() - o.x(), y() - o.y() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract a scalar from this vector.
    /// \param  o       the scalar.
    /// \return this vector minus the scalar.
    constexpr vec2 operator-(const float& o) const noexcept {
        return vec2{ x() - o, y() - o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract another vector from this one.
    /// \param  o       the other vector.
    /// \return this vector minus the other vector.
    constexpr vec2& operator-=(const vec2& o) noexcept {
        m_data[0] -= o.m_data[0];
        m_data[1] -= o.m_data[1];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract a scalar from this one.
    /// \param  o       the scalar to subtract.
    /// \return this vector minus the scalar.
    constexpr vec2& operator-=(const float& o) noexcept {
        m_data[0] -= o;
        m_data[1] -= o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by another vector.
    /// \param  o       the other vector.
    /// \return this vector multiplied by the other vector.
    constexpr vec2 operator*(const vec2& o) const noexcept {
        return vec2{ x() * o.x(), y() * o.y() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by a scalar.
    /// \param  o       the scalar.
    /// \return this vector multiplied by the scalar.
    constexpr vec2 operator*(const float& o) const noexcept {
        return vec2{ x() * o, y() * o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by another vector.
    /// \param  o       the other vector.
    /// \return this vector multiplied by the other vector.
    constexpr vec2& operator*=(const vec2& o) noexcept {
        m_data[0] *= o.m_data[0];
        m_data[1] *= o.m_data[1];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by a scalar.
    /// \param  o       the scalar.
    /// \return this vector multiplied by the scalar.
    constexpr vec2& operator*=(const float& o) noexcept {
        m_data[0] *= o;
        m_data[1] *= o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by another vector.
    /// \param  o       the other vector.
    /// \return this vector divided by the other vector.
    constexpr vec2 operator/(const vec2& o) const noexcept {
        return vec2{ x() / o.x(), y() / o.y() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by a scalar.
    /// \param  o       the scalar.
    /// \return this vector divided by the scalar.
    constexpr vec2 operator/(const float& o) const noexcept {
        return vec2{ x() / o, y() / o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by another vector.
    /// \param  o       the other vector.
    /// \return this vector divided by the other vector.
    constexpr vec2& operator/=(const vec2& o) noexcept {
        m_data[0] /= o.m_data[0];
        m_data[1] /= o.m_data[1];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by a scalar.
    /// \param  o       the scalar.
    /// \return this vector divided by the scalar.
    constexpr vec2& operator/=(const float& o) noexcept {
        m_data[0] /= o;
        m_data[1] /= o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Negative Operator
    /// \return negative version of this vector.
    constexpr vec2 operator-() const noexcept { return vec2{ -x(), -y() }; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Compare this vector against another for sorting purposes.
    /// \param  o       the other vector.
    /// \return true if this vector is less than the other vector.
    constexpr bool operator<(const vec2& o) const noexcept {
        if (x() == o.x())
            return y() < o.y();
        return x() < o.x();
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Compare against another vector.
    /// \param  o       the other vector.
    /// \return true if this equals the other vector, false otherwise.
    constexpr bool operator==(const vec2& o) const noexcept {
        return x() == o.x() && y() == o.y();
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Compare against another vector.
    /// \param  o       the other vector.
    /// \return true if this doesn't equal the other vector, false otherwise.
    constexpr bool operator!=(const vec2& o) const noexcept {
        return !(*this == o);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Index operator.
    /// \param  i       the index.
    /// \return reference to the data found at index.
    constexpr float& operator[](const size_t& i) noexcept { return m_data[i]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Const Index operator.
    /// \param  i       the index.
    /// \return reference to the data found at index.
    constexpr const float& operator[](const size_t& i) const noexcept {
        return m_data[i];
    }

    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the X component of this vector.
    /// \return reference to the X component.
    constexpr float& x() noexcept { return m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the const X component of this vector.
    /// \return const reference to the X component.
    constexpr const float& x() const noexcept { return m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the Y component of this vector.
    /// \return reference to the Y component.
    constexpr float& y() noexcept { return m_data[1]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the const Y component of this vector.
    /// \return const reference to the Y component.
    constexpr const float& y() const noexcept { return m_data[1]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get a pointer to the underlying data container.
    /// \return pointer to the data array.
    constexpr float* data() noexcept { return &m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get a const pointer to the underlying data container.
    /// \return pointer to the data array.
    constexpr const float* data() const noexcept { return &m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Normalize this vector.
    /// \return normalized version of this vector.
    vec2 normalize() const noexcept { return normalize(*this); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Normalize the supplied vector.
    /// \param  v       the vector to normalize.
    /// \return normalize version of the supplied vector.
    static vec2 normalize(const vec2& v) noexcept {
        const auto length_of_v = std::sqrt((v.x() * v.x()) + (v.y() * v.y()));
        return vec2{ v.x() / length_of_v, v.y() / length_of_v };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the dot product of this vector.
    /// \param  b       the other vector to dot against.
    /// \return dot product of this and the supplied vector.
    constexpr float dot(const vec2& b) const noexcept { return dot(*this, b); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the dot product the supplied vectors.
    /// \param  a       the first vector to dot against.
    /// \param  b       the second vector to dot against.
    /// \return dot product of a and b.
    constexpr static float dot(const vec2& a, const vec2& b) noexcept {
        return (a.x() * b.x()) + (a.y() * b.y());
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the length of this vector.
    /// \return the length of this vector.
    float length() const noexcept { return length(*this); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the length of the input vector.
    /// \param  v       the vector to check the length of.
    /// \return the length of the supplied vector.
    static float length(const vec2& v) noexcept {
        return std::sqrt((v.x() * v.x()) + (v.y() * v.y()));
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the distance between the 2 supplied vectors.
    /// \param  a       the first vector.
    /// \param  b       the second vector.
    /// \return the length of a - b.
    static float distance(const vec2& a, const vec2& b) noexcept {
        return length(a - b);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the minimum values between this and the input vector.
    /// \param  o       the other vector.
    /// \return the minimum x,y values.
    vec2 min(const vec2& o) const noexcept { return min(*this, o); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the minimum values between the 2 supplied vectors.
    /// \param  a       the first vector.
    /// \param  b       the second vector.
    /// \return the minimum x,y values.
    static vec2 min(const vec2& a, const vec2& b) noexcept {
        return vec2(
            std::min(a.m_data[0], b.m_data[0]),
            std::min(a.m_data[1], b.m_data[1]));
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the maximum values between this and the input vector.
    /// \param  o       the other vector.
    /// \return the maximum x,y values.
    vec2 max(const vec2& o) const noexcept { return max(*this, o); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the maximum values between the 2 supplied vectors.
    /// \param  a       the first vector.
    /// \param  b       the second vector.
    /// \return the maximum x,y values.
    static vec2 max(const vec2& a, const vec2& b) noexcept {
        return vec2(
            std::max(a.m_data[0], b.m_data[0]),
            std::max(a.m_data[1], b.m_data[1]));
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Clamp this vector between the 2 supplied ranges.
    /// \param  low     the lowest values vector.
    /// \param  high    the highest values vector.
    /// \return clamped x,y values between low and high.
    vec2 clamp(const vec2& low, const vec2& high) const noexcept {
        return clamp(*this, low, high);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Clamp the input vector between the 2 supplied ranges.
    /// \param  low     the lowest values vector.
    /// \param  high    the highest values vector.
    /// \return clamped x,y values between low and high.
    static vec2
    clamp(const vec2& value, const vec2& low, const vec2& high) noexcept {
        return vec2(
            std::clamp(value.m_data[0], low.m_data[0], high.m_data[0]),
            std::clamp(value.m_data[1], low.m_data[1], high.m_data[1]));
    }

    private:
    float m_data[2] = { 0.0f, 0.0f }; ///< The underlying data container.
};

//////////////////////////////////////////////////////////////////////
/// \class  vec3
/// \brief  A vector of 3 floats.
class vec3 {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default destruct this vector.
    ~vec3() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default construct this vector.
    constexpr vec3() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a vector using 1 specific value.
    constexpr explicit vec3(const float& value) noexcept
        : m_data{ value, value, value } {}
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a vector using 3 specific attributes.
    /// \param _x the x value to use.
    /// \param _y the y value to use.
    /// \param _z the z value to use.
    constexpr vec3(const float& _x, const float& _y, const float& _z) noexcept
        : m_data{ _x, _y, _z } {}
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default copy constructor.
    constexpr vec3(const vec3& o) = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move constructor.
    constexpr vec3(vec3&& o) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Default copy-assignment operator.
    constexpr vec3& operator=(const vec3& p) = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move-assignment operator.
    constexpr vec3& operator=(vec3&& p) noexcept = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add another vector to this one.
    /// \param  o       the other vector.
    /// \return this vector plus the other vector.
    constexpr vec3 operator+(const vec3& o) const noexcept {
        return vec3{ x() + o.x(), y() + o.y(), z() + o.z() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add a scalar to this vector.
    /// \param  o       the scalar
    /// \return this vector plus the scalar.
    constexpr vec3 operator+(const float& o) const noexcept {
        return vec3{ x() + o, y() + o, z() + o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add another vector to this one.
    /// \param  o       the other vector.
    /// \return this vector plus the other vector.
    constexpr vec3& operator+=(const vec3& o) noexcept {
        m_data[0] += o.m_data[0];
        m_data[1] += o.m_data[1];
        m_data[2] += o.m_data[2];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add a scalar to this one.
    /// \param  o       the scalar.
    /// \return this vector plus the scalar.
    constexpr vec3& operator+=(const float& o) noexcept {
        m_data[0] += o;
        m_data[1] += o;
        m_data[2] += o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract another vector from this one.
    /// \param  o       the other vector.
    /// \return this vector minus the other vector.
    constexpr vec3 operator-(const vec3& o) const noexcept {
        return vec3{ x() - o.x(), y() - o.y(), z() - o.z() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract a scalar from this one.
    /// \param  o       the scalar.
    /// \return this vector minus the scalar.
    constexpr vec3 operator-(const float& o) const noexcept {
        return vec3{ x() - o, y() - o, z() - o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract another vector from this one.
    /// \param  o       the other vector.
    /// \return this vector minus the other vector.
    constexpr vec3& operator-=(const vec3& o) noexcept {
        m_data[0] -= o.m_data[0];
        m_data[1] -= o.m_data[1];
        m_data[2] -= o.m_data[2];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract a scalar from this one.
    /// \param  o       the scalar.
    /// \return this vector minus the scalar.
    constexpr vec3& operator-=(const float& o) noexcept {
        m_data[0] -= o;
        m_data[1] -= o;
        m_data[2] -= o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by another vector.
    /// \param  o       the other vector.
    /// \return this vector multiplied by the other vector.
    constexpr vec3 operator*(const vec3& o) const noexcept {
        return vec3{ x() * o.x(), y() * o.y(), z() * o.z() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by a scalar.
    /// \param  o       the scalar.
    /// \return this vector multiplied by the scalar.
    constexpr vec3 operator*(const float& o) const noexcept {
        return vec3{ x() * o, y() * o, z() * o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by another vector.
    /// \param  o       the other vector.
    /// \return this vector multiplied by the other vector.
    constexpr vec3& operator*=(const vec3& o) noexcept {
        m_data[0] *= o.m_data[0];
        m_data[1] *= o.m_data[1];
        m_data[2] *= o.m_data[2];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by a scalar.
    /// \param  o       the scalar.
    /// \return this vector multiplied by the scalar.
    constexpr vec3& operator*=(const float& o) noexcept {
        m_data[0] *= o;
        m_data[1] *= o;
        m_data[2] *= o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by another vector.
    /// \param  o       the other vector.
    /// \return this vector divided by the other vector.
    constexpr vec3 operator/(const vec3& o) const noexcept {
        return vec3{ x() / o.x(), y() / o.y(), z() / o.z() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by a scalar.
    /// \param  o       the scalar.
    /// \return this vector divided by the scalar.
    constexpr vec3 operator/(const float& o) const noexcept {
        return vec3{ x() / o, y() / o, z() / o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by another vector.
    /// \param  o       the other vector.
    /// \return this vector divided by the other vector.
    constexpr vec3& operator/=(const vec3& o) noexcept {
        m_data[0] /= o.m_data[0];
        m_data[1] /= o.m_data[1];
        m_data[2] /= o.m_data[2];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by a scalar.
    /// \param  o       the scalar.
    /// \return this vector divided by the scalar.
    constexpr vec3& operator/=(const float& o) noexcept {
        m_data[0] /= o;
        m_data[1] /= o;
        m_data[2] /= o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Negative Operator
    /// \return negative version of this vector.
    constexpr vec3 operator-() const noexcept {
        return vec3{ -x(), -y(), -z() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Compare this vector against another for sorting purposes.
    /// \param  o       the other vector.
    /// \return true if this vector is less than the other vector.
    constexpr bool operator<(const vec3& o) const noexcept {
        if (z() == o.z()) {
            if (x() == o.x())
                return y() < o.y();
            return x() < o.x();
        }
        return z() < o.z();
    };
    //////////////////////////////////////////////////////////////////////
    /// \brief  Compare against another vector.
    /// \param  o       the other vector.
    /// \return true if this equals the  other vector, false otherwise.
    constexpr bool operator==(const vec3& o) const noexcept {
        return x() == o.x() && y() == o.y() && z() == o.z();
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Compare against another vector.
    /// \param  o       the other vector.
    /// \return true if this doesn't equal the other vector, false otherwise.
    constexpr bool operator!=(const vec3& o) const noexcept {
        return !(*this == o);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Index operator.
    /// \param  i       the index.
    /// \return reference to the data found at index;
    constexpr float& operator[](const size_t& i) noexcept { return m_data[i]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Const Index operator.
    /// \param i the index.
    /// \return reference to the data found at index;
    constexpr const float& operator[](const size_t& i) const noexcept {
        return m_data[i];
    }

    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the X component of this vector.
    /// \return reference to the X component.
    constexpr float& x() noexcept { return m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the const X component of this vector.
    /// \return const reference to the X component.
    constexpr const float& x() const noexcept { return m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the Y component of this vector.
    /// \return reference to the Y component.
    constexpr float& y() noexcept { return m_data[1]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the const Y component of this vector.
    /// \return const reference to the Y component.
    constexpr const float& y() const noexcept { return m_data[1]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the Z component of this vector.
    /// \return reference to the Z component.
    constexpr float& z() noexcept { return m_data[2]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the const Z component of this vector.
    /// \return const reference to the Z component.
    constexpr const float& z() const noexcept { return m_data[2]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get a pointer to the underlying data container.
    /// \return pointer to the data array.
    constexpr float* data() noexcept { return &m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get a const pointer to the underlying data container.
    /// \return pointer to the data array.
    constexpr const float* data() const noexcept { return &m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Normalize this vector.
    /// \return normalized version of this vector.
    vec3 normalize() const noexcept { return normalize(*this); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Normalize the supplied vector.
    /// \param  v       the vector to normalize.
    /// \return normalize version of the supplied vector.
    static vec3 normalize(const vec3& v) noexcept {
        const auto length_of_v =
            std::sqrt((v.x() * v.x()) + (v.y() * v.y()) + (v.z() * v.z()));
        return vec3{ v.x() / length_of_v, v.y() / length_of_v,
                     v.z() / length_of_v };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the cross product of this vector.
    /// \param  b       the other vector to cross against.
    /// \return cross product of this and the supplied vector.
    constexpr vec3 cross(const vec3& b) const noexcept {
        return cross(*this, b);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the cross product the supplied vectors.
    /// \param  a       the first vector to cross against.
    /// \param  b       the second vector to cross against.
    /// \return cross product of a and b.
    constexpr static vec3 cross(const vec3& a, const vec3& b) noexcept {
        return vec3{ a.y() * b.z() - a.z() * b.y(),
                     a.z() * b.x() - a.x() * b.z(),
                     a.x() * b.y() - a.y() * b.x() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the length of this vector.
    /// \return the length of this vector.
    float length() const noexcept { return length(*this); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the length of the input vector.
    /// \param  v       the vector to check the length of.
    /// \return the length of the supplied vector.
    static float length(const vec3& v) noexcept {
        return std::sqrt((v.x() * v.x()) + (v.y() * v.y()) + (v.z() * v.z()));
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the distance between the 2 supplied vectors.
    /// \param  a       the first vector.
    /// \param  b       the second vector.
    /// \return the length of a - b.
    static float distance(const vec3& a, const vec3& b) noexcept {
        return length(a - b);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the dot product of this vector.
    /// \param  b       the other vector to dot against.
    /// \return dot product of this and the supplied vector.
    constexpr float dot(const vec3& b) const noexcept { return dot(*this, b); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the dot product the supplied vectors.
    /// \param  a       the first vector to dot against.
    /// \param  b       the second vector to dot against.
    /// \return dot product of a and b.
    constexpr static float dot(const vec3& a, const vec3& b) noexcept {
        return (a.x() * b.x()) + (a.y() * b.y()) + (a.z() * b.z());
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the minimum values between this and the input vector.
    /// \param  o       the other vector.
    /// \return the minimum x,y,z values.
    vec3 min(const vec3& o) const noexcept { return min(*this, o); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the minimum values between the 2 supplied vectors.
    /// \param  a       the first vector.
    /// \param  b       the second vector.
    /// \return the minimum x,y,z values.
    static vec3 min(const vec3& a, const vec3& b) noexcept {
        return vec3(
            std::min(a.m_data[0], b.m_data[0]),
            std::min(a.m_data[1], b.m_data[1]),
            std::min(a.m_data[2], b.m_data[2]));
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the maximum values between this and the input vector.
    /// \param  o       the other vector.
    /// \return the maximum x,y,z values.
    vec3 max(const vec3& o) const noexcept { return max(*this, o); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the maximum values between the 2 supplied vectors.
    /// \param  a       the first vector.
    /// \param  b       the second vector.
    /// \return the maximum x,y,z values.
    static vec3 max(const vec3& a, const vec3& b) noexcept {
        return vec3(
            std::max(a.m_data[0], b.m_data[0]),
            std::max(a.m_data[1], b.m_data[1]),
            std::max(a.m_data[2], b.m_data[2]));
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Clamp this vector between the 2 supplied ranges.
    /// \param  low     the lowest values vector.
    /// \param  high    the highest values vector.
    /// \return clamped x,y,z values between low and high.
    vec3 clamp(const vec3& low, const vec3& high) const noexcept {
        return clamp(*this, low, high);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Clamp the input vector between the 2 supplied ranges.
    /// \param  low     the lowest values vector.
    /// \param  high    the highest values vector.
    /// \return clamped x,y,z values between low and high.
    static vec3
    clamp(const vec3& value, const vec3& low, const vec3& high) noexcept {
        return vec3(
            std::clamp(value.m_data[0], low.m_data[0], high.m_data[0]),
            std::clamp(value.m_data[1], low.m_data[1], high.m_data[1]),
            std::clamp(value.m_data[2], low.m_data[2], high.m_data[2]));
    }

    private:
    float m_data[3] = { 0.0f, 0.0f, 0.0f }; ///< The underlying data container.
};

//////////////////////////////////////////////////////////////////////
/// \class  vec4
/// \brief  A vector of 4 floats.
class vec4 {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default destruct this vector.
    ~vec4() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default construct this vector.
    constexpr vec4() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a vector using 1 specific value.
    constexpr explicit vec4(const float& value) noexcept
        : m_data{ value, value, value, value } {}
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a vector using 3 specific attributes.
    /// \param _x the x value to use.
    /// \param _y the y value to use.
    /// \param _z the z value to use.
    /// \param _w the z value to use.
    constexpr vec4(
        const float& _x, const float& _y, const float& _z,
        const float& _w) noexcept
        : m_data{ _x, _y, _z, _w } {}
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default copy constructor.
    constexpr vec4(const vec4& o) = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move constructor.
    constexpr vec4(vec4&& o) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Default copy-assignment operator.
    constexpr vec4& operator=(const vec4& p) = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move-assignment operator.
    constexpr vec4& operator=(vec4&& p) noexcept = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add another vector to this one.
    /// \param  o       the other vector.
    /// \return this vector plus the other vector.
    constexpr vec4 operator+(const vec4& o) const noexcept {
        return vec4{ x() + o.x(), y() + o.y(), z() + o.z(), w() + o.w() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add a scalar to this one.
    /// \param  o       the scalar.
    /// \return this vector plus the scalar.
    constexpr vec4 operator+(const float& o) const noexcept {
        return vec4{ x() + o, y() + o, z() + o, w() + o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add another vector to this one.
    /// \param  o       the other vector.
    /// \return this vector plus the other vector.
    constexpr vec4& operator+=(const vec4& o) noexcept {
        m_data[0] += o.m_data[0];
        m_data[1] += o.m_data[1];
        m_data[2] += o.m_data[2];
        m_data[3] += o.m_data[3];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add a scalar to this one.
    /// \param  o       the scalar.
    /// \return this vector plus the scalar.
    constexpr vec4& operator+=(const float& o) noexcept {
        m_data[0] += o;
        m_data[1] += o;
        m_data[2] += o;
        m_data[3] += o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract another vector from this one.
    /// \param  o       the other vector.
    /// \return this vector minus the other vector.
    constexpr vec4 operator-(const vec4& o) const noexcept {
        return vec4{ x() - o.x(), y() - o.y(), z() - o.z(), w() - o.w() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract a scalar from this one.
    /// \param  o       the scalar.
    /// \return this vector minus the scalar.
    constexpr vec4 operator-(const float& o) const noexcept {
        return vec4{ x() - o, y() - o, z() - o, w() - o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract another vector from this one.
    /// \param  o       the other vector.
    /// \return this vector minus the other vector.
    constexpr vec4& operator-=(const vec4& o) noexcept {
        m_data[0] -= o.m_data[0];
        m_data[1] -= o.m_data[1];
        m_data[2] -= o.m_data[2];
        m_data[3] -= o.m_data[3];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract a scalar from this one.
    /// \param  o       the scalar.
    /// \return this vector minus the scalar.
    constexpr vec4& operator-=(const float& o) noexcept {
        m_data[0] -= o;
        m_data[1] -= o;
        m_data[2] -= o;
        m_data[3] -= o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by another vector.
    /// \param  o       the other vector.
    /// \return this vector multiplied by the other vector.
    constexpr vec4 operator*(const vec4& o) const noexcept {
        return vec4{ x() * o.x(), y() * o.y(), z() * o.z(), w() * o.w() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by a scalar.
    /// \param  o       the scalar.
    /// \return this vector multiplied by the scalar.
    constexpr vec4 operator*(const float& o) const noexcept {
        return vec4{ x() * o, y() * o, z() * o, w() * o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by another vector.
    /// \param  o       the other vector.
    /// \return this vector multiplied by the other vector.
    constexpr vec4& operator*=(const vec4& o) noexcept {
        m_data[0] *= o.m_data[0];
        m_data[1] *= o.m_data[1];
        m_data[2] *= o.m_data[2];
        m_data[3] *= o.m_data[3];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by a scalar.
    /// \param  o       the scalar.
    /// \return this vector multiplied by the scalar.
    constexpr vec4& operator*=(const float& o) noexcept {
        m_data[0] *= o;
        m_data[1] *= o;
        m_data[2] *= o;
        m_data[3] *= o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by another vector.
    /// \param  o       the other vector.
    /// \return this vector divided by the other vector.
    constexpr vec4 operator/(const vec4& o) const noexcept {
        return vec4{ x() / o.x(), y() / o.y(), z() / o.z(), w() / o.w() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by a scalar.
    /// \param  o       the scalar.
    /// \return this vector divided by the scalar.
    constexpr vec4 operator/(const float& o) const noexcept {
        return vec4{ x() / o, y() / o, z() / o, w() / o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by another vector.
    /// \param  o       the other vector.
    /// \return this vector divided by the other vector.
    constexpr vec4& operator/=(const vec4& o) noexcept {
        m_data[0] /= o.m_data[0];
        m_data[1] /= o.m_data[1];
        m_data[2] /= o.m_data[2];
        m_data[3] /= o.m_data[3];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by a scalar.
    /// \param  o       the scalar.
    /// \return this vector divided by the scalar.
    constexpr vec4& operator/=(const float& o) noexcept {
        m_data[0] /= o;
        m_data[1] /= o;
        m_data[2] /= o;
        m_data[3] /= o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Negative Operator
    /// \return negative version of this vector.
    constexpr vec4 operator-() const noexcept {
        return vec4{ -x(), -y(), -z(), -w() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Compare against another vector.
    /// \param  o       the other vector.
    /// \return true if this equals the other vector, false otherwise.
    constexpr bool operator==(const vec4& o) const noexcept {
        return x() == o.x() && y() == o.y() && z() == o.z() && w() == o.w();
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Compare against another vector.
    /// \param  o       the other vector.
    /// \return true if this doesn't equal the other vector, false otherwise.
    constexpr bool operator!=(const vec4& o) const noexcept {
        return !(*this == o);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Index operator.
    /// \param  i       the index.
    /// \return reference to the data found at index.
    constexpr float& operator[](const size_t& i) noexcept { return m_data[i]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Const Index operator.
    /// \param  i       the index.
    /// \return reference to the data found at index.
    constexpr const float& operator[](const size_t& i) const noexcept {
        return m_data[i];
    }

    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the X component of this vector.
    /// \return reference to the X component.
    constexpr float& x() noexcept { return m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the const X component of this vector.
    /// \return const reference to the X component.
    constexpr const float& x() const noexcept { return m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the Y component of this vector.
    /// \return reference to the Y component.
    constexpr float& y() noexcept { return m_data[1]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the const Y component of this vector.
    /// \return const reference to the Y component.
    constexpr const float& y() const noexcept { return m_data[1]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the Z component of this vector.
    /// \return reference to the Z component.
    constexpr float& z() noexcept { return m_data[2]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the const Z component of this vector.
    /// \return const reference to the Z component.
    constexpr const float& z() const noexcept { return m_data[2]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the W component of this vector.
    /// \return reference to the W component.
    constexpr float& w() noexcept { return m_data[3]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the const W component of this vector.
    /// \return const reference to the W component.
    constexpr const float& w() const noexcept { return m_data[3]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get a pointer to the underlying data container.
    /// \return pointer to the data array.
    constexpr float* data() noexcept { return &m_data[0]; }
    /// \brief  Get a const pointer to the underlying data container.
    /// \return pointer to the data array.
    constexpr const float* data() const noexcept { return &m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Normalize this vector.
    /// \return normalized version of this vector.
    vec4 normalize() const noexcept { return normalize(*this); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Normalize the supplied vector.
    /// \param  v       the vector to normalize.
    /// \return normalize version of the supplied vector.
    static vec4 normalize(const vec4& v) noexcept {
        const auto length_of_v = std::sqrt(
            (v.x() * v.x()) + (v.y() * v.y()) + (v.z() * v.z()) +
            (v.w() * v.w()));
        return vec4{ v.x() / length_of_v, v.y() / length_of_v,
                     v.z() / length_of_v, v.w() / length_of_v };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the length of this vector.
    /// \return the length of this vector.
    float length() const noexcept { return length(*this); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the length of the input vector.
    /// \param  v       the vector to check the length of.
    /// \return the length of the supplied vector.
    static float length(const vec4& v) noexcept {
        return std::sqrt(
            (v.x() * v.x()) + (v.y() * v.y()) + (v.z() * v.z()) +
            (v.w() * v.w()));
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the distance between the 2 supplied vectors.
    /// \param  a       the first vector.
    /// \param  b       the second vector.
    /// \return the length of a - b.
    static float distance(const vec4& a, const vec4& b) noexcept {
        return length(a - b);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the minimum values between this and the input vector.
    /// \param  o       the other vector.
    /// \return the minimum x,y,z,w values.
    vec4 min(const vec4& o) const noexcept { return min(*this, o); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the minimum values between the 2 supplied vectors.
    /// \param  a       the first vector.
    /// \param  b       the second vector.
    /// \return the minimum x,y,z,w values.
    static vec4 min(const vec4& a, const vec4& b) noexcept {
        return vec4(
            std::min(a.m_data[0], b.m_data[0]),
            std::min(a.m_data[1], b.m_data[1]),
            std::min(a.m_data[2], b.m_data[2]),
            std::min(a.m_data[3], b.m_data[3]));
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the maximum values between this and the input vector.
    /// \param  o       the other vector.
    /// \return the maximum x,y,z,w values.
    vec4 max(const vec4& o) const noexcept { return max(*this, o); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the maximum values between the 2 supplied vectors.
    /// \param  a       the first vector.
    /// \param  b       the second vector.
    /// \return the maximum x,y,z,w values.
    static vec4 max(const vec4& a, const vec4& b) noexcept {
        return vec4(
            std::max(a.m_data[0], b.m_data[0]),
            std::max(a.m_data[1], b.m_data[1]),
            std::max(a.m_data[2], b.m_data[2]),
            std::max(a.m_data[3], b.m_data[3]));
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Clamp this vector between the 2 supplied ranges.
    /// \param  low     the lowest values vector.
    /// \param  high    the highest values vector.
    /// \return clamped x,y,z,w values between low and high.
    vec4 clamp(const vec4& low, const vec4& high) const noexcept {
        return clamp(*this, low, high);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Clamp the input vector between the 2 supplied ranges.
    /// \param  low     the lowest values vector.
    /// \param  high    the highest values vector.
    /// \return clamped x,y,z,w values between low and high.
    static vec4
    clamp(const vec4& value, const vec4& low, const vec4& high) noexcept {
        return vec4(
            std::clamp(value.m_data[0], low.m_data[0], high.m_data[0]),
            std::clamp(value.m_data[1], low.m_data[1], high.m_data[1]),
            std::clamp(value.m_data[2], low.m_data[2], high.m_data[2]),
            std::clamp(value.m_data[3], low.m_data[3], high.m_data[3]));
    }

    private:
    float m_data[4] = { 0.0f, 0.0f, 0.0f,
                        0.0f }; ///< The underlying data container.
};
}; // namespace mini

#endif // MINIGFX_VEC_HPP