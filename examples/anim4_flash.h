#pragma once

class Anim4Flash : public BaseAnimation {
private:
  uint8_t curBrightness = 0;
  uint8_t stepSize = 1;
  int8_t stepDir = 1;

public:
  Anim4Flash(FrameBuffer* fb) {
    this->fb = fb;
    delayUpdate = 5;
  }

  void init() override {
    fb->setWrapX(false);
    fb->setWrapY(false);
    fb->fillBuffer(0xff000000);

    curBrightness = 0;
  }

  void onBtnClick() {}

  void onBtnDblClick() {}

  void onBtnTrpClick() {}

private:
  void run() override {
    uint32_t col = 0xffffffff;

    for (uint8_t i = 0; i < fb->getHeight(); i++) {
      uint32_t newCol = (0xff << 24) | col & ((0xff / curBrightness - 1) << 16) | col & ((0xff / curBrightness - 1) << 8) | col & ((0xff / curBrightness - 1) << 0);
      fb->drawHorizontalLine(0, i, fb->getWidth(), newCol);
    }

    int nextBrightness = curBrightness + (stepSize * stepDir);

    if (nextBrightness > 100 || nextBrightness < 1) {
      stepDir *= -1;
    } else {
      curBrightness = nextBrightness;
    }
  }
};