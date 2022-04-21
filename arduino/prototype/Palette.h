#define MAX_PALETTE_INDEX 245
#define CM_SOLID 0
#define CM_VERTICAL_GRADIENT 1
#define CM_RADIUS_GRADIENT 2
#define CM_ANGLE_GRADIENT 3
#define CM_PETAL_GRADIENT 4

struct Palette {
  CRGBPalette16 currentPalette = *(activePalettes[0]);
  CRGBPalette16 targetPalette = *(activePalettes[0]);
  uint8_t colorMode = CM_RADIUS_GRADIENT;
  uint8_t _secondsPerPalette = 10;

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

  CRGB getPixelColor(uint8_t p) {
    return ColorFromPalette(currentPalette, p);
  }

  CRGB getColor(uint8_t d) {
    uint8_t paletteIndex = map(d, 0, NUM_DISCS - 1, 0, MAX_PALETTE_INDEX);
    return ColorFromPalette(currentPalette, paletteIndex);
  }

  CRGB getColor(uint8_t d, uint8_t p, bool reversePalette = false) {
    uint8_t paletteIndex = 0;
    switch (colorMode) {
      case CM_VERTICAL_GRADIENT: {
        paletteIndex = map(d, 0, NUM_DISCS - 1, 0, MAX_PALETTE_INDEX);
        break;
      }
      case CM_RADIUS_GRADIENT: {
        paletteIndex = map(discs[d].radius(p), 0, discs[d].maxRadius, 0,
                           MAX_PALETTE_INDEX);
        break;
      }
      case CM_ANGLE_GRADIENT: {
        paletteIndex = map(discs[d].angle(p), 0, 360, 0, MAX_PALETTE_INDEX);
        break;
      }
      case CM_PETAL_GRADIENT: {
        if (discs[d].isInner(p)) {
          paletteIndex = map(discs[d].petalIndex(p), 0,
                             discs[d].numLEDsP1 + discs[d].numLEDsP2 - 1, 0,
                             MAX_PALETTE_INDEX / 2);
        } else {
          paletteIndex = map(discs[d].petalIndex(p), 0, discs[d].numLEDsP3 - 1,
                             MAX_PALETTE_INDEX, MAX_PALETTE_INDEX / 2);
        }
        break;
      }
      default:
        break;
    }
    if (reversePalette) {
      paletteIndex = MAX_PALETTE_INDEX - paletteIndex;
    }
    return ColorFromPalette(currentPalette, paletteIndex);
  }
};
