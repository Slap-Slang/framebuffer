#include "framebuffer.h"

void printFrameBuffer(const framebuffer::FrameBuffer &fb);

int main()
{
    // clear terminal before rendering
    std::cout << "\033[2J\033[H";

    framebuffer::FrameBuffer fb(31, 9);
    fb.fillBufferRandomGray();

    do {
        fb.setStrokeColour(0xffff0000);
        fb.drawHorizontalLine(2, 1, 27);

        fb.setStrokeColour(0xff00ff00);
        fb.drawVerticalLine(1, 2, 5);

        fb.setStrokeColour(0xff0000ff);
        fb.drawLine(3, 3, 27, 3);

        fb.setStrokeColour(0xffffff00);
        fb.drawLine(3, 4, 27, 6);

        fb.setStrokeColour(0xffffffff);
        fb.drawLine(0, 0, 30, 8);

        printFrameBuffer(fb);

    } while (true);

    return 0;
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