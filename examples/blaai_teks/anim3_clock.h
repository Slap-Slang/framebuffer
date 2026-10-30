#pragma once

#include "baseanimation.h"
#include "framebuffer.h"

class Anim3Clock : public framebuffer::BaseAnimation
{
private:
  uint16_t x = 0;

public:
    Anim3Clock(framebuffer::FrameBuffer *fb)
    {
        this->fb = fb;
        delayUpdate = 1;
    }

  void init() override {
    fb->setWrapX(true);
    fb->setWrapY(false);
  }

  private:
  void run() override {
      fb->fillBuffer(0xff0000ff);
      fb->setStrokeColour(0xffff0000);
      fb->drawText(x, 0, "23:26");
      x++;
  }
};