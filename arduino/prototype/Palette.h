#define MAX_PALETTE_INDEX 245

class Palette {
 private:
  CRGBPalette16 _currentPalette = *(activePalettes[0]);
  CRGBPalette16 _targetPalette = *(activePalettes[0]);
  uint8_t _activeColorMode = PATCHY;
  uint8_t _secondsPerPalette = 10;
  Timer _paletteCycleTimer = {_secondsPerPalette * 1000};

  void _setNextColorPalette() {
    const uint8_t numberOfPalettes =
        sizeof(activePalettes) / sizeof(activePalettes[0]);
    static uint8_t whichPalette = -1;
    whichPalette = addmod8(whichPalette, 1, numberOfPalettes);

    _targetPalette = *(activePalettes[whichPalette]);
  }

 public:
  static const uint8_t SOLID = 0;
  static const uint8_t VERTICAL_GRADIENT = 1;
  static const uint8_t RADIUS_GRADIENT = 2;
  static const uint8_t ANGLE_GRADIENT = 3;
  static const uint8_t PETAL_GRADIENT = 4;
  static const uint8_t PATCHY = 5;

  uint8_t getActiveColorMode() { return _activeColorMode; }

  void setColorMode(uint8_t colorMode) { _activeColorMode = colorMode; }

  uint8_t getNumPalettes() {
    return sizeof(activePalettes) / sizeof(activePalettes[0]);
  }

  void setPalette(uint8_t whichPalette) {
    _currentPalette = *(activePalettes[whichPalette]);
    _targetPalette = *(activePalettes[whichPalette]);
    _paletteCycleTimer.reset();
  }

  void cycle() {
    if (_paletteCycleTimer.complete()) {
      _setNextColorPalette();
      _paletteCycleTimer.reset();
    }

    EVERY_N_MILLISECONDS(10) {
      nblendPaletteTowardPalette(_currentPalette, _targetPalette, 12);
    }
  }

  CRGB getPixelColor(uint8_t p) { return ColorFromPalette(_currentPalette, p); }

  CRGB getColor(uint8_t d) {
    uint8_t paletteIndex = map(d, 0, NUM_DISCS - 1, 0, MAX_PALETTE_INDEX);
    return ColorFromPalette(_currentPalette, paletteIndex);
  }

  CRGB getColor(uint8_t d, uint8_t p, bool reversePalette = false) {
    uint8_t paletteIndex = 0;
    switch (_activeColorMode) {
      case VERTICAL_GRADIENT: {
        paletteIndex = map(d, 0, NUM_DISCS - 1, 0, MAX_PALETTE_INDEX);
        break;
      }
      case RADIUS_GRADIENT: {
        paletteIndex = map(discs[d].radius(p), 0, discs[d].maxRadius, 0,
                           MAX_PALETTE_INDEX);
        break;
      }
      case ANGLE_GRADIENT: {
        paletteIndex = map(discs[d].angle(p), 0, 360, 0, MAX_PALETTE_INDEX);
        break;
      }
      case PETAL_GRADIENT: {
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
      case PATCHY: {
        uint16_t maxRadius = sinwave(0, 250, 400);
        uint16_t maxAngle = sinwave(0, 360, 400);
        uint8_t r = abs(maxRadius - discs[d].radius(p));
        uint8_t g = abs(maxAngle - discs[d].angle(p)) % 255;
        uint8_t b = maxRadius / 2;
        paletteIndex = r + g + b;  // CRGB(r, g, b)
        break;
      }
      default:
        break;
    }
    if (reversePalette) {
      paletteIndex = MAX_PALETTE_INDEX - paletteIndex;
    }
    return ColorFromPalette(_currentPalette, paletteIndex);
  }
};
