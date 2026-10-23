#pragma once
#include "glyph.h"
#include <cstdint>

struct Font {
public:
    const uint8_t* fontData;
    const Glyph* glyphData;
    uint8_t LOCHAR, HICHAR, AVHEIGHT;

    Font() = default;

    Font(const uint8_t* fontData, const Glyph* glyphData, uint8_t LOCHAR, uint8_t HICHAR, uint8_t AVHEIGHT)
        : fontData(fontData)
        , glyphData(glyphData)
        , LOCHAR(LOCHAR)
        , HICHAR(HICHAR)
        , AVHEIGHT(AVHEIGHT)
    {
    }
};
