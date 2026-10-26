#include "bitmap_cvw.h"
#include "framebuffer.h"
#include <iostream>

using namespace framebuffer;

void printFrameBuffer(const FrameBuffer &fb);

const uint16_t FB_WIDTH = 36;
const uint16_t FB_HEIGHT = 9;

FrameBuffer fb(FB_WIDTH, FB_HEIGHT);

const uint8_t dataRGBMario[]
    = {0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 0,   0,   255, 0,   0,   255, 0,  0,
       0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 0,  0,
       255, 0,   0,   255, 0,   0,   255, 0,   0,   255, 0,   0,   255, 0,   0,   0,   0,  0,
       0,   0,   0,   0,   0,   0,   0,   0,   0,   156, 95,  0,   255, 167, 78,  52,  51, 65,
       255, 167, 78,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,
       156, 95,  0,   255, 167, 78,  255, 167, 78,  255, 167, 78,  255, 167, 78,  0,   0,  0,
       0,   0,   0,   0,   0,   0,   156, 95,  0,   156, 95,  0,   255, 167, 78,  52,  51, 65,
       52,  51,  65,  0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 0,   0,   255, 0,  0,
       68,  53,  255, 255, 0,   0,   68,  53,  255, 255, 0,   0,   255, 0,   0,   0,   0,  0,
       255, 167, 78,  0,   0,   0,   68,  53,  255, 68,  53,  255, 68,  53,  255, 68,  53, 255,
       68,  53,  255, 0,   0,   0,   255, 167, 78,  255, 167, 78,  0,   0,   0,   0,   0,  0,
       68,  53,  255, 68,  53,  255, 68,  53,  255, 68,  53,  255, 0,   0,   0,   0,   0,  0,
       0,   0,   0,   0,   0,   0,   156, 95,  0,   156, 95,  0,   0,   0,   0,   0,   0,  0,
       0,   0,   0,   156, 95,  0,   156, 95,  0};
Bitmap bmRGBMario(9, 9, dataRGBMario, BitmapType::RGB);

const uint8_t dataARGBMario[]
    = {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 0,   0,   255, 255,
       0,   0,   255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
       0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 0,   0,   255, 255, 0,   0,   255, 255,
       0,   0,   255, 255, 0,   0,   255, 255, 0,   0,   255, 255, 0,   0,   0,   0,   0,   0,
       0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 156, 95,  0,   255, 255,
       167, 78,  255, 52,  51,  65,  255, 255, 167, 78,  0,   0,   0,   0,   0,   0,   0,   0,
       0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 156, 95,  0,   255, 255,
       167, 78,  255, 255, 167, 78,  255, 255, 167, 78,  255, 255, 167, 78,  0,   0,   0,   0,
       0,   0,   0,   0,   0,   0,   0,   0,   255, 156, 95,  0,   255, 156, 95,  0,   255, 255,
       167, 78,  255, 52,  51,  65,  255, 52,  51,  65,  0,   0,   0,   0,   0,   0,   0,   0,
       0,   0,   0,   0,   255, 255, 0,   0,   255, 255, 0,   0,   255, 68,  53,  255, 255, 255,
       0,   0,   255, 68,  53,  255, 255, 255, 0,   0,   255, 255, 0,   0,   0,   0,   0,   0,
       255, 255, 167, 78,  0,   0,   0,   0,   255, 68,  53,  255, 255, 68,  53,  255, 255, 68,
       53,  255, 255, 68,  53,  255, 255, 68,  53,  255, 0,   0,   0,   0,   255, 255, 167, 78,
       255, 255, 167, 78,  0,   0,   0,   0,   0,   0,   0,   0,   255, 68,  53,  255, 255, 68,
       53,  255, 255, 68,  53,  255, 255, 68,  53,  255, 0,   0,   0,   0,   0,   0,   0,   0,
       0,   0,   0,   0,   0,   0,   0,   0,   255, 156, 95,  0,   255, 156, 95,  0,   0,   0,
       0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 156, 95,  0,   255, 156, 95,  0};
Bitmap bmARGBMario(9, 9, dataARGBMario, BitmapType::ARGB);

const uint8_t dataGRAYMario[] = {0,   0,  0,   85,  85,  85, 0,   0,   0,   0,   0,   85,
                                 85,  85, 85,  85,  85,  0,  0,   0,   0,   84,  167, 56,
                                 167, 0,  0,   0,   0,   0,  84,  167, 167, 167, 167, 0,
                                 0,   0,  84,  84,  167, 56, 56,  0,   0,   0,   84,  84,
                                 125, 84, 125, 84,  84,  0,  167, 0,   125, 125, 125, 125,
                                 125, 0,  167, 167, 0,   0,  125, 125, 125, 125, 0,   0,
                                 0,   0,  84,  84,  0,   0,  0,   84,  84};
Bitmap bmGRAYMario(9, 9, dataGRAYMario, BitmapType::MONO);

const uint8_t dataPALETTEMario[] = {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
                                    2, 3, 4, 3, 0, 0, 0, 0, 0, 2, 3, 3, 3, 3, 0, 0, 0, 2, 2, 3, 4,
                                    4, 0, 0, 0, 1, 1, 5, 1, 5, 1, 1, 0, 3, 0, 5, 5, 5, 5, 5, 0, 3,
                                    3, 0, 0, 5, 5, 5, 5, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2};

uint8_t paletteMario1[] = {
    0,   // 0
    0,   // 0
    0,   // 0
    0,   // 0
    255, // 1
    255, // 1
    0,   // 1
    0,   // 1
    255, // 2
    156, // 2
    95,  // 2
    0,   // 2
    255, // 3
    255, // 3
    167, // 3
    78,  // 3
    255, // 4
    52,  // 4
    51,  // 4
    65,  // 4
    255, // 5
    68,  // 5
    53,  // 5
    255, // 5
};
uint8_t paletteMario2[] = {
    0,   // 0
    0,   // 0
    0,   // 0
    0,   // 1
    255, // 1
    255, // 1
    99,  // 2
    160, // 2
    255, // 2
    0,   // 3
    177, // 3
    177, // 3
    203, // 4
    204, // 4
    190, // 4
    187, // 5
    202, // 5
    0,   // 5
};
Bitmap bmPALETTEMario(9, 9, dataPALETTEMario, paletteMario1);
uint8_t *marioPalettes[] = {paletteMario1, paletteMario2};
int i = 0;

float x = 0;

int main()
{
    // clear terminal before rendering
    std::cout << "\033[2J\033[H";

    //// SETUP ////
    fb.setStrokeColour(0xff00ff00);
    fb.setFillColour(0x00ffffff);
    fb.fillBufferRandomGray();
    fb.setWrapX(true);

    //// LOOP ////
    do {
        //// UPDATE ////

        //// DRAW ////
        // fb.fillBuffer(0xffa0a0a0);

        // fb.setStrokeColour(0x00ff00);
        // fb.setFillColour(0xff0000);
        fb.fillBufferRandomGray();
        // fb.fillBuffer(RGBtoHex(255, 255, 255, 100));
        // fb.drawRectangle(0, 0, 36, 9);
        // fb.setStrokeColour(0x0000ff);
        // fb.drawHorizontalLine(2, 4, 33);
        // fb.setStrokeColour(0xffff0000);
        // fb.drawVerticalLine(3, 4, 3);
        // fb.drawVerticalLine(5, 4, -3);
        // fb.setStrokeColour(0xff0000ff);
        // fb.drawHorizontalLine(5, 1, -4);
        // fb.drawHorizontalLine(3, 7, 4);
        // fb.setStrokeColour(0xff00ff00);
        // fb.drawRectangle(7, 1, 5, 6);
        // fb.drawRectangle(17, 2, -5, 6);
        // fb.drawRectangle(19, 6, 5, -6);
        // fb.drawRectangle(29, 7, -5, -6);
        // fb.drawBitmap(x, 0, bmPALETTEMario);
        x += 0.001;

        if (x > fb.getWidth()) {
            x = 0;
            i = (i + 1) % 2;
        }

        fb.drawPaletteBitmap(x, 0, dataPALETTEMario, i == 0 ? paletteMario1 : paletteMario2, 9, 9);
        fb.fillBuffer(RGBtoHex(255, 255, 255, 100));

        printFrameBuffer(fb);
        std::cout << "Press 'ctrl' + 'z' to stop program.\n";

    } while (true);

    return 0;
}

/////////////////////////////
void printFrameBuffer(const FrameBuffer &fb)
{
    std::cout << "\033[?25l"; // hide cursor
    std::cout << "\033[H";    // move cursor to top of terminal

    for (int y = 0; y < fb.getHeight(); y++) {
        for (int x = 0; x < fb.getWidth(); x++) {
            uint32_t pixel = fb.getPixel(x, y);
            uint32_t r = (pixel >> 16) & 0xff;
            uint32_t g = (pixel >> 8) & 0xff;
            uint32_t b = (pixel >> 0) & 0xff;
            std::cout << "\033[48;2;" << r << ";" << g << ";" << b << "m \033[0m";
            std::cout << "\033[48;2;" << r << ";" << g << ";" << b << "m \033[0m";
        }
        std::cout << '\n';
    }
    std::cout << "\033[?25h"; // show cursor at end
}