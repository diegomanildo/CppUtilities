#pragma once

class Size {
public:
    constexpr Size() noexcept = default;
    constexpr Size(int width, int height) noexcept : m_width(width), m_height(height) {}
    constexpr Size(const Size&) noexcept = default;

private:
    int m_width;
    int m_height;
};