#include "framebuffer.h"
#pragma once

#include "baseanimation.h"

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

  void onBtnClick() override {}

  void onBtnDblClick() override {}

  void onBtnTrpClick() override{};

private:
  void run() override {
      fb->fillBuffer(fb->getFillColour());
      // fb->setStrokeColour(0xffff0000);
      fb->drawLine(0, row, fb->getWidth(), row);
      row++;
  }
};