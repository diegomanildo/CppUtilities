#pragma once

#include <cmath>
#include <algorithm>

template <typename T>
class Vector2 {
public:
    constexpr Vector2(T x, T y) noexcept : m_x(x), m_y(y) {}
    constexpr Vector2() noexcept : Vector2(T(), T()) {}
    constexpr Vector2(const Vector2& v) = default;
    constexpr Vector2(Vector2&& v) noexcept = default;

    constexpr Vector2& operator=(const std::pair<T, T>& values) noexcept {
        m_x = values.first;
        m_y = values.second;
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
        return os << "(" << v.m_x << ", " << v.m_y << ")";
    }

    constexpr Vector2 abs() const noexcept {
        return Vector2(std::abs(m_x), std::abs(m_y));
    }

    constexpr T angle() const noexcept {
        return std::atan2(m_y, m_x);
    }

    constexpr T angle_to(const Vector2& other) const noexcept {
        return std::atan2(other.m_y - m_y, other.m_x - m_x);
    }

    constexpr T angle_to_point(T x, T y) const noexcept {
        return angle_to(Vector2(x, y));
    }

    constexpr T aspect() const noexcept {
        return m_x / m_y;
    }

    constexpr Vector2 bounce(const Vector2& normal) const noexcept {
        const auto dotProduct = m_x * normal.m_x + m_y * normal.m_y;
        
        return Vector2(
            m_x - 2 * dotProduct * normal.m_x,
            m_y - 2 * dotProduct * normal.m_y
        );
    }

    constexpr Vector2 ceil() const noexcept {
        return Vector2(std::ceil(m_x), std::ceil(m_y));
    }

    constexpr Vector2 clamp(const Vector2& min, const Vector2& max) const noexcept {
        return Vector2(
            std::clamp(m_x, min.m_x, max.m_x),
            std::clamp(m_y, min.m_y, max.m_y)
        );
    }

    constexpr T cross(const Vector2& with) const noexcept {
        return m_x * with.m_y - m_y * with.m_x;
    }

    constexpr Vector2 cubic_interpolate(const Vector2& b, const Vector2& pre_a, const Vector2& post_b, T weight) const noexcept {
        const auto t2 = weight * weight;
        const auto t3 = t2 * weight;

        return Vector2(
            ((2 * t3 - 3 * t2 + 1) * m_x + (t3 - 2 * t2 + weight) * b.m_x + (-2 * t3 + 3 * t2) * pre_a.m_x + (t3 - t2) * post_b.m_x),
            ((2 * t3 - 3 * t2 + 1) * m_y + (t3 - 2 * t2 + weight) * b.m_y + (-2 * t3 + 3 * t2) * pre_a.m_y + (t3 - t2) * post_b.m_y)
        );
    }

    constexpr Vector2 direction_to(const Vector2& to) const noexcept {
        const auto displacement = to - *this;
        return displacement.normalized();
    }

    constexpr T distance_squared_to(const Vector2& to) const noexcept {
        const auto dx = to.m_x - m_x;
        const auto dy = to.m_y - m_y;
        return dx * dx + dy * dy;
    }

    constexpr T distance_to(const Vector2& to) const noexcept {
        const auto dx = to.m_x - m_x;
        const auto dy = to.m_y - m_y;
        return std::sqrt(dx * dx + dy * dy);
    }

    constexpr T dot(const Vector2& with) const noexcept {
        return m_x * with.m_x + m_y * with.m_y;
    }

    constexpr Vector2 floor() const noexcept {
        return Vector2(std::floor(m_x), std::floor(m_y));
    }

    constexpr static Vector2 from_angle(float angle) noexcept {
        return Vector2(std::cos(angle), std::sin(angle));
    }

    bool is_equal_approx(const Vector2& to, float tolerance = 1.5f) const noexcept {
        return std::abs(m_x - to.m_x) < tolerance && std::abs(m_y - to.m_y) < tolerance;
    }


    constexpr Vector2 normalized() const noexcept {
        const auto length = std::sqrt(m_x * m_x + m_y * m_y);
        return (length != 0) ? Vector2(m_x / length, m_y / length) : *this;
    }
private:
    T m_x;
    T m_y;
};

using Vector2F = Vector2<float>;
using Vector2D = Vector2<double>;

using Vector2I = Vector2<int>;
using Vector2L = Vector2<long long>;
using Vector2UI = Vector2<unsigned int>;
using Vector2UL = Vector2<unsigned long long>;