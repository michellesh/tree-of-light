struct Twinkle {
  Range SPEED = {1, 8, 4};
  Range DENSITY = {1, 8, 5};

  uint8_t _speed = SPEED.DFLT;
  uint8_t _density = DENSITY.DFLT;

  Twinkle speed(uint8_t speed) {
    _speed = speed;
    return *this;
  };

  Twinkle density(uint8_t density) {
    _density = density;
    return *this;
  };

  Twinkle show() {
    uint16_t PRNG16 = 11337;
    uint32_t clock32 = millis();

    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      for (uint8_t p = 0; p < discs[d].numLEDs; p++) {
        // Use pseudo random number generator to get values for the clock speed
        // adjustment and clock offset of this pixel
        PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384;  // next 'random' number
        uint16_t myclockoffset16 = PRNG16;  // use that number as clock offset
        PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384;  // next 'random' number
        // use that number as clock speed adjustment factor (in 8ths, from 8/8ths
        // to 23/8ths)
        uint8_t myspeedmultiplierQ5_3 =
            ((((PRNG16 & 0xFF) >> 4) + (PRNG16 & 0x0F)) & 0x0F) + 0x08;
        uint32_t myclock30 =
            (uint32_t)((clock32 * myspeedmultiplierQ5_3) >> 3) + myclockoffset16;
        uint8_t myunique8 = PRNG16 >> 8;  // get 'salt' value for this pixel

        // We now have the adjusted 'clock' for this pixel, now we call
        // the function that computes what color the pixel should be based
        // on the "brightness = f( time )" idea.
        discs[d].leds[p] = _getColor(d, p, myclock30, myunique8);
      }
    }

    FastLED.show();
    return *this;
  }

  CRGB _getColor(uint8_t d, uint8_t p, uint32_t ms, uint8_t salt) {
    uint16_t ticks = ms >> (8 - _speed);
    uint8_t fastcycle8 = ticks;
    uint16_t slowcycle16 = (ticks >> 8) + salt;
    slowcycle16 += sin8(slowcycle16);
    slowcycle16 = (slowcycle16 * 2053) + 1384;
    uint8_t slowcycle8 = (slowcycle16 & 0xFF) + (slowcycle16 >> 8);

    uint8_t bright =
        ((slowcycle8 & 0x0E) / 2) < _density ? attackDecayWave8(fastcycle8) : 0;
    uint8_t hue = slowcycle8 - salt;

    CRGB color = palette.getPixelColor(hue);
    return bright > 0 ? color.nscale8(bright) : CRGB::Black;
  }
};
