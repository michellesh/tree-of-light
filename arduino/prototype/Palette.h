#define CM_VERTICAL_GRADIENT 0
#define CM_RADIUS_GRADIENT 1
#define CM_ANGLE_GRADIENT 2
#define CM_PETAL_GRADIENT 3

struct Palette {
  CRGBPalette16 currentPalette;
  CRGBPalette16 targetPalette;
  uint8_t colorMode = CM_ANGLE_GRADIENT;
  uint8_t _secondsPerPalette = 30;

  Palette setNextColorPalette() {
    const uint8_t numberOfPalettes =
        sizeof(activePalettes) / sizeof(activePalettes[0]);
    static uint8_t whichPalette = -1;
    whichPalette = addmod8(whichPalette, 1, numberOfPalettes);

    targetPalette = *(activePalettes[whichPalette]);

    return *this;
  }

  Palette cycle() {
    EVERY_N_SECONDS(_secondsPerPalette) { setNextColorPalette(); }

    EVERY_N_MILLISECONDS(10) {
      nblendPaletteTowardPalette(currentPalette, targetPalette, 12);
    }

    return *this;
  }

  CRGB getColor(uint8_t d, uint8_t p) {
    switch (colorMode) {
      case CM_VERTICAL_GRADIENT: {
        uint8_t index = map(d, 0, NUM_DISCS - 1, 0, 255);
        return ColorFromPalette(currentPalette, index);
      }
      case CM_RADIUS_GRADIENT: {
        uint8_t index = map(discs[d].radius(p), 0, discs[d].maxRadius, 0, 255);
        return ColorFromPalette(currentPalette, index);
      }
      case CM_ANGLE_GRADIENT: {
        uint8_t index = map(discs[d].angle(p), 0, 360, 0, 255);
        return ColorFromPalette(currentPalette, index);
      }
      case CM_PETAL_GRADIENT:
        return campfire[d];  // TODO
      default:
        return campfire[d];  // TODO
    }
  }
};
