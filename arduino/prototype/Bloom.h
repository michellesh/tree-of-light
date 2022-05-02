int colorInc = 2;  // How many colors to increment each new ripple by

struct Ripple {
  uint8_t colorIndex;
  uint8_t discIndex;
  int16_t radius;
  bool continuous;

  int16_t maxRadius() {
    return MAX_RADIUS_DISC[continuous ? discIndex : 0] + 5;
  }

  void updateDiscIndex(int8_t amount) {
    if (continuous) {
      discIndex = (discIndex + amount + NUM_DISCS) % NUM_DISCS;
    }
  }

  void updateColorIndex() {
    colorIndex = (colorIndex + NUM_DISCS + (colorInc * 2)) % NUM_DISCS;
  }

  void updateRadius(int16_t speed, int16_t width) {
    int16_t newRadius = radius + speed;
    radius = (newRadius + maxRadius() + width) % (maxRadius() + width);
    if (speed < 0 && newRadius < 0) {
      updateDiscIndex(-1);
      updateColorIndex();
    } else if (speed > 0 && newRadius >= maxRadius() + width) {
      updateDiscIndex(1);
      updateColorIndex();
    }
  }

  void show(int16_t width) {
    for (uint8_t p = 0; p < discs[discIndex].numLEDs; p++) {
      int16_t dist = radius - discs[discIndex].radius(p);
      if (dist > 0 && dist < width) {
        uint8_t brightness = mapDistToBrightness(map(dist, 0, width, 0, 255));
        discs[discIndex].leds[p] = palette.getColor(colorIndex);
        discs[discIndex].leds[p].nscale8(brightness);
      } else if (isBetween(dist, -10, 0) ||
                 isBetween(dist, width, width + 10)) {
        // this just ensures that the pixels go back to black after the ripple
        // has passed by. The 10 will probably need to be adjusted to account
        // for different speeds
        discs[discIndex].leds[p] = CRGB::Black;
      }
    }
  }
};

struct Bloom {
  Range WIDTH = {20, 255, 100};
  Range SPEED = {1, 8, 2};
  Range OFFSET = {0, 255, 0};

  Ripple _ripples[NUM_DISCS];

  uint8_t _group = 0;
  int16_t _width = WIDTH.DFLT;
  int16_t _speed = SPEED.DFLT;
  int16_t _offset = OFFSET.DFLT;

  Bloom init(int16_t discOffset = 0, bool continuous = true) {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      uint8_t colorIndex = ((d * colorInc) + (_group * colorInc)) % NUM_DISCS;
      Ripple r = {colorIndex, d, d * discOffset + _offset, continuous};
      _ripples[d] = r;
    }
    return *this;
  }

  Bloom initContinuous() { return init(); }

  Bloom initStartSame() { return init(0, false); }

  Bloom initEndSame() { return init(-20, false); }

  Bloom initUpward() { return init(20, false); }

  Bloom initDownward() { return init(-40, false); }

  Bloom group(uint8_t group) {
    _group = group;
    return *this;
  }

  Bloom offset(int16_t offset) {
    _offset = offset;
    return *this;
  }

  Bloom reverse() {
    _speed = _speed * -1;
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
      _ripples[d].updateRadius(_speed, _width);
    }
    return *this;
  }
};
