struct Disc {
  uint8_t discIndex;
  uint8_t numLEDs;    // number of LEDs in this disc
  uint8_t numLEDsP1;  // number of LEDs in first segment of inner petal
  uint8_t numLEDsP2;  // number of LEDs in second segment of inner petal
  uint8_t numLEDsP3;  // number of LEDs in outer petal segment
  uint16_t maxRadius;
  CRGB *leds;           // the LEDs for this disc
  uint8_t *brightness;  // the brightness of the LEDs for this disc

  int16_t radius(uint8_t pixelIndex) {
    return RADII[discIndex][pixelIndex % (numLEDs / NUM_PETAL_GROUPS)];
  }

  int16_t angle(uint8_t pixelIndex) { return ANGLES[discIndex][pixelIndex]; }

  void setBrighter(uint8_t pixelIndex, CRGB color, uint8_t colorBrightness) {
    if (colorBrightness > brightness[pixelIndex]) {
      leds[pixelIndex] = color;
      brightness[pixelIndex] = colorBrightness;
    }
  }

  void setBlend(uint8_t pixelIndex, CRGB color, uint8_t colorBrightness) {
    if (brightness[pixelIndex] == 0) {
      leds[pixelIndex] = color;
      brightness[pixelIndex] = colorBrightness;
    } else {
      leds[pixelIndex] = getColorBetween(color, leds[pixelIndex]);
      brightness[pixelIndex] = (brightness[pixelIndex] + colorBrightness) / 2;
    }
  }

  uint8_t petalIndex(uint8_t pixelIndex) {
    uint8_t petalGroupIndex = pixelIndex % (numLEDs / NUM_PETAL_GROUPS);
    uint8_t segment = numLEDsP1 + numLEDsP2;
    if (petalGroupIndex < segment) {
      return petalGroupIndex;
    }
    segment += numLEDsP2;
    if (petalGroupIndex < segment) {
      return numLEDsP1 + (segment - petalGroupIndex - 1);
    } else if (petalGroupIndex < (segment + numLEDsP3)) {
      return petalGroupIndex - segment;
    }
    return (numLEDs / NUM_PETAL_GROUPS) - petalGroupIndex - 1;
  }

  bool isInner(uint8_t pixelIndex) {
    uint8_t petalGroupIndex = pixelIndex % (numLEDs / NUM_PETAL_GROUPS);
    return petalGroupIndex < (numLEDsP1 + 2 * numLEDsP2);
  }
};
