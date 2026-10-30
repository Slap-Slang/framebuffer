#pragma once
#include <cstdint>

namespace framebuffer {

enum BitmapType : uint16_t {
    RGB,
    ARGB,
    MONO,
    GRAY,
    PALETTE,
};

class Bitmap {
private:
    const uint8_t* data;
    const uint8_t* palette;
    uint8_t width, height;
    BitmapType type;

public:
    Bitmap() = default;
    // RGB, MONO or GRAY
    Bitmap(uint8_t width, uint8_t height, const uint8_t* data, BitmapType type);
    // PALETTE
    Bitmap(uint8_t width, uint8_t height, const uint8_t* data, const uint8_t* palette);

    uint8_t getWidth() const { return width; };
    uint8_t getHeight() const { return height; };

    const uint8_t* getData() const { return data; };
    BitmapType getType() const { return type; }
    const uint8_t* getPalette() const { return palette; };
    void changePalette(const uint8_t* newPalette) { palette = newPalette; };
};
} // namespace framebuffer