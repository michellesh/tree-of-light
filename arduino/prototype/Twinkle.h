struct Twinkle {
  Range SPEED = {0, 8, 4};
  Range DENSITY = {0, 8, 5};

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

    for (uint16_t i = 0; i < NUM_LEDS_TOTAL; i++) {
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
      leds[i] = computeOneTwinkle(myclock30, myunique8);
    }

    FastLED.show();
    return *this;
  }

  CRGB computeOneTwinkle(uint32_t ms, uint8_t salt) {
    uint16_t ticks = ms >> (8 - _speed);
    uint8_t fastcycle8 = ticks;
    uint16_t slowcycle16 = (ticks >> 8) + salt;
    slowcycle16 += sin8(slowcycle16);
    slowcycle16 = (slowcycle16 * 2053) + 1384;
    uint8_t slowcycle8 = (slowcycle16 & 0xFF) + (slowcycle16 >> 8);

    uint8_t bright = 0;
    if (((slowcycle8 & 0x0E) / 2) < _density) {
      bright = attackDecayWave8(fastcycle8);
    }

    uint8_t hue = slowcycle8 - salt;
    CRGB c;
    if (bright > 0) {
      c = ColorFromPalette(gCurrentPalette, hue, bright, NOBLEND);
    } else {
      c = CRGB::Black;
    }
    return c;
  }
};
