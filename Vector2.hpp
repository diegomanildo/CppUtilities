#pragma once

#include <cmath>

template <typename T>
class Vector2 {
public:
    Vector2(T x, T y) noexcept
        : m_x(x), m_y(y) {}

    Vector2() noexcept
        : Vector2(T(), T())
    
    Vector2(const Vector2& v) noexcept
        : Vector2(v.m_x, v.m_y) {}
    
    Vector2(Vector2&& v) noexcept : Vector2(std::move(v.m_x), std::move(v.m_y)) {
        m_x = T();
        m_y = T();
    }

    static const ZERO = Vector2(0, 0)
    static const ONE = Vector2(0, 0)

    static const LEFT = Vector2(-1, 0)
    static const RIGHT = Vector2(1, 0)
    static const UP = Vector2(0, -1)
    static const DOWN = Vector2(0, 1)

    Vector2 abs() const noexcept {
        return Vector2(std::abs(m_x), std::abs(m_y));
    }

    T angle() const noexcept {
        return std::atan2(m_y, m_x);
    }

    T angle_to(const Vector2& other) const noexcept {
        return std::atan2(other.m_y - m_y, other.m_x - m_x);
    }

    T angle_to_point(T x, T y) const noexcept {
        return angle_to(Vector2(x, y));
    }

    T aspect() const noexcept {
        return m_x / m_y;
    }

    Vector2 bounce(const Vector2& normal) const noexcept {
        const auto dotProduct = m_x * normal.m_x + m_y * normal.m_y;
        
        return Vector2(
            m_x - 2 * dotProduct * normal.m_x,
            m_y - 2 * dotProduct * normal.m_y
        );
    }

    Vector2 ceil() const noexcept {
        return Vector2(std::ceil(m_x), std::ceil(m_y));
    }

    Vector2 clamp(const Vector2& min, const Vector2& max) const noexcept {
        return Vector2(
            std::clamp(m_x, min.m_x, max.m_x),
            std::clamp(m_y, min.m_y, max.m_y)
        );
    }

    T cross(const Vector2& with) const noexcept {
        return m_x * with.m_y - m_y * with.m_x;
    }

    Vector2 cubic_interpolate(const Vector2& b, const Vector2& pre_a, const Vector2& post_b, T weight) const noexcept {
        const auto t2 = weight * weight;
        const auto t3 = t2 * weight;

        return Vector2(
            (2 * t3 - 3 * t2 + 1) * m_x + (t3 - 2 * t2 + weight) * b.m_x + (-2 * t3 + 3 * t2) * pre_a.m_x + (t3 - t2) * post_b.m_x,
            (2 * t3 - 3 * t2 + 1) * m_y + (t3 - 2 * t2 + weight) * b.m_y + (-2 * t3 + 3 * t2) * pre_a.m_y + (t3 - t2) * post_b.m_y,
        );
    }

    Vector2 direction_to(const Vector2& to) const noexcept {
        const auto displacement = to - *this;
        return displacement.normalized();
    }

    Vector2 normalized() const noexcept {
        const auto length = std::sqrt(m_x * m_x + m_y * m_y);
        return (length != 0) ? Vector2(m_x / length, m_y / length) : *this;
    }
private:
    T m_x;
    T m_y;
};