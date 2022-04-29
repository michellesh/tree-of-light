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

#include "Palette.h"
Palette palette;

#include "Range.h"
#include "Bloom.h"
#include "Spiral.h"
#include "Twinkle.h"

Bloom bloom, bloom2;
Spiral spiral, spiral2, spiral3;
Twinkle twinkle;

void setup() {
  Serial.begin(115200);
  delay(500);

  leds = new CRGB[NUM_LEDS_TOTAL];

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
                 offset,
                 &leds[offset],
                 MAX_RADIUS_DISC[d]};

    discs[d] = disc;
    offset += disc.numLEDs;
  }

  // Initialize all LEDs to black
  for (int16_t i = 0; i < NUM_LEDS_TOTAL; i++) {
    leds[i] = CRGB::Black;
  }

  bloom = bloom.initStartSame();
  bloom2 = bloom2.offset(bloom.OFFSET.MAX / 2 + bloom.WIDTH.DFLT / 2)
               .initStartSame();
}

int bloomType = 0;

void loop() {
  palette = palette.cycle();

  // cyclePalettes();
  // showPalette();
  // cycleBloomTypes();

  // bloom = bloom.speed(2).show();
  // bloom2 = bloom2.speed(2).show();

  EVERY_N_MILLISECONDS(1000) {
    // bloom = bloom.reverse();
    // bloom2 = bloom2.reverse();
  }

  // twinkle = twinkle.show();

  // rubberBandAnchored();
  // basicSpiralRotation();
  // rubberBandNoAnchor();
  // rubberBandWorm();
  continuousSpiral();

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
    spiral = spiral.id(1).radiusRangePercent(50, 100).speed(3);
    spiral2 = spiral2.id(2).radiusRangePercent(50, 100).speed(-3);

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
  int16_t offset = sawtooth(0, 360, 200);
  int16_t width = sinwave(30, 180, 100, 150);
  int16_t minRadiusPercent = sinwave(0, 90, 100, 150);
  int16_t maxRadiusPercent = sinwave(90, 100, 100, 150);
  int16_t speed = sinwave(0, 5, 100, 150);
  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    spiral = spiral.discOffset(d, (1 + d) * offset)
                 .width(width)
                 .speed(speed)
                 .radiusRangePercent(minRadiusPercent, maxRadiusPercent);
  }
  spiral = spiral.show();
  plotVars(3, offset, width, speed * 100);
}

void cycleBloomTypes() {
  EVERY_N_SECONDS(10) {
    bloomType++;
    if (bloomType >= 5) {
      bloomType = 0;
    }
    if (bloomType == 0) {
      bloom = bloom.initStartSame();
    } else if (bloomType == 1) {
      bloom = bloom.initUpward();
    } else if (bloomType == 2) {
      bloom = bloom.initDownward();
    } else if (bloomType == 3) {
      bloom = bloom.initEndSame();
    } else {
      bloom = bloom.initContinuous();
    }
  }

  bloom = bloom.show();
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
