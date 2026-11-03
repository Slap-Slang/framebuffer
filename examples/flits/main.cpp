#include "anim4_flash.h"
#include "framebuffer.h"
#include <iostream>

using namespace framebuffer;

void printFrameBuffer(const FrameBuffer &fb);

const uint16_t FB_WIDTH = 31;
const uint16_t FB_HEIGHT = 17;

FrameBuffer fb(FB_WIDTH, FB_HEIGHT);

float x = 0;
Anim4Flash a4(&fb);

int main() {
  // clear terminal before rendering
  std::cout << "\033[2J\033[H";

  //// SETUP ////
  a4.init();

  //// LOOP ////
  do {
    //// UPDATE ////
    a4.update(x);
    x += 0.05;

    //// DRAW ////
    printFrameBuffer(fb);
    std::cout << "Press 'ctrl' + 'z' to stop program.\n";

  } while (true);

  return 0;
}

/////////////////////////////
void printFrameBuffer(const FrameBuffer &fb) {
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
