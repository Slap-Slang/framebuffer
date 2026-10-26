#pragma once
#include "baseanimation.h"

class RotBal : public framebuffer::BaseAnimation
{
private:
  uint8_t x = 0;
  uint8_t xMod = 1;
  uint8_t y = 0;
  uint8_t yMod = 1;

public:
    RotBal(framebuffer::FrameBuffer *fb)
    {
        this->fb = fb;
        delayUpdate = 1;
    }

  void init() override {
    fb->setWrapX(true);
    fb->setWrapY(false);
  }

  void onBtnClick() override {
  }

  void onBtnDblClick() override {
  }

  void onBtnTrpClick() override {
    xMod *= -1;
  }


private:
  void run() override {
      fb->fillBuffer(0xffffffff);

      fb->drawPixel(x, y, 0xffff0000);

      x += xMod;

      y += yMod;
      if (y == fb->getHeight() - 1)
          yMod = -1;
      else if (y == 0)
          yMod = 1;
  }
};