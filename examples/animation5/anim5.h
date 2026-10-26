#include "framebuffer.h"
#pragma once

#include "baseanimation.h"

class Anim5 : public framebuffer::BaseAnimation
{
private:
    framebuffer::FrameBuffer *fb;
    float zoom = 0;
    float xScaler = 0.1;
    float yScaler = 0.4;
    bool climbing = true;

public:
    Anim5(framebuffer::FrameBuffer *fb)
    {
        this->fb = fb;
        delayUpdate = 1;
    }

  void init() override {
    fb->setWrapX(false);
    fb->setWrapY(false);
  }

  void onBtnClick() override {}

  void onBtnDblClick() override {}

  void onBtnTrpClick() override{};

private:
  void run() override {
      zoom += climbing ? 0.1 : -0.1;
      if (zoom >= 1800.0) {
          climbing = false;
      } else if (zoom <= 0.0) {
          climbing = true;
      }

      for (int i = 0; i < fb->getWidth(); i++) {
          for (int j = 0; j < fb->getHeight(); j++) {
              float ci = (i - fb->getWidth() / 2) * xScaler;
              float cj = (j - fb->getHeight() / 2) * yScaler;
              float k = (ci * ci) + (cj * cj);
              fb->drawPixel(i, j, framebuffer::RGBtoHex(k * zoom - 80, 0, k * zoom + 255));
          }
      }
  }
};