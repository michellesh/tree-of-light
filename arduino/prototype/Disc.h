struct Disc {
  uint8_t discIndex;
  uint8_t numLEDs; // number of LEDs in this disc
  uint16_t offset; // number of LEDs in tree before this disc
  CRGB *leds; // the LEDs for this disc
  uint16_t maxRadius;

  int16_t radius(uint8_t pixelIndex) {
    return RADII[discIndex][pixelIndex % (numLEDs / NUM_PETAL_GROUPS)];
  }

  int16_t angle(uint8_t pixelIndex) {
    return ANGLES[discIndex][pixelIndex];
  }
};
