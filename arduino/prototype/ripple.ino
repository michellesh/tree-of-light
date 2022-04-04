int16_t maxRadius = 255;
int16_t maxRippleRadius = 50;
float rippleRadius = -maxRippleRadius;

void ripple() {
  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    for (uint8_t p = 0; p < discs[d].numLEDs; p++) {
      int16_t dist = abs(rippleRadius - discs[d].radius(p));
      if (dist < maxRippleRadius) {
        uint8_t fade = map(dist, 0, maxRippleRadius, 0, 255);
        discs[d].leds[p] = campfire[d];
        discs[d].leds[p].fadeLightBy(fade);
      } else {
        discs[d].leds[p] = CRGB::Black;
      }
    }
  }

  rippleRadius += 2;
  if (rippleRadius >= maxRadius + maxRippleRadius) {
    rippleRadius = -maxRippleRadius;
  }
}
