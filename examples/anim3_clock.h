#pragma once

class Anim3Clock : public BaseAnimation {
private:
  uint16_t x = 0;

public:
  Anim3Clock(FrameBuffer* fb) {
    this->fb = fb;
    delayUpdate = 100;
  }

  void init() override {
    fb->setWrapX(true);
    fb->setWrapY(false);
  }

  void onBtnClick() {}

  void onBtnDblClick() {}

  void onBtnTrpClick() {}

private:
  void run() override {
    fb->fillBuffer(fb->getFillColour());
    fb->drawText(x, 0, "23:26");
    x++;
  }
};