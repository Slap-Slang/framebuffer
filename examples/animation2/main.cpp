#include "bitmap_cvw.h"
#include "font.h"
// #include "font_aaron_4thd_4x4.h"
// #include "font_mplus_qub_7x7.h"
// #include "font_windows_Dina_6x9.h"
#include "anim2.h"
#include "font_3x3.h"
#include "framebuffer.h"
#include <iostream>

using namespace framebuffer;

void printFrameBuffer(const FrameBuffer &fb);

const uint16_t FB_WIDTH = 36;
const uint16_t FB_HEIGHT = 9;

FrameBuffer fb(FB_WIDTH, FB_HEIGHT);
float zoom = 0;
float xScaler = 0.05;
float yScaler = 0.1;
bool climbing = true;

const uint8_t dataRGBMario[] = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 0,   0,   255, 0,   0,
    255, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   255, 0,   0,   255, 0,   0,   255, 0,   0,   255, 0,   0,
    255, 0,   0,   255, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   156, 95,  0,   255, 167, 78,  52,  51,  65,  255, 167, 78,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    156, 95,  0,   255, 167, 78,  255, 167, 78,  255, 167, 78,  255, 167, 78,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   156, 95,  0,   156, 95,  0,
    255, 167, 78,  52,  51,  65,  52,  51,  65,  0,   0,   0,   0,   0,   0,
    0,   0,   0,   255, 0,   0,   255, 0,   0,   68,  53,  255, 255, 0,   0,
    68,  53,  255, 255, 0,   0,   255, 0,   0,   0,   0,   0,   255, 167, 78,
    0,   0,   0,   68,  53,  255, 68,  53,  255, 68,  53,  255, 68,  53,  255,
    68,  53,  255, 0,   0,   0,   255, 167, 78,  255, 167, 78,  0,   0,   0,
    0,   0,   0,   68,  53,  255, 68,  53,  255, 68,  53,  255, 68,  53,  255,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   156, 95,  0,
    156, 95,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   156, 95,  0,
    156, 95,  0};
Bitmap bmRGBMario(9, 9, dataRGBMario, BitmapType::RGB);

const uint8_t dataARGBMario[] = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 255, 0,
    0,   255, 255, 0,   0,   255, 255, 0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255,
    255, 0,   0,   255, 255, 0,   0,   255, 255, 0,   0,   255, 255, 0,   0,
    255, 255, 0,   0,   255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 156, 95,  0,   255, 255,
    167, 78,  255, 52,  51,  65,  255, 255, 167, 78,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    255, 156, 95,  0,   255, 255, 167, 78,  255, 255, 167, 78,  255, 255, 167,
    78,  255, 255, 167, 78,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   255, 156, 95,  0,   255, 156, 95,  0,   255, 255, 167, 78,  255,
    52,  51,  65,  255, 52,  51,  65,  0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   255, 255, 0,   0,   255, 255, 0,   0,   255, 68,  53,
    255, 255, 255, 0,   0,   255, 68,  53,  255, 255, 255, 0,   0,   255, 255,
    0,   0,   0,   0,   0,   0,   255, 255, 167, 78,  0,   0,   0,   0,   255,
    68,  53,  255, 255, 68,  53,  255, 255, 68,  53,  255, 255, 68,  53,  255,
    255, 68,  53,  255, 0,   0,   0,   0,   255, 255, 167, 78,  255, 255, 167,
    78,  0,   0,   0,   0,   0,   0,   0,   0,   255, 68,  53,  255, 255, 68,
    53,  255, 255, 68,  53,  255, 255, 68,  53,  255, 0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   255, 156, 95,  0,
    255, 156, 95,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   255, 156, 95,  0,   255, 156, 95,  0};
Bitmap bmARGBMario(9, 9, dataARGBMario, BitmapType::ARGB);

const uint8_t dataGRAYMario[] = {
    0,   0,   0,   85,  85,  85,  0,   0,   0,   0,  0,   85,  85,  85,
    85,  85,  85,  0,   0,   0,   0,   84,  167, 56, 167, 0,   0,   0,
    0,   0,   84,  167, 167, 167, 167, 0,   0,   0,  84,  84,  167, 56,
    56,  0,   0,   0,   84,  84,  125, 84,  125, 84, 84,  0,   167, 0,
    125, 125, 125, 125, 125, 0,   167, 167, 0,   0,  125, 125, 125, 125,
    0,   0,   0,   0,   84,  84,  0,   0,   0,   84, 84};
Bitmap bmGRAYMario(9, 9, dataGRAYMario, BitmapType::MONO);

const uint8_t dataPALETTEMario[] = {
    0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
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

float x = 0;

framebuffer::Font font(FONT, GLYPHS, LOCHAR, HICHAR, AVHEIGHT);

Anim2 a2(&fb);

int main() {
  // clear terminal before rendering
  std::cout << "\033[2J\033[H";

  //// SETUP ////
  fb.setStrokeColour(0xff00ff00);
  fb.setFillColour(0x00ffffff);
  fb.fillBufferRandomGray();
  fb.setFont(&font);
  // fb.turnFill(FillState::OFF);

  a2.init();
  fb.setFillColour(0xffffffff);
  fb.setWrapX(true);

  //// LOOP ////
  do {
    //// UPDATE ////
    for (int i = 0; i < fb.getWidth() - 1; i++) {
      for (int j = 0; j < fb.getHeight(); j++) {
        float ci = (i - fb.getWidth() / 2 + 1) * xScaler;
        float cj = (j - fb.getHeight() / 2) * yScaler;
        float k = (ci * ci) + (cj * cj);
        // fb.drawPixel(i, j, RGBtoHex(k * zoom - 80, 0, k * zoom + 255));
      }
    }

    zoom += climbing ? 0.1 : -0.1;
    if (zoom >= 1800.0) {
      climbing = false;
      // bmPALETTEMario.changePalette(paletteMario2);
    } else if (zoom <= 0.0) {
      climbing = true;
      // bmPALETTEMario.changePalette(paletteMario1);
    }
    // paletteMario1[4] += 1;

    //// DRAW ////
    // fb.fillBuffer(0xffffffff);

    // fb.setStrokeColour(0x00ff00);
    // fb.setFillColour(0xff0000);
    // fb.fillBufferRandomGray();
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

    // if (x > fb.getWidth() + 7)
    //   x = -9;
    // fb.drawPaletteBitmap(x, 0, dataPALETTEMario, paletteMario1, 9, 9);
    // fb.fillBuffer(RGBtoHex(255, 255, 255, 100));

    // fb.drawText(0, 0, "Charl is hier");
    fb.setStrokeColour(0xff00ff00);
    fb.drawText(0, 0, "19:42:31");

    fb.setStrokeColour(0xffff00ff);
    a2.update(x);

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
