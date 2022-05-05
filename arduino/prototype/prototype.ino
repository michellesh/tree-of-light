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
#include "SpiralSubPattern.h"
#include "TwinkleSubPattern.h"

TwinkleSubPattern twinkle;

BloomSubPattern bloomContinuous(BloomSubPattern::CONTINUOUS);
BloomSubPattern bloomStartSame(BloomSubPattern::START_SAME);
BloomSubPattern bloomEndSame(BloomSubPattern::END_SAME);
BloomSubPattern bloomUpward(BloomSubPattern::UPWARD);
BloomSubPattern bloomDownward(BloomSubPattern::DOWNWARD);

SpiralSubPattern rubberBandWorm(SpiralSubPattern::RUBBER_BAND_WORM);
SpiralSubPattern rubberBandNoAnchor(SpiralSubPattern::RUBBER_BAND_NO_ANCHOR);
SpiralSubPattern rubberBandAnchored(SpiralSubPattern::RUBBER_BAND_ANCHORED);
SpiralSubPattern growingSpirals(SpiralSubPattern::GROWING_SPIRALS);
SpiralSubPattern basicSpiralRotation(SpiralSubPattern::BASIC_SPIRAL_ROTATION);
SpiralSubPattern continuousSpiral(SpiralSubPattern::CONTINUOUS_SPIRAL);

// clang-format off
SubPattern *activePatterns[] = {
  &twinkle,
  &bloomContinuous,
  &bloomStartSame,
  &bloomEndSame,
  &bloomUpward,
  &bloomDownward,
  &rubberBandWorm,
  &rubberBandNoAnchor,
  &rubberBandAnchored,
  &growingSpirals,
  &basicSpiralRotation,
  &continuousSpiral
};
// clang-format on

SubPattern *sourcePattern;
SubPattern *targetPattern;
uint8_t numPatterns = sizeof(activePatterns) / sizeof(activePatterns[0]);

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

  // Set first pattern in activePatterns to be played first
  sourcePattern = (SubPattern *)activePatterns[numPatterns - 1];
  sourcePattern->setPercentBrightness(0);
  targetPattern = (SubPattern *)activePatterns[0];
  targetPattern->setPercentBrightness(100);
}

void loop() {
  clearLEDs();
  palette.cycle();

  EVERY_N_SECONDS(15) {
    // Increment active pattern
    sourcePattern = (SubPattern *)targetPattern;
    static uint8_t nextPattern = 0;
    nextPattern = (nextPattern + 1) % numPatterns;
    targetPattern = (SubPattern *)(activePatterns[nextPattern]);
  }

  EVERY_N_MILLISECONDS(100) {
    shiftPercentBrightnessTo(targetPattern, 100);
    shiftPercentBrightnessTo(sourcePattern, 0);
  }

  for (uint8_t i = 0; i < numPatterns; i++) {
    if (activePatterns[i]->getPercentBrightness() > 0) {
      activePatterns[i]->show();
    }
  }

  // demoColorModes();

  FastLED.show();
  ticks++;
}

void shiftPercentBrightnessTo(SubPattern *pattern,
                              uint8_t toPercentBrightness) {
  if (pattern->getPercentBrightness() == toPercentBrightness) {
    return;
  } else if (pattern->getPercentBrightness() < toPercentBrightness) {
    pattern->setPercentBrightness(
        min(pattern->getPercentBrightness() + 3, 100));
  } else if (pattern->getPercentBrightness() > toPercentBrightness) {
    pattern->setPercentBrightness(max(pattern->getPercentBrightness() - 3, 0));
  }
}

void clearLEDs() {
  for (uint16_t i = 0; i < NUM_LEDS_TOTAL; i++) {
    ledBrightness[i] = 0;
    leds[i].nscale8(0);
  }
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

void demoColorModes() {
  // Cycle through color modes for demonstration
  EVERY_N_SECONDS(10) {
    palette.setColorMode((palette.getActiveColorMode() + 1) % 6);
    Serial.println(palette.getActiveColorMode());
  }
  FastLED.setBrightness(50);
  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    for (uint8_t p = 0; p < discs[d].numLEDs; p++) {
      discs[d].leds[p] = palette.getColor(d, p, true);
    }
  }
}
