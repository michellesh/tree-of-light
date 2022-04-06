struct Ripple {
  Range WIDTH = {20, 100, 50};
  Range SPEED = {1, 8, 2};

  int16_t _width = WIDTH.DFLT;
  int16_t _speed = SPEED.DFLT;
  float _radius = -_width;

  Ripple width(int16_t width) {
    _width = width;
    return *this;
  }

  Ripple speed(int16_t speed) {
    _speed = speed;
    return *this;
  }

  Ripple show() {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      for (uint8_t p = 0; p < discs[d].numLEDs; p++) {
        int16_t dist = abs(_radius - discs[d].radius(p));
        if (dist < _width) {
          uint8_t fade = map(dist, 0, _width, 0, 255);
          discs[d].leds[p] = campfire[d];
          discs[d].leds[p].fadeLightBy(fade);
        } else {
          discs[d].leds[p] = CRGB::Black;
        }
      }
    }

    _radius += _speed;
    if (_radius >= MAX_RADIUS_DISC[0] + _width) {
      _radius = -_width;
    }

    FastLED.show();
    return *this;
  }
};
