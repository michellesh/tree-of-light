#define MAX_SPIRALS 3

class SpiralSubPattern : public SubPattern {
 private:
  Spiral _spirals[MAX_SPIRALS];
  uint8_t _numSpirals = MAX_SPIRALS;
  uint8_t _activeSubPattern = 0;
  uint8_t _percentBrightness = 0;  // percent brightness of the whole pattern

  void _showRubberBandWorm() {
    int16_t offset = sinwave(-90, 90, 100);
    int16_t width = sinwave(-180, 180, 100);
    int16_t speed = sinwave(3, 6);

    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      _spirals[0].setSpeed(speed);
      _spirals[0].setDiscOffset(d, d * offset);
      _spirals[0].setWidth(abs(width));
    }
    _spirals[0].show();
  }

  void _showRubberBandNoAnchor() {
    int16_t angle = sinwave(-200, 200, 200);
    int16_t offset = sinwave(-90, 90, 200);
    int16_t width = sinwave(-180, 180, 200);

    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      _spirals[0].setAngle(angle);
      _spirals[0].setDiscOffset(d, d * offset);
      _spirals[0].setWidth(abs(width));
    }
    _spirals[0].show();
  }

  void _showRubberBandAnchored() {
    int toMin = square(8, 0, 100);
    int toMax = square(0, 8, 100);

    // int16_t offset = sinwave(-360, 360, 100);
    // int16_t offset = sawtooth(-360, 360, 100); // swapping effect
    int16_t offset = cosSawtooth(-360, 360, 100);

    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      int16_t discOffset = mapf(d, toMin, toMax, 0, offset);
      _spirals[0].setDiscOffset(d, discOffset);
    }
    _spirals[0].show();
  }

  void _showGrowingSpirals() {
    unsigned long w = 100;  // waveLength
    unsigned long wo = 33;  // waveLengthOffset
    _spirals[0].setHeightRangePercent(sawtooth(-50, 150, w, wo),
                                      sawtooth(-50, 150, w));
    _spirals[0].show();

    _spirals[1].setHeightRangePercent(sawtooth(-50, 150, w, wo * 2),
                                      sawtooth(-50, 150, w, wo));
    _spirals[1].show();

    _spirals[2].setHeightRangePercent(sawtooth(-50, 150, w, w),
                                      sawtooth(-50, 150, w, wo * 2));
    _spirals[2].show();
  }

  void _showBasicSpiralRotation() {
    int16_t offset1 = sawtooth(0, 360, 200);
    int16_t offset2 = sawtooth(360, 0, 200);
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      _spirals[0].setDiscOffset(d, offset1 + (NUM_DISCS - 1 - d) * 30);
      _spirals[1].setDiscOffset(d, offset2 + d * 30);
    }
    _spirals[0].show();
    _spirals[1].show();
  }

  void _showContinuousSpiral() {
    unsigned long w = 400;         // waveLength
    unsigned long wo = w * 3 / 4;  // waveLengthOffset
    int16_t offset = sawtooth(0, 360, w);
    int16_t width = sinwave(30, 180, w / 2, wo);
    int16_t minRadiusPercent = sinwave(0, 90, w / 2, wo);
    int16_t maxRadiusPercent = sinwave(90, 100, w / 2, wo);
    int16_t speed = sinwave(0, 5, w / 2, wo);
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      _spirals[0].setDiscOffset(d, (1 + d) * offset);
      _spirals[0].setWidth(width);
      _spirals[0].setSpeed(speed);
      _spirals[0].setRadiusRangePercent(minRadiusPercent, maxRadiusPercent);
    }
    _spirals[0].show();
  }

 public:
  static const uint8_t RUBBER_BAND_WORM = 0;
  static const uint8_t RUBBER_BAND_NO_ANCHOR = 1;
  static const uint8_t RUBBER_BAND_ANCHORED = 2;
  static const uint8_t GROWING_SPIRALS = 3;
  static const uint8_t BASIC_SPIRAL_ROTATION = 4;
  static const uint8_t CONTINUOUS_SPIRAL = 5;

  SpiralSubPattern(uint8_t activeSubPattern = 0) {
    _activeSubPattern = activeSubPattern;
    switch (_activeSubPattern) {
      case RUBBER_BAND_WORM:
        _numSpirals = 1;
        _spirals[0] = Spiral();
        _spirals[0].setRadiusRangePercent(50, 100);
        break;
      case RUBBER_BAND_NO_ANCHOR:
        _numSpirals = 1;
        _spirals[0] = Spiral();
        _spirals[0].setRadiusRangePercent(50, 100);
        _spirals[0].setSpeed(0);
        break;
      case RUBBER_BAND_ANCHORED:
        _numSpirals = 1;
        _spirals[0] = Spiral();
        _spirals[0].setRadiusRangePercent(50, 100);
        _spirals[0].setAngle(0);
        _spirals[0].setSpeed(0);
        break;
      case GROWING_SPIRALS:
        _numSpirals = 3;
        for (uint8_t i = 0; i < _numSpirals; i++) {
          _spirals[i] = Spiral(i + 1);
          _spirals[i].setRadiusRangePercent(50, 100);
          _spirals[i].setSpeed(0);
          _spirals[i].setAngle(i * 120);
          for (uint8_t d = 0; d < NUM_DISCS; d++) {
            _spirals[i].setDiscOffset(d, d * 30);
          }
        }
        break;
      case BASIC_SPIRAL_ROTATION:
        _numSpirals = 2;
        _spirals[0] = Spiral(1);
        _spirals[1] = Spiral(2);
        _spirals[0].setRadiusRangePercent(50, 100);
        _spirals[0].setSpeed(0);
        _spirals[1].setRadiusRangePercent(50, 100);
        _spirals[1].setSpeed(0);
        break;
      case CONTINUOUS_SPIRAL:
        _numSpirals = 1;
        _spirals[0] = Spiral();
        _spirals[0].setRadiusRangePercent(50, 100);
        _spirals[0].setSpeed(3);
        break;
      default:
        break;
    }
  }

  virtual uint8_t getPercentBrightness() { return _percentBrightness; }

  virtual void setPercentBrightness(uint8_t percentBrightness) {
    _percentBrightness = percentBrightness;
    for (uint8_t i = 0; i < _numSpirals; i++) {
      _spirals[i].setPercentBrightness(percentBrightness);
    }
  }

  virtual void show() {
    switch (_activeSubPattern) {
      case RUBBER_BAND_WORM:
        _showRubberBandWorm();
        break;
      case RUBBER_BAND_NO_ANCHOR:
        _showRubberBandNoAnchor();
        break;
      case RUBBER_BAND_ANCHORED:
        _showRubberBandAnchored();
        break;
      case GROWING_SPIRALS:
        _showGrowingSpirals();
        break;
      case BASIC_SPIRAL_ROTATION:
        _showBasicSpiralRotation();
        break;
      case CONTINUOUS_SPIRAL:
        _showContinuousSpiral();
        break;
      default:
        break;
    }
  }
};
