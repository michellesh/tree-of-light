struct Spiral {
  Range WIDTH = {10, 90, 20};  // How many degrees along the circumference at
                               // the current angle to light up
  Range SPEED = {1, 10, 1};    // How many degrees to add to the current
                               // angle each time
  Range DISC_OFFSET = {20, 90, 30};  // How many degrees to increase angle per
                                     // disc higher = tighter spiral

  uint8_t _id = 0;
  int16_t _angle = 0;  // the current angle
  int16_t _width = WIDTH.DFLT;
  int16_t _speed = SPEED.DFLT;
  int16_t _discOffset = DISC_OFFSET.DFLT;

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

  Spiral show() {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      for (uint8_t p = 0; p < discs[d].numLEDs; p++) {
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
    int16_t dist = abs(angle - discs[d].angle(p));
    if (dist < _width) {
      discs[d].leds[p] = palette.getColor(_id);
      discs[d].leds[p].fadeLightBy(map(dist, 0, _width, 0, 255));
      return true;
    } else if (isBetween(dist, -10, 0) ||
               isBetween(dist, _width, _width + 10)) {
      discs[d].leds[p] = CRGB::Black;
      return true;
    }
    return false;
  }
};
