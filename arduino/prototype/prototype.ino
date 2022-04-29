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

  // spiral = spiral.radiusRangePercent(0, 50);
  // spiral2 = spiral2.id(2).reverse().discOffset(-30).radiusRangePercent(50,
  // 100);
  // spiral3 = spiral3.id(3).offset(240);
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
  // rubberBandLinear();
  // rubberBandSwap();
  rubberBandBounce();
  // basicSpiralRotation();

  // spiral = spiral.show();
  // spiral2 = spiral2.show();
  // spiral3 = spiral3.show();

  EVERY_N_MILLISECONDS(5000) {
    // spiral = spiral.reverse();
    // spiral2 = spiral2.reverse();
    // spiral3 = spiral3.reverse();
  }

  FastLED.show();
  ticks++;
}

void rubberBandSwap() {
  if (ticks == 0) {
    spiral = spiral.id(1).radiusRangePercent(50, 100);
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      spiral = spiral.discAngle(d, d * 55);
    }
  }

  int toMin = square(8, 0, 100);
  int toMax = square(0, 8, 100);

  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    int16_t angle = mapf(d, 0, NUM_DISCS - 1, toMin, toMax);
    spiral = spiral.addDiscAngle(d, angle);
  }
  spiral = spiral.show();
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

void rubberBandBounce() {
  int toMin = square(8, 0, 100);
  int toMax = square(0, 8, 100);
  int16_t angle = oscillate(-360, 360, 100);
  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    int16_t discAngle = mapf(d, toMin, toMax, 0, angle);
    spiral = spiral.discAngle(d, discAngle);
  }
  spiral = spiral.show();
  plotVars(3, toMin * 100, toMax * 100, angle);
}

void basicSpiralRotation() {
  if (ticks == 0) {
    spiral = spiral.id(1).radiusRangePercent(50, 100);
    spiral2 = spiral2.id(2).radiusRangePercent(50, 100);

    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      spiral = spiral.discAngle(d, (NUM_DISCS - 1 - d) * 30);
      spiral2 = spiral2.discAngle(d, d * 30);
    }
  }

  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    spiral = spiral.addDiscAngle(d, 3);
    spiral2 = spiral2.addDiscAngle(d, -3);

    // spiral = spiral.discAngle(NUM_DISCS - 1 - d, d * offset);
  }
  spiral = spiral.show();
  spiral2 = spiral2.show();

  // spiral = spiral.discOffset(oscillate(-360, 360))
  //                .width(oscillate(50, 180))
  //                .speed(oscillate(-3, 3, 100))
  //                .angle(oscillate(-500, 500)) //sawtooth(0, 360, 100)
  //                .show();
}

void rubberBandLinear() {
  spiral = spiral
               .discOffset(oscillateLinear(0, spiral.DISC_OFFSET.MAX))
               //.width(oscillateLinear(50, 180))
               //.speed(oscillateLinear(-6, 6, 100))
               .show();
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
