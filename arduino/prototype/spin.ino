int16_t angle = 0;
int16_t maxWidth = 40;
float percentRadius = 0.8;

void spin() {
  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    for (uint8_t p = 0; p < discs[d].numLEDs; p++) {
      // only light up LEDs close to the edge of the disc
      if (discs[d].radius(p) < percentRadius * discs[d].maxRadius) {
        discs[d].leds[p] = CRGB::Black;
        continue;
      }

      int16_t ledAngle = discs[d].angle(p);
      if (setLED(d, p, angle, ledAngle) ||
         (angle < maxWidth && setLED(d, p, 360 + angle, ledAngle)) ||
         (angle > 360 - maxWidth && setLED(d, p, angle - 360, ledAngle))) {
        continue;
      }

      discs[d].leds[p] = CRGB::Black;
    }
  }

  angle += 4;
  if (angle >= 360) {
    angle = 0;
  }
}

bool setLED(uint8_t d, uint8_t p, int16_t angle, int16_t ledAngle) {
  int16_t dist = getDist(angle, ledAngle);
  if (inRange(dist)) {
    setColor(d, p, dist);
    return true;
  }
  return false;
}

void setColor(uint8_t d, uint8_t p, int16_t dist) {
  discs[d].leds[p] = campfire[d];
  discs[d].leds[p].fadeLightBy(map(dist, 0, maxWidth, 0, 255));
}

bool inRange(int16_t dist) {
  return dist < maxWidth;
}

int16_t getDist(int16_t angle, int16_t ledAngle) {
  return abs(angle - ledAngle);
}
