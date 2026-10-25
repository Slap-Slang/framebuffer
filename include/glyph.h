#pragma once
#include <cstdint>

namespace framebuffer {

struct Glyph {
public:
    const uint8_t width;
    const uint8_t height;
    const uint8_t start;

    Glyph(uint8_t width, uint8_t height, uint8_t start)
        : width(width)
        , height(height)
        , start(start)
    {
    }
};
} // namespace framebuffer