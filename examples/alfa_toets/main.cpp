#include "anim.h"
#include "framebuffer.h"
#include <iostream>

namespace fb = framebuffer;

void printFrameBuffer(const fb::FrameBuffer &fb);

const uint8_t FB_WIDTH = 37;
const uint8_t FB_HEIGHT = 9;

uint32_t pixels[FB_WIDTH * FB_HEIGHT];
fb::FrameBuffer fb1(FB_WIDTH, FB_HEIGHT, pixels);

Anim a(&fb1);
float count = 0;

int main()
{
    // clear terminal before rendering
    std::cout << "\033[2J\033[H";

    //// SETUP ////
    a.init();

    do {
        //// UPDATE ////
        if (a.update(count)) {
            fb1.setStrokeColour(0x1000ff00);
            fb1.drawHorizontalLine(4, 2, 29);
        }

        count += 0.001;

        //// DRAW ////
        printFrameBuffer(fb1);
        std::cout << "Press 'ctrl' + 'z' to stop program.\n";

    } while (true);
}

/////////////////////////////
void printFrameBuffer(const framebuffer::FrameBuffer &fb)
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