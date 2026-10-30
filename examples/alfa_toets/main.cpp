#include "anim.h"
#include "framebuffer.h"

void printFrameBuffer(const framebuffer::FrameBuffer &fb);

const uint8_t WIDTH = 37;
const uint8_t HEIGHT = 9;
framebuffer::FrameBuffer fb(WIDTH, HEIGHT);

Anim a(&fb);
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
            fb.setStrokeColour(0x1000ff00);
            fb.drawHorizontalLine(4, 2, 29);
        }

        count += 0.001;

        //// DRAW ////
        printFrameBuffer(fb);
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