#pragma once
#include "glyph.h"
#include <cstdint>

namespace framebuffer {

struct Font
{
public:
    const uint8_t *fontData = nullptr;
    const Glyph *glyphData = nullptr;
    uint8_t LOCHAR, HICHAR, AVHEIGHT;

    Font() = default;
    Font(const Font &f) = delete;
    Font operator=(const Font &f) = delete;

    Font(const uint8_t* fontData, const Glyph* glyphData, uint8_t LOCHAR, uint8_t HICHAR, uint8_t AVHEIGHT)
        : fontData(fontData)
        , glyphData(glyphData)
        , LOCHAR(LOCHAR)
        , HICHAR(HICHAR)
        , AVHEIGHT(AVHEIGHT)
    {
    }

    void set(const uint8_t *fontData,
             const Glyph *glyphData,
             uint8_t LOCHAR,
             uint8_t HICHAR,
             uint8_t AVHEIGHT)
    {
        this->fontData = fontData;
        this->glyphData = glyphData;
        this->LOCHAR = LOCHAR;
        this->HICHAR = HICHAR;
        this->AVHEIGHT = AVHEIGHT;
    }
};
} // namespace framebuffer
