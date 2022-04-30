uint8_t PERCENT_HEIGHT_DISC[] = {100, 89, 78, 67, 56, 45, 34, 23, 12};

struct Spiral {
  Range WIDTH = {10, 90, 90};  // How many degrees along the circumference at
                               // the current angle to light up
  Range SPEED = {1, 10, 2};    // How many degrees to add to the current
                               // angle each time
  Range DISC_OFFSET = {20, 90, 30};  // How many degrees to increase angle per
                                     // disc higher = tighter spiral

  uint8_t _id = 0;
  int16_t _angle = 0;  // the current angle
  int16_t _width = WIDTH.DFLT;
  int16_t _speed = SPEED.DFLT;
  int16_t _discOffset[NUM_DISCS] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint8_t _minRadius[NUM_DISCS] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint8_t _maxRadius[NUM_DISCS] = {100, 100, 100, 100, 100, 100, 100, 100, 100};
  uint8_t _minHeightPercent = 0;
  uint8_t _maxHeightPercent = 100;

  Spiral width(int16_t width) {
    _width = abs(width);
    return *this;
  }

  Spiral speed(int16_t speed) {
    _speed = speed;
    return *this;
  }

  Spiral discOffset(uint8_t i, int16_t angle) {
    _discOffset[i] = angle;
    return *this;
  }

  Spiral reverse() {
    _speed = _speed * -1;
    return *this;
  }

  Spiral id(uint8_t id) {
    _id = id;
    return *this;
  }

  Spiral radiusRangePercent(uint8_t min, uint8_t max) {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      _minRadius[d] = map(min, 0, 100, 0, MAX_RADIUS_DISC[d]);
      _maxRadius[d] = map(max, 0, 100, 0, MAX_RADIUS_DISC[d]);
    }
    return *this;
  }

  Spiral heightRangePercent(uint8_t min, uint8_t max) {
    _minHeightPercent = min;
    _maxHeightPercent = max;
    return *this;
  }

  Spiral angle(int16_t angle) {
    _angle = angle;
    return *this;
  }

  uint8_t radiusRangeBrightness(uint8_t d) {
    uint8_t percentFade = 50;
    uint8_t height = PERCENT_HEIGHT_DISC[d];
    if (isBetween(height, _minHeightPercent, _minHeightPercent + percentFade,
                  true)) {
      return map(height, _minHeightPercent, _minHeightPercent + percentFade, 0,
                 255);
    } else if (isBetween(height, _maxHeightPercent - percentFade,
                         _maxHeightPercent, true)) {
      return map(height, _maxHeightPercent - percentFade, _maxHeightPercent,
                 255, 0);
    } else if (_minHeightPercent < _maxHeightPercent) {
      return isBetween(height, _minHeightPercent + percentFade,
                       _maxHeightPercent - percentFade, true)
                 ? 255
                 : 0;
    } else {
      return isBetween(height, _maxHeightPercent, _minHeightPercent, true)
                 ? 0
                 : 255;
    }
  }

  Spiral show() {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      for (uint8_t p = 0; p < discs[d].numLEDs; p++) {
        // Set the LED color if its in range of the current angle
        // If angle is near beginning (0 degrees), also check LEDs near
        // end. If angle is near end (360 degrees), also check LEDs near
        // beginning
        int16_t angle = (_angle + _discOffset[d] + 360) % 360;
        if (setLED(d, p, angle) ||
            (angle < _width && setLED(d, p, 360 + angle)) ||
            (angle > 360 - _width && setLED(d, p, angle - 360))) {
          continue;
        }
        // discs[d].leds[p] = CRGB::Black;
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
      uint8_t radiusFade = radiusRangeBrightness(d);
      brightness = min(brightness, radiusFade);
      if (!isBetween(discs[d].radius(p), _minRadius[d], _maxRadius[d]) ||
          (_speed < 3 && brightness < 5)) {
        brightness = 0;
      }
      discs[d].leds[p] = palette.getColor(_id * 2).nscale8(brightness);
      // discs[d].leds[p] = palette.getColor(d, p).nscale8(brightness);
      return true;
    }
    if (_speed >= 3 && isBetween(dist, -20, 0) ||
        isBetween(dist, _width, _width + 20)) {
      discs[d].leds[p] = CRGB::Black;
      return true;
    }
    return false;
  }
};
