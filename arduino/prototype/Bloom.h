struct Ripple {
  uint8_t discIndex;
  float radius;
  CRGB color;

  void incRadius(int16_t speed, int16_t width) {
    radius += speed;
    if (radius >= MAX_RADIUS_DISC[discIndex] + width) {
      radius = -width;
      discIndex = discIndex == 0 ? NUM_DISCS - 1 : discIndex - 1;
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

  Bloom init() {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      Ripple r = {d, -_width, campfire[d]};
      _ripples[d] = r;
    }
    return *this;
  }

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
