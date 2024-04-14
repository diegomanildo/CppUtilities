#pragma once

#include <cmath>
#include <algorithm>

template <typename T>
class Vector2 {
public:
    T x, y;

    constexpr Vector2(T _x, T _y) noexcept : x(_x), y(_y) {}
    constexpr Vector2() noexcept : Vector2(T(), T()) {}
    constexpr Vector2(const Vector2& v) = default;
    constexpr Vector2(Vector2&& v) noexcept = default;

    constexpr Vector2& operator=(const std::pair<T, T>& values) noexcept {
        x = values.first;
        y = values.second;
        return *this;
    }

    constexpr Vector2& operator=(const Vector2& v) noexcept = default;

    constexpr Vector2& operator=(Vector2&& v) noexcept = default;

    static constexpr Vector2<int> ZERO = Vector2{0, 0};
    static constexpr Vector2<int> ONE = Vector2{0, 0};

    static constexpr Vector2<int> LEFT = Vector2{-1, 0};
    static constexpr Vector2<int> RIGHT = Vector2{1, 0};
    static constexpr Vector2<int> UP = Vector2{0, -1};
    static constexpr Vector2<int> DOWN = Vector2{0, 1};

    friend std::ostream& operator<<(std::ostream& os, const Vector2& v) noexcept {
        return os << "(" << v.x << ", " << v.y << ")";
    }

    constexpr Vector2 abs() const noexcept {
        return Vector2(std::abs(x), std::abs(y));
    }

    constexpr T angle() const noexcept {
        return std::atan2(y, x);
    }

    constexpr T angle_to(const Vector2& other) const noexcept {
        return std::atan2(other.y - y, other.x - x);
    }

    constexpr T angle_to_point(T x, T y) const noexcept {
        return angle_to(Vector2(x, y));
    }

    constexpr T aspect() const noexcept {
        return x / y;
    }

    constexpr Vector2 bounce(const Vector2& normal) const noexcept {
        const auto dotProduct = x * normal.x + y * normal.y;
        
        return Vector2(
            x - 2 * dotProduct * normal.x,
            y - 2 * dotProduct * normal.y
        );
    }

    constexpr Vector2 ceil() const noexcept {
        return Vector2(std::ceil(x), std::ceil(y));
    }

    constexpr Vector2 clamp(const Vector2& min, const Vector2& max) const noexcept {
        return Vector2(
            std::clamp(x, min.x, max.x),
            std::clamp(y, min.y, max.y)
        );
    }

    constexpr T cross(const Vector2& with) const noexcept {
        return x * with.y - y * with.x;
    }

    constexpr Vector2 cubic_interpolate(const Vector2& b, const Vector2& pre_a, const Vector2& post_b, T weight) const noexcept {
        const auto t2 = weight * weight;
        const auto t3 = t2 * weight;

        return Vector2(
            ((2 * t3 - 3 * t2 + 1) * x + (t3 - 2 * t2 + weight) * b.x + (-2 * t3 + 3 * t2) * pre_a.x + (t3 - t2) * post_b.x),
            ((2 * t3 - 3 * t2 + 1) * y + (t3 - 2 * t2 + weight) * b.y + (-2 * t3 + 3 * t2) * pre_a.y + (t3 - t2) * post_b.y)
        );
    }

    constexpr Vector2 direction_to(const Vector2& to) const noexcept {
        const auto displacement = to - *this;
        return displacement.normalized();
    }

    constexpr T distance_squared_to(const Vector2& to) const noexcept {
        const auto dx = to.x - x;
        const auto dy = to.y - y;
        return dx * dx + dy * dy;
    }

    constexpr T distance_to(const Vector2& to) const noexcept {
        const auto dx = to.x - x;
        const auto dy = to.y - y;
        return std::sqrt(dx * dx + dy * dy);
    }

    constexpr T dot(const Vector2& with) const noexcept {
        return x * with.x + y * with.y;
    }

    constexpr Vector2 floor() const noexcept {
        return Vector2(std::floor(x), std::floor(y));
    }

    constexpr static Vector2 from_angle(float angle) noexcept {
        return Vector2(std::cos(angle), std::sin(angle));
    }

    constexpr bool is_equal_approx(const Vector2& to, float tolerance = 1.5f) const noexcept {
        return std::abs(x - to.x) < tolerance && std::abs(y - to.y) < tolerance;
    }

    bool is_finite() const noexcept {
        return std::isfinite(x) && std::isfinite(y);
    }

    constexpr bool is_normalized(float tolerance = 1.5f) const noexcept {
        const auto lengthSquared = x * x + y * y;
        return std::abs(lengthSquared - 1.0f) < tolerance;
    }

    constexpr Vector2 normalized() const noexcept {
        const auto length = std::sqrt(x * x + y * y);
        return (length != 0) ? Vector2(x / length, y / length) : *this;
    }

    constexpr T length() const noexcept {
        return std::sqrt(x * x + y * y);
    }

    constexpr T length_squared() const noexcept {
        return x * x + y * y;
    }

    constexpr Vector2 lerp(const Vector2& to, T weight) const noexcept {
        return (*this) * (T(1) - weight) + to * weight;
    }

    constexpr Vector2 operator+(const Vector2& other) noexcept {
        return Vector2(x + other.x, y + other.y);
    }

    constexpr Vector2 operator-(const Vector2& other) noexcept {
        return Vector2(x - other.x, y - other.y);
    }

    constexpr Vector2 operator*(T scalar) const noexcept {
        return Vector2(x * scalar, y * scalar);
    }

    constexpr Vector2 operator/(T scalar) const noexcept {
        return scalar != 0 ? Vector2(x / scalar, y / scalar) : Vector2(T(), T());
    }

    constexpr Vector2& operator+=(const Vector2& other) noexcept {
        *this = *this + other;
        return *this;
    }

    constexpr Vector2& operator-=(const Vector2& other) noexcept {
        *this = *this - other;
        return *this;
    }

    constexpr Vector2& operator*=(T scalar) noexcept {
        *this = *this * scalar;
        return *this;
    }

    constexpr Vector2& operator/=(T scalar) noexcept {
        *this = *this * scalar;
        return *this;
    }
};

using Vector2F = Vector2<float>;
using Vector2D = Vector2<double>;

using Vector2I = Vector2<int>;
using Vector2L = Vector2<long long>;
using Vector2UI = Vector2<unsigned int>;
using Vector2UL = Vector2<unsigned long long>;