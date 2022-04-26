struct Spiral {
  Range WIDTH = {10, 90, 70};  // How many degrees along the circumference at
                               // the current angle to light up
  Range SPEED = {1, 10, 2};    // How many degrees to add to the current
                               // angle each time
  Range DISC_OFFSET = {20, 90, 30};  // How many degrees to increase angle per
                                     // disc higher = tighter spiral

  uint8_t _id = 0;
  int16_t _angle = 0;  // the current angle
  int16_t _width = WIDTH.DFLT;
  int16_t _speed = SPEED.DFLT;
  int16_t _discOffset = DISC_OFFSET.DFLT;
  uint8_t _minRadiusPercent = 0;
  uint8_t _maxRadiusPercent = 100;

  Spiral width(int16_t width) {
    _width = width;
    return *this;
  }

  Spiral speed(int16_t speed) {
    _speed = speed;
    return *this;
  }

  Spiral discOffset(int16_t discOffset) {
    _discOffset = discOffset;
    return *this;
  }

  Spiral reverse() {
    _speed = _speed * -1;
    return *this;
  }

  Spiral offset(int16_t offset) {
    _angle = (_angle + offset + 360) % 360;
    return *this;
  }

  Spiral id(uint8_t id) {
    _id = id;
    return *this;
  }

  Spiral radiusRangePercent(uint8_t min, uint8_t max) {
    _minRadiusPercent = min;
    _maxRadiusPercent = max;
    return *this;
  }

  Spiral show() {
    uint8_t minRadius, maxRadius;
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      minRadius = map(_minRadiusPercent, 0, 100, 0, MAX_RADIUS_DISC[d]);
      maxRadius = map(_maxRadiusPercent, 0, 100, 0, MAX_RADIUS_DISC[d]);
      for (uint8_t p = 0; p < discs[d].numLEDs; p++) {
        if (!isBetween(discs[d].radius(p), minRadius, maxRadius)) {
          continue;
        }

        int16_t angle = (_angle + d * _discOffset + 360) % 360;

        // Set the LED color if its in range of the current angle
        // If angle is near beginning (0 degrees), also check LEDs near
        // end. If angle is near end (360 degrees), also check LEDs near
        // beginning
        if (setLED(d, p, angle) ||
            (angle < _width && setLED(d, p, 360 + angle)) ||
            (angle > 360 - _width && setLED(d, p, angle - 360))) {
          continue;
        }
      }
    }

    // Increment the angle. After 360 degrees, start over at 0 degrees
    _angle = (_angle + _speed + 360) % 360;

    return *this;
  }

  // Sets the LED color if the LED's angle is close to the current
  // angle. Returns true if the LED was turned on
  bool setLED(uint8_t d, uint8_t p, int16_t angle) {
    int16_t dist = angle - discs[d].angle(p);
    if (dist > 0 && dist < _width) {
      uint8_t brightness = mapDistToBrightness(map(dist, 0, _width, 0, 255));
      if (_speed < 3 && brightness < 5) {
        brightness = 0;
      }
      discs[d].leds[p] = palette.getColor(_id * 2).nscale8(brightness);
      // discs[d].leds[p] = palette.getColor(d, p).nscale8(brightness);
      return true;
    }
    if (_speed >= 3 && isBetween(dist, -10, 0) ||
        isBetween(dist, _width, _width + 10)) {
      discs[d].leds[p] = CRGB::Black;
      return true;
    }
    return false;
  }
};
