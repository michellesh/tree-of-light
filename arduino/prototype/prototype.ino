#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>

#include "globals.h"
#include "colors.h"
#include "utils.h"
#include "fade.h"
#include "Disc.h"

Disc discs[NUM_DISCS];
CRGB *leds;
uint8_t *ledBrightness;

#include "Palette.h"
Palette palette;

#include "Range.h"
#include "Pattern.h"
#include "Bloom.h"
#include "Spiral.h"
#include "Twinkle.h"

#include "SubPattern.h"
#include "BloomSubPattern.h"

Spiral spiral, spiral2, spiral3;
Twinkle twinkle;

BloomSubPattern bloomContinuous(0, true, 1, false);
BloomSubPattern bloomStartSame(0, false, 2, false);
BloomSubPattern bloomEndSame(-20, false, 2, false);
BloomSubPattern bloomUpward(20, false, 2, true);
BloomSubPattern bloomDownward(-40, false, 2, true);

void logMemory() {
  Serial.print("Used PSRAM: ");
  Serial.println(ESP.getPsramSize() - ESP.getFreePsram());
}

void setup() {
  Serial.begin(115200);
  delay(500);

  leds = (CRGB *)ps_malloc(sizeof(CRGB) * NUM_LEDS_TOTAL);
  ledBrightness = (uint8_t *)ps_malloc(sizeof(uint8_t) * NUM_LEDS_TOTAL);
  logMemory();

  uint16_t startIndex = 0;
  FastLED.addLeds<NEOPIXEL, PIN_1>(leds, startIndex, NUM_LEDS_PIN_1);
  startIndex += NUM_LEDS_PIN_1;
  FastLED.addLeds<NEOPIXEL, PIN_2>(leds, startIndex, NUM_LEDS_PIN_2);
  startIndex += NUM_LEDS_PIN_2;
  FastLED.addLeds<NEOPIXEL, PIN_3>(leds, startIndex, NUM_LEDS_PIN_3);
  startIndex += NUM_LEDS_PIN_3;
  FastLED.addLeds<NEOPIXEL, PIN_4>(leds, startIndex, NUM_LEDS_PIN_4);
  startIndex += NUM_LEDS_PIN_4;
  FastLED.addLeds<NEOPIXEL, PIN_5>(leds, startIndex, NUM_LEDS_PIN_5);
  startIndex += NUM_LEDS_PIN_5;
  FastLED.addLeds<NEOPIXEL, PIN_6>(leds, startIndex, NUM_LEDS_PIN_6);
  startIndex += NUM_LEDS_PIN_6;
  FastLED.addLeds<NEOPIXEL, PIN_7>(leds, startIndex, NUM_LEDS_PIN_7);

  uint16_t offset = 0;
  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    Disc disc = {d,
                 NUM_LEDS_DISC[d],
                 NUM_LEDS_PETAL[d][0],
                 NUM_LEDS_PETAL[d][1],
                 NUM_LEDS_PETAL[d][2],
                 MAX_RADIUS_DISC[d],
                 &leds[offset],
                 &ledBrightness[offset]};

    discs[d] = disc;
    offset += disc.numLEDs;
  }

  // Initialize all LEDs to black
  for (int16_t i = 0; i < NUM_LEDS_TOTAL; i++) {
    leds[i] = CRGB::Black;
  }

  FastLED.setBrightness(100);
}

void loop() {
  clearLEDs();
  palette = palette.cycle();

  // cyclePalettes();
  // showPalette();

  // twinkle.show();

  bloomStartSame.show();

  // rubberBandAnchored();
  // basicSpiralRotation();
  // rubberBandNoAnchor();
  // rubberBandWorm();
  // continuousSpiral();
  // growingSpirals();

  EVERY_N_MILLISECONDS(5000) {
    // spiral = spiral.reverse();
    // spiral2 = spiral2.reverse();
    // spiral3 = spiral3.reverse();
  }

  FastLED.show();
  ticks++;
}


void plotVars(int numValues, ...) {
  va_list values;
  va_start(values, numValues);
  for (int i = 0; i < numValues; i++) {
    Serial.print(va_arg(values, int));
    Serial.print(" ");
  }
  va_end(values);
  Serial.println();
}

void growingSpirals() {
  if (ticks == 0) {
    spiral = spiral.id(1).radiusRangePercent(50, 100).speed(0).angle(0);
    spiral2 = spiral2.id(2).radiusRangePercent(50, 100).speed(0).angle(120);
    spiral3 = spiral3.id(3).radiusRangePercent(50, 100).speed(0).angle(240);
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      spiral = spiral.discOffset(d, d * 30);
      spiral2 = spiral2.discOffset(d, d * 30);
      spiral3 = spiral3.discOffset(d, d * 30);
    }
  }

  unsigned long w = 100;  // waveLength
  unsigned long wo = 33;  // waveLengthOffset
  spiral =
      spiral
          .heightRangePercent(sawtooth(-50, 150, w, wo), sawtooth(-50, 150, w))
          .show();
  spiral2 = spiral2
                .heightRangePercent(sawtooth(-50, 150, w, wo * 2),
                                    sawtooth(-50, 150, w, wo))
                .show();
  spiral3 = spiral3
                .heightRangePercent(sawtooth(-50, 150, w, w),
                                    sawtooth(-50, 150, w, wo * 2))
                .show();
}

void rubberBandWorm() {
  if (ticks == 0) {
    spiral = spiral.radiusRangePercent(50, 100);
  }

  int16_t offset = sinwave(-90, 90, 100);
  int16_t width = sinwave(-180, 180, 100);
  int16_t speed = sinwave(3, 6);

  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    spiral = spiral.speed(speed).discOffset(d, d * offset).width(abs(width));
  }
  spiral = spiral.show();
}

void rubberBandNoAnchor() {
  if (ticks == 0) {
    spiral = spiral.radiusRangePercent(50, 100).speed(0);
  }

  int16_t angle = sinwave(-200, 200, 200);
  int16_t offset = sinwave(-90, 90, 200);
  int16_t width = sinwave(-180, 180, 200);

  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    spiral = spiral.angle(angle).discOffset(d, d * offset).width(abs(width));
  }
  spiral = spiral.show();
}

void rubberBandAnchored() {
  if (ticks == 0) {
    spiral = spiral.radiusRangePercent(50, 100).angle(0).speed(0);
  }

  int toMin = square(8, 0, 100);
  int toMax = square(0, 8, 100);
  // int16_t offset = sinwave(-360, 360, 100);
  // int16_t offset = sawtooth(-360, 360, 100); // swapping effect
  int16_t offset = cosSawtooth(-360, 360, 100);
  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    int16_t discOffset = mapf(d, toMin, toMax, 0, offset);
    spiral = spiral.discOffset(d, discOffset);
  }
  spiral = spiral.show();
}

void basicSpiralRotation() {
  if (ticks == 0) {
    spiral = spiral.id(1).radiusRangePercent(50, 100).speed(2);
    spiral2 = spiral2.id(2).radiusRangePercent(50, 100).speed(-2);

    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      spiral = spiral.discOffset(d, (NUM_DISCS - 1 - d) * 30);
      spiral2 = spiral2.discOffset(d, d * 30);
    }
  }

  spiral = spiral.show();
  spiral2 = spiral2.show();
}

void continuousSpiral() {
  if (ticks == 0) {
    spiral = spiral.radiusRangePercent(50, 100).speed(3);
  }
  unsigned long waveLength = 400;
  unsigned long waveLengthOffset = waveLength * 3 / 4;
  int16_t offset = sawtooth(0, 360, waveLength);
  int16_t width = sinwave(30, 180, waveLength / 2, waveLengthOffset);
  int16_t minRadiusPercent = sinwave(0, 90, waveLength / 2, waveLengthOffset);
  int16_t maxRadiusPercent = sinwave(90, 100, waveLength / 2, waveLengthOffset);
  int16_t speed = sinwave(0, 5, waveLength / 2, waveLengthOffset);
  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    spiral = spiral.discOffset(d, (1 + d) * offset)
                 .width(width)
                 .speed(speed)
                 .radiusRangePercent(minRadiusPercent, maxRadiusPercent);
  }
  spiral = spiral.show();
  plotVars(3, 4 * offset, 4 * width, 4 * speed * 100);
}

void cyclePalettes() {
  // Cycle through color modes for demonstration
  EVERY_N_SECONDS(15) {
    palette.colorMode = palette.colorMode < 4 ? palette.colorMode + 1 : 0;
  }

  showPalette();
}

void showPalette() {
  FastLED.setBrightness(50);
  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    for (uint8_t p = 0; p < discs[d].numLEDs; p++) {
      discs[d].leds[p] = palette.getColor(d, p, true);
      // discs[d].leds[p] = campfire[d];
    }
  }
  FastLED.show();
}

void clearLEDs() {
  for (uint16_t i = 0; i < NUM_LEDS_TOTAL; i++) {
    ledBrightness[i] = 0;
    leds[i].nscale8(0);
  }
}
