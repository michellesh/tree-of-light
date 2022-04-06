struct Spin {
  Range WIDTH = {30, 90, 30};
  Range SPEED = {3, 12, 4};
  Range OFFSET = {20, 90, 30};

  int16_t _angle = 0;             // the current angle
  int16_t _width = WIDTH.DFLT;    // How many degrees along the circumference
                                  // at the current angle to light up
  int16_t _speed = SPEED.DFLT;    // How many degrees to increase the
                                  // current angle each tick
  int16_t _offset = OFFSET.DFLT;  // How much to increasse angle per disc

  Spin width(int16_t width) {
    _width = width;
    return *this;
  }

  Spin speed(int16_t speed) {
    _speed = speed;
    return *this;
  }

  Spin offset(int16_t offset) {
    _offset = offset;
    return *this;
  }

  Spin show() {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      for (uint8_t p = 0; p < discs[d].numLEDs; p++) {
        // Set the LED color if its in range of the current angle
        if (setLED(d, p)) {
          continue;
        }

        discs[d].leds[p] = CRGB::Black;
      }
    }

    // Increment the angle. After 360 degrees, start over at 0 degrees
    _angle = incWrap(_angle, 360, _speed);

    FastLED.show();
    return *this;
  }

  bool setLED(uint8_t d, uint8_t p) {
    int16_t angle = incWrap(_angle, d * _offset, 360);

    // If angle is near beginning (0 degrees), also check LEDs near
    // end. If angle is near end (360 degrees), also check LEDs near
    // beginning
    return _setLED(d, p, angle) ||
           (angle < _width && _setLED(d, p, 360 + angle)) ||
           (angle > 360 - _width && _setLED(d, p, angle - 360));
  }

  // Sets the LED color if the LED's angle is close to the current
  // angle. Returns true if the LED was turned on
  bool _setLED(uint8_t d, uint8_t p, int16_t angle) {
    int16_t dist = abs(angle - discs[d].angle(p));
    if (dist < _width) {
      discs[d].leds[p] = campfire[d];
      discs[d].leds[p].fadeLightBy(map(dist, 0, _width, 0, 255));
      return true;
    }
    return false;
  }
};
