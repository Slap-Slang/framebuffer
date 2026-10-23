#include "bitmap_cvw.h"

Bitmap::Bitmap(uint8_t width, uint8_t height, const uint8_t* data, BitmapType type)
    : width(width)
    , height(height)
    , data(data)
    , type(type)
    , palette(nullptr)
{
}

Bitmap::Bitmap(uint8_t width, uint8_t height, const uint8_t* data, const uint8_t* palette)
    : width(width)
    , height(height)
    , data(data)
    , type(BitmapType::PALETTE)
    , palette(palette)
{
}
