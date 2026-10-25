#include "framebuffer.h"
#pragma once

namespace framebuffer {

class BaseAnimation {
protected:
  FrameBuffer* fb;
  uint64_t lastUpdate = 0;
  uint64_t delayUpdate = 20;

public:
  virtual ~BaseAnimation(){};

  inline void update(uint64_t currentTime) {
    if (currentTime - lastUpdate >= delayUpdate) {
      run();
      lastUpdate = currentTime;
    }
  }

  virtual void init() = 0;
  virtual void onBtnClick() = 0;
  virtual void onBtnDblClick() = 0;
  virtual void onBtnTrpClick() = 0;

protected:
  virtual void run() = 0;
};
} // namespace framebuffer