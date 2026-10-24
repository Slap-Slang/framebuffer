#pragma once

#include "bitmap_cvw.h"
#include "font.h"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>

// Colour saved as ARGB

enum FillState {
  ON,
  OFF,
};

class FrameBuffer {
private:
  Font* font;

  uint32_t* pixels;

  uint32_t strokeColour = 0xffffffff;
  uint32_t fillColour = 0xffffffff;

  uint16_t width, height;

  uint8_t strokeWidth = 1;

  bool fill = true;
  bool wrapX = false;
  bool wrapY = false;

public:
  FrameBuffer(uint16_t width, uint16_t height);
  inline ~FrameBuffer() {
    delete[] pixels;
  };
  inline int16_t XYtoPixel(uint16_t x, uint16_t y) const {
    return y * width + x;
  };

  inline uint16_t getWidth() const {
    return width;
  };
  inline uint16_t getHeight() const {
    return height;
  };

  inline void setWrapX(bool val) {
    wrapX = val;
  };

  inline void setWrapY(bool val) {
    wrapY = val;
  };

  inline void setStrokeColour(uint32_t newStrokeColour) {
    strokeColour = newStrokeColour;
  };
  inline uint32_t getStrokeColour() const {
    return strokeColour;
  };
  inline void setStrokeWidth(uint8_t newStrokeWidth) {
    strokeWidth = newStrokeWidth;
  };
  inline uint8_t getStrokeWidth() const {
    return strokeWidth;
  };
  inline void setFillColour(uint32_t newFillColour) {
    fillColour = newFillColour;
  };
  inline uint32_t getFillColour() const {
    return fillColour;
  };
  inline void turnFill(FillState f = FillState::ON) {
    fill = f == FillState::ON ? true : f == FillState::OFF ? false
                                                           : false;
  };

  inline void setFont(Font* newFont) {
    font = newFont;
  };
  void drawPixel(uint16_t x, uint16_t y, uint32_t value);
  void drawPixel(uint16_t index, uint32_t value);
  inline uint32_t getPixel(uint16_t index) const {
    return pixels[index];
  }
  inline uint32_t getPixel(uint16_t x, uint16_t y) const {
    return pixels[XYtoPixel(x, y)];
  };

  //////////LINES/////////
  void drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
  void drawVerticalLine(int16_t x1, int16_t y1, int16_t length);
  void drawHorizontalLine(int16_t x1, int16_t y1, int16_t length);
  void drawHorizontalLine(int16_t x1, int16_t y1, int16_t length, uint32_t colour);
  //////////LINES/////////

  //////////SHAPES/////////
  void drawRectangle(int16_t x1, int16_t y1, int16_t width, int16_t height);
  //////////SHAPES/////////

  //////////BITMAPS/////////
  void drawBitmap(int16_t x, int16_t y, const Bitmap& bm);
  void drawMonoBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int width, int height);
  void drawGrayBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int width, int height);
  void drawRGBBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int width, int height);
  void drawPaletteBitmap(int16_t x, int16_t y, const uint8_t* bitmap, const uint8_t* palette, int width, int height);
  //////////BITMAPS/////////

  //////////TEXT/////////
  void drawChar(int16_t x, int16_t y, char c);
  void drawText(int16_t x, int16_t y, std::string s);
  //////////TEXT/////////

  //////////KAK/////////
  void fillBuffer(uint32_t colour);
  void fillBufferRandom();
  void fillBufferRandomGray();
  //////////KAK/////////
};

////////////////////////////////////////////////////////////////////////////////////

uint32_t RGBtoHex(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint32_t RGBtoHex(uint8_t r, uint8_t g, uint8_t b);
uint32_t GRAYtoHex(uint8_t gray);
