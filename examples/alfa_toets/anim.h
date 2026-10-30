#pragma once

#include "baseanimation.h"
#include "font.h"
// #include "font_aaron_4thd_4x4.h"
#include "font_mplus_qub_7x7.h"
#include "framebuffer.h"

class Anim : public framebuffer::BaseAnimation
{
private:
    const uint8_t dataPALETTEMario[81] = {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
                                          0, 0, 0, 0, 2, 3, 4, 3, 0, 0, 0, 0, 0, 2, 3, 3, 3,
                                          3, 0, 0, 0, 2, 2, 3, 4, 4, 0, 0, 0, 1, 1, 5, 1, 5,
                                          1, 1, 0, 3, 0, 5, 5, 5, 5, 5, 0, 3, 3, 0, 0, 5, 5,
                                          5, 5, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2};

    uint8_t paletteMario1[24] = {
        0,   // 0
        0,   // 0
        0,   // 0
        0,   // 0
        125, // 1
        255, // 1
        0,   // 1
        0,   // 1
        125, // 2
        156, // 2
        95,  // 2
        0,   // 2
        125, // 3
        255, // 3
        167, // 3
        78,  // 3
        125, // 4
        52,  // 4
        51,  // 4
        65,  // 4
        125, // 5
        68,  // 5
        53,  // 5
        255, // 5
    };

    framebuffer::Bitmap bm;

    framebuffer::Font f;

    uint8_t pos = 0;

public:
    Anim(framebuffer::FrameBuffer *fb)
    {
        this->fb = fb;
        delayUpdate = 1;

        bm = framebuffer::Bitmap(9, 9, dataPALETTEMario, paletteMario1);
        f = framebuffer::Font(FONT, GLYPHS, LOCHAR, HICHAR, AVHEIGHT);
    }

    void init() override
    {
        fb->setWrapX(true);
        fb->setFont(&f);
    }

private:
    void run() override
    {
        fb->fillBuffer(0xff000000);

        fb->setStrokeColour(0xff0000ff);
        fb->drawText(0, 2, "Charl Was Hier!");

        fb->drawBitmap(pos, 0, bm);
        pos++;
    }
};
