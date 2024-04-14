#pragma once

class Size {
public:
    constexpr Size() noexcept = default;
    constexpr Size(int width, int height) noexcept : m_width(width), m_height(height) {}
    constexpr Size(const Size&) noexcept = default;
    constexpr Size(Size&&) noexcept = default;

    constexpr Size& operator=(const std::pair<int, int> pair) noexcept {
        m_width = pair.first;
        m_height = pair.second;
    }

    constexpr Size& operator=(const Size&) noexcept = default;
    constexpr Size& operator=(Size&&) noexcept = default;

private:
    int m_width;
    int m_height;
};