
#include "framebuffer.h"

FrameBuffer::FrameBuffer(uint16_t width, uint16_t height)
  : width(width), height(height) {
  uint16_t pixelCount = width * height;
  pixels = new uint32_t[pixelCount];
  for (uint16_t i = 0; i < pixelCount; i++) {
    pixels[i] = 0;
  }
}

void FrameBuffer::drawPixel(uint16_t x, uint16_t y, uint32_t value) {
  if (wrapX) {
    x = abs(x) % width;
  }
  if (wrapY) {
    y = abs(y) % height;
  }

  if (x < 0 || x >= width || y < 0 || y >= height)
    return;

  drawPixel(XYtoPixel(x, y), value);
}

void FrameBuffer::drawPixel(uint16_t index, uint32_t value) {

  uint8_t alpha = value >> 24 & 0xff;
  if (alpha == 255) {
    pixels[index] = value;
    return;
  } else if (alpha == 0)
    return;

  float red = value >> 16 & 0xff;
  float green = value >> 8 & 0xff;
  float blue = value & 0xff;

  uint32_t curColour = getPixel(index);
  uint8_t invAlpha = 255 - alpha;
  uint8_t newRed = ((curColour >> 16 & 0xff) * invAlpha + red * alpha) / 255;
  uint8_t newGreen = ((curColour >> 8 & 0xff) * invAlpha + green * alpha) / 255;
  uint8_t newBlue = ((curColour & 0xff) * invAlpha + blue * alpha) / 255;

  pixels[index] = RGBtoHex(newRed, newGreen, newBlue);
}

////////////////////////////////////////////////////////////////////////////////////
//////////LINES/////////
// plotLine(x0, y0, x1, y1)
// dx = abs(x1 - x0)
// sx = x0 < x1 ? 1 : -1
// dy = -abs(y1 - y0)
// sy = y0 < y1 ? 1 : -1
// error = dx + dy
//
// while true
//     plot(x0, y0)
//     e2 = 2 * error
//     if e2 >= dy
//         if x0 == x1 break
//             error = error + dy
//             x0 = x0 + sx
//             end if
//             if e2 <= dx
//                 if y0 == y1 break
//                     error = error + dx
//                     y0 = y0 + sy
//                     end if
//                     end while

void FrameBuffer::drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
  float slope;
  if (y1 == y2) {
    slope = 0;
  } else {
    slope = (x2 - x1) / (y2 - y1);
  }
  float c = y1 - (slope * x1);

  if (x2 < x1)
    std::swap(x1, x2);
  if (y2 < y1)
    std::swap(y1, y2);

  for (int16_t x = x1; x <= x2; x++) {
    float y = slope * x + c;
    drawPixel(x, y, strokeColour);
  }

  for (int16_t y = y1; y <= y2; y++) {
    float x = (y - c) / slope;
    drawPixel(x, y, strokeColour);
  }
}

void FrameBuffer::drawVerticalLine(int16_t x1, int16_t y1, int16_t length) {
  if (length < 0) {
    y1 += length + 1;
    length *= -1;
  }

  for (int16_t i = 0; i < length; i++) {
    // pixels[XYtoPixel(x1, i)] = strokeColour;
    drawPixel(x1, i + y1, strokeColour);
  }
}

void FrameBuffer::drawHorizontalLine(int16_t x1, int16_t y1, int16_t length) {
  // if (length < 0) {
  //   x1 += length + 1;
  //   length *= -1;
  // }

  // for (int16_t i = x1; i < length + x1; i++) {
  //   // pixels[XYtoPixel(i, y1)] = strokeColour;
  //   drawPixel(i, y1, strokeColour);
  // }

  drawHorizontalLine(x1, y1, length, strokeColour);
}

void FrameBuffer::drawHorizontalLine(int16_t x1, int16_t y1, int16_t length, uint32_t colour) {
  if (length < 0) {
    x1 += length + 1;
    length *= -1;
  }

  for (int16_t i = x1; i < length + x1; i++) {
    drawPixel(i, y1, colour);
  }
}


//////////LINES/////////

//////////SHAPES/////////
void FrameBuffer::drawRectangle(int16_t x1, int16_t y1, int16_t width, int16_t height) {
  int8_t horMod = width / abs(width);
  int8_t vertMod = height / abs(height);

  drawVerticalLine(x1, y1, height);
  drawVerticalLine(x1 + width - (1 * horMod), y1, height);
  drawHorizontalLine(x1 + (1 * horMod), y1, width - (2 * horMod));
  drawHorizontalLine(x1 + (1 * horMod), y1 + height - (1 * vertMod), width - (2 * horMod));

  if (!fill)
    return;

  int32_t colourSaver = strokeColour;
  strokeColour = fillColour;
  int16_t vertDist = abs(height - (2 * vertMod));

  for (int i = 0; i < vertDist; i++) {
    drawHorizontalLine(x1 + (1 * horMod), y1 + (i * vertMod) + (1 * vertMod), width - (2 * horMod));
  }

  strokeColour = colourSaver;
}
//////////SHAPES/////////

//////////BITMAPS/////////
void FrameBuffer::drawBitmap(int16_t x, int16_t y, const Bitmap& bm) {
  uint8_t bmWidth = bm.getWidth();
  uint8_t bmHeight = bm.getHeight();
  const uint8_t* data = bm.getData();
  BitmapType type = bm.getType();
  const uint8_t* palette = bm.getPalette();

  for (uint16_t ybm = 0; ybm < bmHeight; ybm++) {
    for (uint16_t xbm = 0; xbm < bmWidth; xbm++) {
      uint16_t index = ybm * bmWidth + xbm;
      uint32_t colour = 0;
      switch (type) {
        case RGB:
          index *= 3;
          colour = RGBtoHex(data[index], data[index + 1], data[index + 2]);
          break;
        case ARGB:
          index *= 4;
          colour = RGBtoHex(data[index + 1], data[index + 2], data[index + 3], data[index]);
          break;

        case MONO:
          if (data[index] > 0)
            colour = strokeColour;
          break;

        case GRAY:
          colour = GRAYtoHex(data[index]);
          break;

        case PALETTE:
          uint8_t pi = data[index] * 4;
          colour = RGBtoHex(palette[pi + 1], palette[pi + 2], palette[pi + 3], palette[pi]);
          break;
      }
      drawPixel(x + xbm, y + ybm, colour);
    }
  }
}

void FrameBuffer::drawMonoBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int bmWidth, int bmHeight) {
  Bitmap bm(bmWidth, bmHeight, bitmap, BitmapType::MONO);
  drawBitmap(x, y, bm);
}

void FrameBuffer::drawGrayBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int bmWidth, int bmHeight) {
  Bitmap bm(bmWidth, bmHeight, bitmap, BitmapType::GRAY);
  drawBitmap(x, y, bm);
}

void FrameBuffer::drawRGBBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int bmWidth, int bmHeight) {
  Bitmap bm(bmWidth, bmHeight, bitmap, BitmapType::RGB);
  drawBitmap(x, y, bm);
}

void FrameBuffer::drawPaletteBitmap(int16_t x, int16_t y, const uint8_t* bitmap, const uint8_t* palette, int bmWidth, int bmHeight) {
  Bitmap bm(bmWidth, bmHeight, bitmap, palette);
  drawBitmap(x, y, bm);
}

//////////BITMAPS/////////

//////////TEXT/////////
void FrameBuffer::drawChar(int16_t x, int16_t y, char c) {
  if (font != nullptr) {
    if (c < font->LOCHAR || c > font->HICHAR)
      return;

    uint16_t glyphIndex = c - font->LOCHAR;
    uint16_t charIndex = glyphIndex * font->AVHEIGHT;
    const Glyph* g = font->glyphData + glyphIndex;

    for (uint16_t row = 0; row < g->height; row++) {
      uint8_t rowData = font->fontData[charIndex + row];

      for (uint8_t col = 0; col < g->width; col++) {
        if ((rowData >> (col + g->start)) & 1) {
          drawPixel(x + col, y + row, strokeColour);
        }
      }
    }
  }
}

void FrameBuffer::drawText(int16_t x, int16_t y, std::string s) {
  if (font != nullptr) {
    const Glyph* g;
    uint16_t nextX = x;

    for (uint8_t i = 0; i < s.length(); i++) {
      g = font->glyphData + (s[i] - font->LOCHAR);
      drawChar(nextX, y, s[i]);
      nextX += g->width + 1;
    }
  }
}
//////////TEXT/////////

//////////KAK/////////
void FrameBuffer::fillBuffer(uint32_t colour) {
  for (uint16_t y = 0; y < height; y++) {
    for (uint16_t x = 0; x < width; x++) {
      drawPixel(x, y, colour);
    }
  }
}

void FrameBuffer::fillBufferRandom() {
  for (uint16_t y = 0; y < height; y++) {
    for (uint16_t x = 0; x < width; x++) {
      uint32_t colour = RGBtoHex(rand(), rand(), rand());
      drawPixel(x, y, colour);
    }
  }
}

void FrameBuffer::fillBufferRandomGray() {
  for (uint16_t y = 0; y < height; y++) {
    for (uint16_t x = 0; x < width; x++) {
      uint8_t shade = rand();
      drawPixel(x, y, RGBtoHex(shade, shade, shade));
    }
  }
}
//////////KAK/////////

////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
uint32_t RGBtoHex(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  uint32_t colour = ((a << 24) | (uint32_t)r << 16) | ((uint32_t)g << 8) | ((uint32_t)b << 0);
  return colour;
}

uint32_t RGBtoHex(uint8_t r, uint8_t g, uint8_t b) {
  return RGBtoHex(r, g, b, 255);
}

uint32_t GRAYtoHex(uint8_t gray) {
  uint32_t colour = RGBtoHex(gray, gray, gray);
  return colour;
}
