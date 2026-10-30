#include "framebuffer.h"
#pragma once

namespace framebuffer {

class BaseAnimation {
protected:
    FrameBuffer *fb;
    uint64_t lastUpdate = 0;
    uint64_t delayUpdate = 20;

public:
    BaseAnimation() = default;

    virtual ~BaseAnimation() {};

    inline bool update(uint64_t currentTime)
    {
        if (currentTime - lastUpdate >= delayUpdate) {
            run();
            lastUpdate = currentTime;
            return true;
        }
        return false;
    }

  virtual void init() = 0;

protected:
  virtual void run() = 0;
};
} // namespace framebuffer