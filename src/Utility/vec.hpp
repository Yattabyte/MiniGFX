#pragma once
#ifndef MINIGFX_VEC_HPP
#define MINIGFX_VEC_HPP

#include <algorithm>
#include <cmath>

namespace mini {
//////////////////////////////////////////////////////////////////////
/// Forward Declarations
template <typename DataType> class tvec2;
template <typename DataType> class tvec3;
template <typename DataType> class tvec4;
//////////////////////////////////////////////////////////////////////
/// Float variants
using vec2 = tvec2<float>;
using vec3 = tvec3<float>;
using vec4 = tvec4<float>;
//////////////////////////////////////////////////////////////////////
/// Integer variants
using ivec2 = tvec2<int>;
using ivec3 = tvec3<int>;
using ivec4 = tvec4<int>;

//////////////////////////////////////////////////////////////////////
/// \class  tvec2
/// \brief  A vector of 2 values.
template <typename DataType> class tvec2 {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default destruct this vector.
    ~tvec2() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default construct this vector.
    constexpr tvec2() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a vector using 1 specific value.
    constexpr explicit tvec2(const DataType& value) noexcept
        : m_data{ value, value } {}
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a vector using 2 specific attributes.
    /// \param  _x      the x value to use./// \param _y the y value to use.
    constexpr tvec2(const DataType& _x, const DataType& _y) noexcept
        : m_data{ _x, _y } {}
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default copy constructor.
    constexpr tvec2(const tvec2& o) = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move constructor.
    constexpr tvec2(tvec2&& o) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Default copy-assignment operator.
    constexpr tvec2& operator=(const tvec2& p) = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move-assignment operator.
    constexpr tvec2& operator=(tvec2&& p) noexcept = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add another vector to this one.
    /// \param  o       the other vector.
    /// \return this vector plus the other vector.
    constexpr tvec2 operator+(const tvec2& o) const noexcept {
        return tvec2{ x() + o.x(), y() + o.y() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add a scalar to this vector
    /// \param  o       the scalar to add.
    /// \return this vector plus the scalar.
    constexpr tvec2 operator+(const DataType& o) const noexcept {
        return tvec2{ x() + o, y() + o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add another vector to this one.
    /// \param  o       the other vector.
    /// \return this vector plus the other vector.
    constexpr tvec2& operator+=(const tvec2& o) noexcept {
        m_data[0] += o.m_data[0];
        m_data[1] += o.m_data[1];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add a scalar to this one.
    /// \param  o       the scalar to add.
    /// \return this vector plus the scalar.
    constexpr tvec2& operator+=(const DataType& o) noexcept {
        m_data[0] += o;
        m_data[1] += o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract another vector from this one.
    /// \param  o       the other vector.
    /// \return this vector minus the other vector.
    constexpr tvec2 operator-(const tvec2& o) const noexcept {
        return tvec2{ x() - o.x(), y() - o.y() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract a scalar from this vector.
    /// \param  o       the scalar.
    /// \return this vector minus the scalar.
    constexpr tvec2 operator-(const DataType& o) const noexcept {
        return tvec2{ x() - o, y() - o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract another vector from this one.
    /// \param  o       the other vector.
    /// \return this vector minus the other vector.
    constexpr tvec2& operator-=(const tvec2& o) noexcept {
        m_data[0] -= o.m_data[0];
        m_data[1] -= o.m_data[1];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract a scalar from this one.
    /// \param  o       the scalar to subtract.
    /// \return this vector minus the scalar.
    constexpr tvec2& operator-=(const DataType& o) noexcept {
        m_data[0] -= o;
        m_data[1] -= o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by another vector.
    /// \param  o       the other vector.
    /// \return this vector multiplied by the other vector.
    constexpr tvec2 operator*(const tvec2& o) const noexcept {
        return tvec2{ x() * o.x(), y() * o.y() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by a scalar.
    /// \param  o       the scalar.
    /// \return this vector multiplied by the scalar.
    constexpr tvec2 operator*(const DataType& o) const noexcept {
        return tvec2{ x() * o, y() * o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by another vector.
    /// \param  o       the other vector.
    /// \return this vector multiplied by the other vector.
    constexpr tvec2& operator*=(const tvec2& o) noexcept {
        m_data[0] *= o.m_data[0];
        m_data[1] *= o.m_data[1];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by a scalar.
    /// \param  o       the scalar.
    /// \return this vector multiplied by the scalar.
    constexpr tvec2& operator*=(const DataType& o) noexcept {
        m_data[0] *= o;
        m_data[1] *= o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by another vector.
    /// \param  o       the other vector.
    /// \return this vector divided by the other vector.
    constexpr tvec2 operator/(const tvec2& o) const noexcept {
        return tvec2{ x() / o.x(), y() / o.y() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by a scalar.
    /// \param  o       the scalar.
    /// \return this vector divided by the scalar.
    constexpr tvec2 operator/(const DataType& o) const noexcept {
        return tvec2{ x() / o, y() / o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by another vector.
    /// \param  o       the other vector.
    /// \return this vector divided by the other vector.
    constexpr tvec2& operator/=(const tvec2& o) noexcept {
        m_data[0] /= o.m_data[0];
        m_data[1] /= o.m_data[1];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by a scalar.
    /// \param  o       the scalar.
    /// \return this vector divided by the scalar.
    constexpr tvec2& operator/=(const DataType& o) noexcept {
        m_data[0] /= o;
        m_data[1] /= o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Negative Operator
    /// \return negative version of this vector.
    constexpr tvec2 operator-() const noexcept { return tvec2{ -x(), -y() }; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Compare this vector against another for sorting purposes.
    /// \param  o       the other vector.
    /// \return true if this vector is less than the other vector.
    constexpr bool operator<(const tvec2& o) const noexcept {
        if (x() == o.x())
            return y() < o.y();
        return x() < o.x();
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Compare against another vector.
    /// \param  o       the other vector.
    /// \return true if this equals the other vector, false otherwise.
    constexpr bool operator==(const tvec2& o) const noexcept {
        return x() == o.x() && y() == o.y();
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Compare against another vector.
    /// \param  o       the other vector.
    /// \return true if this doesn't equal the other vector, false otherwise.
    constexpr bool operator!=(const tvec2& o) const noexcept {
        return !(*this == o);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Index operator.
    /// \param  i       the index.
    /// \return reference to the data found at index.
    constexpr DataType& operator[](const size_t& i) noexcept {
        return m_data[i];
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Const Index operator.
    /// \param  i       the index.
    /// \return reference to the data found at index.
    constexpr const DataType& operator[](const size_t& i) const noexcept {
        return m_data[i];
    }

    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the X component of this vector.
    /// \return reference to the X component.
    constexpr DataType& x() noexcept { return m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the const X component of this vector.
    /// \return const reference to the X component.
    constexpr const DataType& x() const noexcept { return m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the Y component of this vector.
    /// \return reference to the Y component.
    constexpr DataType& y() noexcept { return m_data[1]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the const Y component of this vector.
    /// \return const reference to the Y component.
    constexpr const DataType& y() const noexcept { return m_data[1]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get a pointer to the underlying data container.
    /// \return pointer to the data array.
    constexpr DataType* data() noexcept { return &m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get a const pointer to the underlying data container.
    /// \return pointer to the data array.
    constexpr const DataType* data() const noexcept { return &m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Normalize this vector.
    /// \return normalized version of this vector.
    tvec2 normalize() const noexcept { return normalize(*this); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Normalize the supplied vector.
    /// \param  v       the vector to normalize.
    /// \return normalize version of the supplied vector.
    static tvec2 normalize(const tvec2& v) noexcept {
        const auto length_of_v = std::sqrt((v.x() * v.x()) + (v.y() * v.y()));
        return tvec2{ v.x() / length_of_v, v.y() / length_of_v };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the dot product of this vector.
    /// \param  b       the other vector to dot against.
    /// \return dot product of this and the supplied vector.
    constexpr DataType dot(const tvec2& b) const noexcept {
        return dot(*this, b);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the dot product the supplied vectors.
    /// \param  a       the first vector to dot against.
    /// \param  b       the second vector to dot against.
    /// \return dot product of a and b.
    constexpr static DataType dot(const tvec2& a, const tvec2& b) noexcept {
        return (a.x() * b.x()) + (a.y() * b.y());
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the length of this vector.
    /// \return the length of this vector.
    DataType length() const noexcept { return length(*this); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the length of the input vector.
    /// \param  v       the vector to check the length of.
    /// \return the length of the supplied vector.
    static DataType length(const tvec2& v) noexcept {
        return std::sqrt((v.x() * v.x()) + (v.y() * v.y()));
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the distance between the 2 supplied vectors.
    /// \param  a       the first vector.
    /// \param  b       the second vector.
    /// \return the length of a - b.
    static DataType distance(const tvec2& a, const tvec2& b) noexcept {
        return length(a - b);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the minimum values between this and the input vector.
    /// \param  o       the other vector.
    /// \return the minimum x,y values.
    tvec2 min(const tvec2& o) const noexcept { return min(*this, o); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the minimum values between the 2 supplied vectors.
    /// \param  a       the first vector.
    /// \param  b       the second vector.
    /// \return the minimum x,y values.
    static tvec2 min(const tvec2& a, const tvec2& b) noexcept {
        return tvec2(
            std::min(a.m_data[0], b.m_data[0]),
            std::min(a.m_data[1], b.m_data[1]));
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the maximum values between this and the input vector.
    /// \param  o       the other vector.
    /// \return the maximum x,y values.
    tvec2 max(const tvec2& o) const noexcept { return max(*this, o); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the maximum values between the 2 supplied vectors.
    /// \param  a       the first vector.
    /// \param  b       the second vector.
    /// \return the maximum x,y values.
    static tvec2 max(const tvec2& a, const tvec2& b) noexcept {
        return tvec2(
            std::max(a.m_data[0], b.m_data[0]),
            std::max(a.m_data[1], b.m_data[1]));
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Clamp this vector between the 2 supplied ranges.
    /// \param  low     the lowest values vector.
    /// \param  high    the highest values vector.
    /// \return clamped x,y values between low and high.
    tvec2 clamp(const tvec2& low, const tvec2& high) const noexcept {
        return clamp(*this, low, high);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Clamp the input vector between the 2 supplied ranges.
    /// \param  value   the value vector to clamp.
    /// \param  low     the lowest values vector.
    /// \param  high    the highest values vector.
    /// \return clamped x,y values between low and high.
    static tvec2
    clamp(const tvec2& value, const tvec2& low, const tvec2& high) noexcept {
        return tvec2(
            std::clamp(value.m_data[0], low.m_data[0], high.m_data[0]),
            std::clamp(value.m_data[1], low.m_data[1], high.m_data[1]));
    }

    private:
    DataType m_data[2] = { (DataType)0,
                           (DataType)0 }; ///< The underlying data container.
};

//////////////////////////////////////////////////////////////////////
/// \class  tvec3
/// \brief  A vector of 3 values.
template <typename DataType> class tvec3 {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default destruct this vector.
    ~tvec3() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default construct this vector.
    constexpr tvec3() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a vector using 1 specific value.
    constexpr explicit tvec3(const DataType& value) noexcept
        : m_data{ value, value, value } {}
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a vector using 3 specific attributes.
    /// \param _x the x value to use.
    /// \param _y the y value to use.
    /// \param _z the z value to use.
    constexpr tvec3(
        const DataType& _x, const DataType& _y, const DataType& _z) noexcept
        : m_data{ _x, _y, _z } {}
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default copy constructor.
    constexpr tvec3(const tvec3& o) = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move constructor.
    constexpr tvec3(tvec3&& o) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Default copy-assignment operator.
    constexpr tvec3& operator=(const tvec3& p) = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move-assignment operator.
    constexpr tvec3& operator=(tvec3&& p) noexcept = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add another vector to this one.
    /// \param  o       the other vector.
    /// \return this vector plus the other vector.
    constexpr tvec3 operator+(const tvec3& o) const noexcept {
        return tvec3{ x() + o.x(), y() + o.y(), z() + o.z() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add a scalar to this vector.
    /// \param  o       the scalar
    /// \return this vector plus the scalar.
    constexpr tvec3 operator+(const DataType& o) const noexcept {
        return tvec3{ x() + o, y() + o, z() + o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add another vector to this one.
    /// \param  o       the other vector.
    /// \return this vector plus the other vector.
    constexpr tvec3& operator+=(const tvec3& o) noexcept {
        m_data[0] += o.m_data[0];
        m_data[1] += o.m_data[1];
        m_data[2] += o.m_data[2];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add a scalar to this one.
    /// \param  o       the scalar.
    /// \return this vector plus the scalar.
    constexpr tvec3& operator+=(const DataType& o) noexcept {
        m_data[0] += o;
        m_data[1] += o;
        m_data[2] += o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract another vector from this one.
    /// \param  o       the other vector.
    /// \return this vector minus the other vector.
    constexpr tvec3 operator-(const tvec3& o) const noexcept {
        return tvec3{ x() - o.x(), y() - o.y(), z() - o.z() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract a scalar from this one.
    /// \param  o       the scalar.
    /// \return this vector minus the scalar.
    constexpr tvec3 operator-(const DataType& o) const noexcept {
        return tvec3{ x() - o, y() - o, z() - o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract another vector from this one.
    /// \param  o       the other vector.
    /// \return this vector minus the other vector.
    constexpr tvec3& operator-=(const tvec3& o) noexcept {
        m_data[0] -= o.m_data[0];
        m_data[1] -= o.m_data[1];
        m_data[2] -= o.m_data[2];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract a scalar from this one.
    /// \param  o       the scalar.
    /// \return this vector minus the scalar.
    constexpr tvec3& operator-=(const DataType& o) noexcept {
        m_data[0] -= o;
        m_data[1] -= o;
        m_data[2] -= o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by another vector.
    /// \param  o       the other vector.
    /// \return this vector multiplied by the other vector.
    constexpr tvec3 operator*(const tvec3& o) const noexcept {
        return tvec3{ x() * o.x(), y() * o.y(), z() * o.z() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by a scalar.
    /// \param  o       the scalar.
    /// \return this vector multiplied by the scalar.
    constexpr tvec3 operator*(const DataType& o) const noexcept {
        return tvec3{ x() * o, y() * o, z() * o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by another vector.
    /// \param  o       the other vector.
    /// \return this vector multiplied by the other vector.
    constexpr tvec3& operator*=(const tvec3& o) noexcept {
        m_data[0] *= o.m_data[0];
        m_data[1] *= o.m_data[1];
        m_data[2] *= o.m_data[2];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by a scalar.
    /// \param  o       the scalar.
    /// \return this vector multiplied by the scalar.
    constexpr tvec3& operator*=(const DataType& o) noexcept {
        m_data[0] *= o;
        m_data[1] *= o;
        m_data[2] *= o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by another vector.
    /// \param  o       the other vector.
    /// \return this vector divided by the other vector.
    constexpr tvec3 operator/(const tvec3& o) const noexcept {
        return tvec3{ x() / o.x(), y() / o.y(), z() / o.z() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by a scalar.
    /// \param  o       the scalar.
    /// \return this vector divided by the scalar.
    constexpr tvec3 operator/(const DataType& o) const noexcept {
        return tvec3{ x() / o, y() / o, z() / o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by another vector.
    /// \param  o       the other vector.
    /// \return this vector divided by the other vector.
    constexpr tvec3& operator/=(const tvec3& o) noexcept {
        m_data[0] /= o.m_data[0];
        m_data[1] /= o.m_data[1];
        m_data[2] /= o.m_data[2];
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by a scalar.
    /// \param  o       the scalar.
    /// \return this vector divided by the scalar.
    constexpr tvec3& operator/=(const DataType& o) noexcept {
        m_data[0] /= o;
        m_data[1] /= o;
        m_data[2] /= o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Negative Operator
    /// \return negative version of this vector.
    constexpr tvec3 operator-() const noexcept {
        return tvec3{ -x(), -y(), -z() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Compare this vector against another for sorting purposes.
    /// \param  o       the other vector.
    /// \return true if this vector is less than the other vector.
    constexpr bool operator<(const tvec3& o) const noexcept {
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
    constexpr bool operator==(const tvec3& o) const noexcept {
        return x() == o.x() && y() == o.y() && z() == o.z();
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Compare against another vector.
    /// \param  o       the other vector.
    /// \return true if this doesn't equal the other vector, false otherwise.
    constexpr bool operator!=(const tvec3& o) const noexcept {
        return !(*this == o);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Index operator.
    /// \param  i       the index.
    /// \return reference to the data found at index;
    constexpr DataType& operator[](const size_t& i) noexcept {
        return m_data[i];
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Const Index operator.
    /// \param i the index.
    /// \return reference to the data found at index;
    constexpr const DataType& operator[](const size_t& i) const noexcept {
        return m_data[i];
    }

    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the X component of this vector.
    /// \return reference to the X component.
    constexpr DataType& x() noexcept { return m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the const X component of this vector.
    /// \return const reference to the X component.
    constexpr const DataType& x() const noexcept { return m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the Y component of this vector.
    /// \return reference to the Y component.
    constexpr DataType& y() noexcept { return m_data[1]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the const Y component of this vector.
    /// \return const reference to the Y component.
    constexpr const DataType& y() const noexcept { return m_data[1]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the Z component of this vector.
    /// \return reference to the Z component.
    constexpr DataType& z() noexcept { return m_data[2]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the const Z component of this vector.
    /// \return const reference to the Z component.
    constexpr const DataType& z() const noexcept { return m_data[2]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get a pointer to the underlying data container.
    /// \return pointer to the data array.
    constexpr DataType* data() noexcept { return &m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get a const pointer to the underlying data container.
    /// \return pointer to the data array.
    constexpr const DataType* data() const noexcept { return &m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Normalize this vector.
    /// \return normalized version of this vector.
    tvec3 normalize() const noexcept { return normalize(*this); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Normalize the supplied vector.
    /// \param  v       the vector to normalize.
    /// \return normalize version of the supplied vector.
    static tvec3 normalize(const tvec3& v) noexcept {
        const auto length_of_v =
            std::sqrt((v.x() * v.x()) + (v.y() * v.y()) + (v.z() * v.z()));
        return tvec3{ v.x() / length_of_v, v.y() / length_of_v,
                      v.z() / length_of_v };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the cross product of this vector.
    /// \param  b       the other vector to cross against.
    /// \return cross product of this and the supplied vector.
    constexpr tvec3 cross(const tvec3& b) const noexcept {
        return cross(*this, b);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the cross product the supplied vectors.
    /// \param  a       the first vector to cross against.
    /// \param  b       the second vector to cross against.
    /// \return cross product of a and b.
    constexpr static tvec3 cross(const tvec3& a, const tvec3& b) noexcept {
        return tvec3{ a.y() * b.z() - a.z() * b.y(),
                      a.z() * b.x() - a.x() * b.z(),
                      a.x() * b.y() - a.y() * b.x() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the length of this vector.
    /// \return the length of this vector.
    DataType length() const noexcept { return length(*this); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the length of the input vector.
    /// \param  v       the vector to check the length of.
    /// \return the length of the supplied vector.
    static DataType length(const tvec3& v) noexcept {
        return std::sqrt((v.x() * v.x()) + (v.y() * v.y()) + (v.z() * v.z()));
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the distance between the 2 supplied vectors.
    /// \param  a       the first vector.
    /// \param  b       the second vector.
    /// \return the length of a - b.
    static DataType distance(const tvec3& a, const tvec3& b) noexcept {
        return length(a - b);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the dot product of this vector.
    /// \param  b       the other vector to dot against.
    /// \return dot product of this and the supplied vector.
    constexpr DataType dot(const tvec3& b) const noexcept {
        return dot(*this, b);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the dot product the supplied vectors.
    /// \param  a       the first vector to dot against.
    /// \param  b       the second vector to dot against.
    /// \return dot product of a and b.
    constexpr static DataType dot(const tvec3& a, const tvec3& b) noexcept {
        return (a.x() * b.x()) + (a.y() * b.y()) + (a.z() * b.z());
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the minimum values between this and the input vector.
    /// \param  o       the other vector.
    /// \return the minimum x,y,z values.
    tvec3 min(const tvec3& o) const noexcept { return min(*this, o); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the minimum values between the 2 supplied vectors.
    /// \param  a       the first vector.
    /// \param  b       the second vector.
    /// \return the minimum x,y,z values.
    static tvec3 min(const tvec3& a, const tvec3& b) noexcept {
        return tvec3(
            std::min(a.m_data[0], b.m_data[0]),
            std::min(a.m_data[1], b.m_data[1]),
            std::min(a.m_data[2], b.m_data[2]));
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the maximum values between this and the input vector.
    /// \param  o       the other vector.
    /// \return the maximum x,y,z values.
    tvec3 max(const tvec3& o) const noexcept { return max(*this, o); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the maximum values between the 2 supplied vectors.
    /// \param  a       the first vector.
    /// \param  b       the second vector.
    /// \return the maximum x,y,z values.
    static tvec3 max(const tvec3& a, const tvec3& b) noexcept {
        return tvec3(
            std::max(a.m_data[0], b.m_data[0]),
            std::max(a.m_data[1], b.m_data[1]),
            std::max(a.m_data[2], b.m_data[2]));
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Clamp this vector between the 2 supplied ranges.
    /// \param  low     the lowest values vector.
    /// \param  high    the highest values vector.
    /// \return clamped x,y,z values between low and high.
    tvec3 clamp(const tvec3& low, const tvec3& high) const noexcept {
        return clamp(*this, low, high);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Clamp the input vector between the 2 supplied ranges.
    /// \param  value   the value vector to clamp.
    /// \param  low     the lowest values vector.
    /// \param  high    the highest values vector.
    /// \return clamped x,y,z values between low and high.
    static tvec3
    clamp(const tvec3& value, const tvec3& low, const tvec3& high) noexcept {
        return tvec3(
            std::clamp(value.m_data[0], low.m_data[0], high.m_data[0]),
            std::clamp(value.m_data[1], low.m_data[1], high.m_data[1]),
            std::clamp(value.m_data[2], low.m_data[2], high.m_data[2]));
    }

    private:
    DataType m_data[3] = { DataType(0), DataType(0),
                           DataType(0) }; ///< The underlying data container.
};

//////////////////////////////////////////////////////////////////////
/// \class  tvec4
/// \brief  A vector of 4 values.
template <typename DataType> class tvec4 {
    public:
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default destruct this vector.
    ~tvec4() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default construct this vector.
    constexpr tvec4() = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a vector using 1 specific value.
    constexpr explicit tvec4(const DataType& value) noexcept
        : m_data{ value, value, value, value } {}
    //////////////////////////////////////////////////////////////////////
    /// \brief  Construct a vector using 3 specific attributes.
    /// \param _x the x value to use.
    /// \param _y the y value to use.
    /// \param _z the z value to use.
    /// \param _w the z value to use.
    constexpr tvec4(
        const DataType& _x, const DataType& _y, const DataType& _z,
        const DataType& _w) noexcept
        : m_data{ _x, _y, _z, _w } {}
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default copy constructor.
    constexpr tvec4(const tvec4& o) = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move constructor.
    constexpr tvec4(tvec4&& o) noexcept = default;

    //////////////////////////////////////////////////////////////////////
    /// \brief  Default copy-assignment operator.
    constexpr tvec4& operator=(const tvec4& p) = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Default move-assignment operator.
    constexpr tvec4& operator=(tvec4&& p) noexcept = default;
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add another vector to this one.
    /// \param  o       the other vector.
    /// \return this vector plus the other vector.
    constexpr tvec4 operator+(const tvec4& o) const noexcept {
        return tvec4{ x() + o.x(), y() + o.y(), z() + o.z(), w() + o.w() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add a scalar to this one.
    /// \param  o       the scalar.
    /// \return this vector plus the scalar.
    constexpr tvec4 operator+(const DataType& o) const noexcept {
        return tvec4{ x() + o, y() + o, z() + o, w() + o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Add another vector to this one.
    /// \param  o       the other vector.
    /// \return this vector plus the other vector.
    constexpr tvec4& operator+=(const tvec4& o) noexcept {
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
    constexpr tvec4& operator+=(const DataType& o) noexcept {
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
    constexpr tvec4 operator-(const tvec4& o) const noexcept {
        return tvec4{ x() - o.x(), y() - o.y(), z() - o.z(), w() - o.w() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract a scalar from this one.
    /// \param  o       the scalar.
    /// \return this vector minus the scalar.
    constexpr tvec4 operator-(const DataType& o) const noexcept {
        return tvec4{ x() - o, y() - o, z() - o, w() - o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Subtract another vector from this one.
    /// \param  o       the other vector.
    /// \return this vector minus the other vector.
    constexpr tvec4& operator-=(const tvec4& o) noexcept {
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
    constexpr tvec4& operator-=(const DataType& o) noexcept {
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
    constexpr tvec4 operator*(const tvec4& o) const noexcept {
        return tvec4{ x() * o.x(), y() * o.y(), z() * o.z(), w() * o.w() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by a scalar.
    /// \param  o       the scalar.
    /// \return this vector multiplied by the scalar.
    constexpr tvec4 operator*(const DataType& o) const noexcept {
        return tvec4{ x() * o, y() * o, z() * o, w() * o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Multiply by another vector.
    /// \param  o       the other vector.
    /// \return this vector multiplied by the other vector.
    constexpr tvec4& operator*=(const tvec4& o) noexcept {
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
    constexpr tvec4& operator*=(const DataType& o) noexcept {
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
    constexpr tvec4 operator/(const tvec4& o) const noexcept {
        return tvec4{ x() / o.x(), y() / o.y(), z() / o.z(), w() / o.w() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by a scalar.
    /// \param  o       the scalar.
    /// \return this vector divided by the scalar.
    constexpr tvec4 operator/(const DataType& o) const noexcept {
        return tvec4{ x() / o, y() / o, z() / o, w() / o };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Divide by another vector.
    /// \param  o       the other vector.
    /// \return this vector divided by the other vector.
    constexpr tvec4& operator/=(const tvec4& o) noexcept {
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
    constexpr tvec4& operator/=(const DataType& o) noexcept {
        m_data[0] /= o;
        m_data[1] /= o;
        m_data[2] /= o;
        m_data[3] /= o;
        return *this;
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Negative Operator
    /// \return negative version of this vector.
    constexpr tvec4 operator-() const noexcept {
        return tvec4{ -x(), -y(), -z(), -w() };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Compare against another vector.
    /// \param  o       the other vector.
    /// \return true if this equals the other vector, false otherwise.
    constexpr bool operator==(const tvec4& o) const noexcept {
        return x() == o.x() && y() == o.y() && z() == o.z() && w() == o.w();
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Compare against another vector.
    /// \param  o       the other vector.
    /// \return true if this doesn't equal the other vector, false otherwise.
    constexpr bool operator!=(const tvec4& o) const noexcept {
        return !(*this == o);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Index operator.
    /// \param  i       the index.
    /// \return reference to the data found at index.
    constexpr DataType& operator[](const size_t& i) noexcept {
        return m_data[i];
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Const Index operator.
    /// \param  i       the index.
    /// \return reference to the data found at index.
    constexpr const DataType& operator[](const size_t& i) const noexcept {
        return m_data[i];
    }

    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the X component of this vector.
    /// \return reference to the X component.
    constexpr DataType& x() noexcept { return m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the const X component of this vector.
    /// \return const reference to the X component.
    constexpr const DataType& x() const noexcept { return m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the Y component of this vector.
    /// \return reference to the Y component.
    constexpr DataType& y() noexcept { return m_data[1]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the const Y component of this vector.
    /// \return const reference to the Y component.
    constexpr const DataType& y() const noexcept { return m_data[1]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the Z component of this vector.
    /// \return reference to the Z component.
    constexpr DataType& z() noexcept { return m_data[2]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the const Z component of this vector.
    /// \return const reference to the Z component.
    constexpr const DataType& z() const noexcept { return m_data[2]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the W component of this vector.
    /// \return reference to the W component.
    constexpr DataType& w() noexcept { return m_data[3]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get the const W component of this vector.
    /// \return const reference to the W component.
    constexpr const DataType& w() const noexcept { return m_data[3]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Get a pointer to the underlying data container.
    /// \return pointer to the data array.
    constexpr DataType* data() noexcept { return &m_data[0]; }
    /// \brief  Get a const pointer to the underlying data container.
    /// \return pointer to the data array.
    constexpr const DataType* data() const noexcept { return &m_data[0]; }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Normalize this vector.
    /// \return normalized version of this vector.
    tvec4 normalize() const noexcept { return normalize(*this); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Normalize the supplied vector.
    /// \param  v       the vector to normalize.
    /// \return normalize version of the supplied vector.
    static tvec4 normalize(const tvec4& v) noexcept {
        const auto length_of_v = std::sqrt(
            (v.x() * v.x()) + (v.y() * v.y()) + (v.z() * v.z()) +
            (v.w() * v.w()));
        return tvec4{ v.x() / length_of_v, v.y() / length_of_v,
                      v.z() / length_of_v, v.w() / length_of_v };
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the length of this vector.
    /// \return the length of this vector.
    DataType length() const noexcept { return length(*this); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the length of the input vector.
    /// \param  v       the vector to check the length of.
    /// \return the length of the supplied vector.
    static DataType length(const tvec4& v) noexcept {
        return std::sqrt(
            (v.x() * v.x()) + (v.y() * v.y()) + (v.z() * v.z()) +
            (v.w() * v.w()));
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Calculate the distance between the 2 supplied vectors.
    /// \param  a       the first vector.
    /// \param  b       the second vector.
    /// \return the length of a - b.
    static DataType distance(const tvec4& a, const tvec4& b) noexcept {
        return length(a - b);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the minimum values between this and the input vector.
    /// \param  o       the other vector.
    /// \return the minimum x,y,z,w values.
    tvec4 min(const tvec4& o) const noexcept { return min(*this, o); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the minimum values between the 2 supplied vectors.
    /// \param  a       the first vector.
    /// \param  b       the second vector.
    /// \return the minimum x,y,z,w values.
    static tvec4 min(const tvec4& a, const tvec4& b) noexcept {
        return tvec4(
            std::min(a.m_data[0], b.m_data[0]),
            std::min(a.m_data[1], b.m_data[1]),
            std::min(a.m_data[2], b.m_data[2]),
            std::min(a.m_data[3], b.m_data[3]));
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the maximum values between this and the input vector.
    /// \param  o       the other vector.
    /// \return the maximum x,y,z,w values.
    tvec4 max(const tvec4& o) const noexcept { return max(*this, o); }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Retrieve the maximum values between the 2 supplied vectors.
    /// \param  a       the first vector.
    /// \param  b       the second vector.
    /// \return the maximum x,y,z,w values.
    static tvec4 max(const tvec4& a, const tvec4& b) noexcept {
        return tvec4(
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
    tvec4 clamp(const tvec4& low, const tvec4& high) const noexcept {
        return clamp(*this, low, high);
    }
    //////////////////////////////////////////////////////////////////////
    /// \brief  Clamp the input vector between the 2 supplied ranges.
    /// \param  value   the value vector to clamp.
    /// \param  low     the lowest values vector.
    /// \param  high    the highest values vector.
    /// \return clamped x,y,z,w values between low and high.
    static tvec4
    clamp(const tvec4& value, const tvec4& low, const tvec4& high) noexcept {
        return tvec4(
            std::clamp(value.m_data[0], low.m_data[0], high.m_data[0]),
            std::clamp(value.m_data[1], low.m_data[1], high.m_data[1]),
            std::clamp(value.m_data[2], low.m_data[2], high.m_data[2]),
            std::clamp(value.m_data[3], low.m_data[3], high.m_data[3]));
    }

    private:
    DataType m_data[4] = { DataType(0), DataType(0), DataType(0),
                           DataType(0) }; ///< The underlying data container.
};
}; // namespace mini

#endif // MINIGFX_VEC_HPP