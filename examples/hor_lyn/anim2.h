#pragma once

#include "baseanimation.h"
#include "framebuffer.h"

class Anim2 : public framebuffer::BaseAnimation
{
private:
    framebuffer::FrameBuffer *fb;
    uint8_t row = 0;

public:
    Anim2(framebuffer::FrameBuffer *fb)
    {
        this->fb = fb;
        delayUpdate = 1;
    }

  void init() override {
    fb->setWrapX(false);
    fb->setWrapY(true);
  }

private:
  void run() override {
      fb->fillBuffer(0xffffffff);
      fb->setStrokeColour(0xffff0000);
      fb->drawLine(0, row, fb->getWidth(), row);
      row++;
  }
};