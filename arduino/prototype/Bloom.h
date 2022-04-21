struct Ripple {
  uint8_t discIndex;
  float radius;
  bool continuous;
  CRGB color;

  float maxRadius() { return MAX_RADIUS_DISC[continuous ? discIndex : 0]; }

  void incDiscIndex() {
    if (continuous) {
      discIndex = discIndex == 0 ? NUM_DISCS - 1 : discIndex - 1;
    }
  }

  void incRadius(int16_t speed, int16_t width) {
    radius += speed;
    if (radius >= maxRadius() + width) {
      radius = -width;
      incDiscIndex();
    }
  }

  void show(int16_t width) {
    for (uint8_t p = 0; p < discs[discIndex].numLEDs; p++) {
      int16_t dist = abs(radius - discs[discIndex].radius(p));
      if (dist < width) {
        uint8_t fade = map(dist, 0, width, 100, 255);
        if (fade > 245) {
          discs[discIndex].leds[p] = CRGB::Black;
        } else {
          discs[discIndex].leds[p] = color;
          discs[discIndex].leds[p].nscale8(255 - fade);
        }
      }
    }
  }
};

struct Bloom {
  Range WIDTH = {20, 100, 50};
  Range SPEED = {1, 8, 3};

  Ripple _ripples[NUM_DISCS];

  int16_t _width = WIDTH.DFLT;
  int16_t _speed = SPEED.DFLT;

  Bloom init(float offset = 0, bool continuous = true) {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      Ripple r = {d, -_width + (d * offset), continuous, campfire[d]};
      _ripples[d] = r;
    }
    return *this;
  }

  Bloom initContinuous() { return init(); }

  Bloom initStartSame() { return init(0, false); }

  Bloom initEndSame() { return init(-_width / 2, false); }

  Bloom initUpward() { return init(_width / 2, false); }

  Bloom initDownward() { return init(-_width, false); }

  Bloom width(int16_t width) {
    _width = width;
    return *this;
  }

  Bloom speed(int16_t speed) {
    _speed = speed;
    return *this;
  }

  Bloom show() {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      _ripples[d].show(_width);
      _ripples[d].incRadius(_speed, _width);
    }
    FastLED.show();
    return *this;
  }
};
