int16_t angle = 0;
int16_t maxWidth = 40;
float percentRadius = 0.8;

void spin() {
  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    for (uint8_t p = 0; p < discs[d].numLEDs; p++) {
      if (discs[d].radius(p) < percentRadius * discs[d].maxRadius) {
        discs[d].leds[p] = CRGB::Black;
        continue;
      }

      int16_t ledAngle = discs[d].angle(p);
      int16_t dist = getDist(angle, ledAngle);
      bool isInRange = dist < maxWidth;
      if (!isInRange && angle < maxWidth) {
        dist = getDist(360 + angle, ledAngle);
        isInRange = dist < maxWidth;
      }
      if (!isInRange && angle > 360 - maxWidth) {
        dist = getDist(angle - 360, ledAngle);
        isInRange = dist < maxWidth;
      }
      if (isInRange) {
        uint8_t fade = map(dist, 0, maxWidth, 0, 255);
        discs[d].leds[p] = campfire[d];
        discs[d].leds[p].fadeLightBy(fade);
      } else {
        discs[d].leds[p] = CRGB::Black;
      }
    }
  }

  angle += 4;
  if (angle >= 360) {
    angle = 0;
  }
}

int16_t getDist(int16_t angle, int16_t ledAngle) {
  return abs(angle - ledAngle);
}
