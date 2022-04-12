struct Palette {
  CRGBPalette16 currentPalette;
  CRGBPalette16 targetPalette;
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

  CRGB getColor(uint8_t index, uint8_t brightness = 255) {
    return ColorFromPalette(currentPalette, index, brightness, NOBLEND);
  }
};
