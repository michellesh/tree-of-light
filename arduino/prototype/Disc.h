struct Disc {
  uint8_t discIndex;
  uint8_t numLEDs; // total number of LEDs in this disc
  uint8_t numInner1; // number of LEDs in inner segments of inner petal
  uint8_t numInner2; // number of LEDs in outer segments of inner petal
  uint8_t numOuter; // number of LEDs in outer segments
  int offset;
  CRGB *pixels;
};
