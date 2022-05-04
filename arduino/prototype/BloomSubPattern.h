#define MAX_BLOOMS 2

class BloomSubPattern : public SubPattern {
 private:
  Bloom _blooms[MAX_BLOOMS];
  uint8_t _numBlooms;
  bool _reverse;

 public:
  BloomSubPattern(int16_t discOffset = 0, bool continuous = true,
                  uint8_t numBlooms = MAX_BLOOMS, bool reverse = false) {
    _numBlooms = numBlooms;
    _reverse = reverse;

    if (_numBlooms > 0) {
      _blooms[0] = Bloom();
      _blooms[0].setRipples(discOffset, continuous);
    }
    if (_numBlooms > 1) {
      _blooms[1] = Bloom(1, Bloom::OFFSET.MAX / 2 + Bloom::WIDTH.DFLT / 2);
      _blooms[1].setRipples(discOffset, continuous);
    }
  }

  void show() {
    for (uint8_t i = 0; i < _numBlooms; i++) {
      _blooms[i].show();
    }

    EVERY_N_MILLISECONDS(1000) {
      if (_reverse) {
        for (uint8_t i = 0; i < _numBlooms; i++) {
          _blooms[i].reverse();
        }
      }
    }
  }
};
