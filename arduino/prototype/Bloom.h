#define FADE_LINEAR 0
#define FADE_LINEAR_SYM 1
#define FADE_LINEAR_REVERSE 2
#define FADE_SAWTOOTH 3  // with 1/3 up 2/3 down
#define FADE_EXP2_SYM 4
#define FADE_EXP3_SYM 5
#define FADE_EXP4_SYM 6
#define FADE_CUSTOM 7

#define MIN_FADE 10

struct XY {
  uint8_t x;
  uint8_t y;
};

// creates a "fade shape" based on 2 or 3 pivot points.
// assumes p1.x < p2.x < p3.x
uint8_t fadeShape(uint8_t x, XY p1, XY p2, XY p3) {
  // clang-format off
  return x < p1.x   ? map(x, 0, p1.x, 0, p1.y)
         : x < p2.x ? map(x, p1.x, p2.x, p1.y, p2.y)
         : x < p3.x ? map(x, p2.x, p3.x, p2.y, p3.y)
                    : map(x, p3.x, 255, p3.y, 0);
  // clang-format on
}

uint8_t fadeShape(uint8_t x, XY p1, XY p2 = {127, 255}) {
  return fadeShape(x, p1, p2, {255 - p1.x, p1.y});
}

uint8_t exp(uint8_t x, uint8_t p, int div) {
  return x < 127 ? pow(x, p) / div : pow(255 - x, p) / div;
}

uint8_t max(uint8_t val1, uint8_t val2) { return val1 < val2 ? val2 : val1; }

bool isBetween(int16_t value, int16_t min, int16_t max,
               bool inclusive = false) {
  return inclusive ? value >= min && value <= max : value > min && value < max;
}

uint8_t mapDistToBrightness(uint8_t x, uint8_t mode = FADE_CUSTOM) {
  switch (mode) {
    case FADE_CUSTOM:
      return fadeShape(x, {60, 20});
    case FADE_EXP4_SYM:
      return max(MIN_FADE, exp(x, 4, 1050000));
    case FADE_EXP3_SYM:
      return max(MIN_FADE, exp(x, 3, 8200));
    case FADE_EXP2_SYM:
      return max(MIN_FADE, exp(x, 2, 65));
    case FADE_SAWTOOTH:
      return attackDecayWave8(x);
    case FADE_LINEAR_SYM:
      return x < 127 ? x * 2 : 255 - (2 * (x - 128));
    case FADE_LINEAR_REVERSE:
      return 255 - x;
    case FADE_LINEAR:
      return x;
    default:  // no fade, square shape
      return 255;
  }
}

struct Ripple {
  uint8_t rippleIndex;
  uint8_t discIndex;
  int16_t radius;
  bool continuous;

  int16_t maxRadius() {
    return MAX_RADIUS_DISC[continuous ? discIndex : 0] + 5;
  }

  void updateDiscIndex(int8_t amount) {
    if (continuous) {
      discIndex = (discIndex + amount) % NUM_DISCS;
    }
  }

  void updateRadius(int16_t speed, int16_t width) {
    int16_t newRadius = radius + speed;
    radius = (newRadius + maxRadius() + width) % (maxRadius() + width);
    if (speed < 0 && newRadius < 0) {
      updateDiscIndex(-1 + NUM_DISCS);
    } else if (speed > 0 && newRadius >= maxRadius() + width) {
      updateDiscIndex(1);
    }
  }

  void show(int16_t width) {
    for (uint8_t p = 0; p < discs[discIndex].numLEDs; p++) {
      int16_t dist = radius - discs[discIndex].radius(p);
      if (dist > 0 && dist < width) {
        uint8_t brightness = mapDistToBrightness(map(dist, 0, width, 0, 255));
        discs[discIndex].leds[p] = palette.getColor(rippleIndex);
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
  Range SPEED = {1, 8, 3};
  Range OFFSET = {0, 255, 0};

  Ripple _ripples[NUM_DISCS];

  int16_t _width = WIDTH.DFLT;
  int16_t _speed = SPEED.DFLT;
  int16_t _offset = OFFSET.DFLT;

  Bloom init(int16_t discOffset = 0, bool continuous = true) {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      Ripple r = {d, d, d * discOffset + _offset, continuous};
      _ripples[d] = r;
    }
    return *this;
  }

  Bloom initContinuous() { return init(); }

  Bloom initStartSame() { return init(0, false); }

  Bloom initEndSame() { return init(-20, false); }

  Bloom initUpward() { return init(20, false); }

  Bloom initDownward() { return init(-40, false); }

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
