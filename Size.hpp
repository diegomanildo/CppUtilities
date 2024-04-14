#pragma once

class Size {
public:
    int width;
    int height;

    constexpr Size() noexcept = default;
    constexpr Size(int w, int h) noexcept : width(w), height(h) {}
    constexpr Size(const Size&) noexcept = default;
    constexpr Size(Size&&) noexcept = default;

    constexpr Size& operator=(const std::pair<int, int> pair) noexcept {
        width = pair.first;
        height = pair.second;
    }

    constexpr Size& operator=(const Size&) noexcept = default;
    constexpr Size& operator=(Size&&) noexcept = default;
};