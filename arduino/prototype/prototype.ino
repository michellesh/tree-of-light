#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>
#include <WiFi.h>
#include <esp_now.h>

#include "globals.h"
#include "colors.h"
#include "utils.h"
#include "fade.h"
#include "Disc.h"
#include "Timer.h"

Disc discs[NUM_DISCS];
CRGB *leds;
uint8_t *ledBrightness;

#include "tree-of-light-shared.h"
msg data;

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

TwinkleSubPattern twinkleLow(TwinkleSubPattern::LOW_DENSITY);
TwinkleSubPattern twinkleMedium(TwinkleSubPattern::MEDIUM_DENSITY);
TwinkleSubPattern twinkleHigh(TwinkleSubPattern::HIGH_DENSITY);

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
  &twinkleLow,
  &twinkleMedium,
  &twinkleHigh,
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

uint8_t twinkleIndexRange[] = {0, 2};
uint8_t bloomIndexRange[] = {3, 7};
uint8_t spiralIndexRange[] = {8, 13};

uint8_t sliderBrightness = 255;
uint8_t sliderSpeed = 1;
uint8_t sliderHue = 0;
Ripple sliderRipple;

SubPattern *sourcePattern;
SubPattern *targetPattern;
uint8_t numPatterns = sizeof(activePatterns) / sizeof(activePatterns[0]);
uint8_t activePatternIndex = 0;
uint8_t strobe = 0;

Timer sliderRippleTimer = {4000};

void logMemory() {
  Serial.print("Used PSRAM: ");
  Serial.println(ESP.getPsramSize() - ESP.getFreePsram());
}

void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(onDataRecv);

  leds = new CRGB[NUM_LEDS_TOTAL];
  ledBrightness = new uint8_t[NUM_LEDS_TOTAL];
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

// Callback function that will be executed when data is received
void onDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&data, incomingData, sizeof(data));

  // Button actions
  if (data.action == RED_BUTTON) {
    Serial.print("RED_BUTTON: ");
    Serial.println(data.value);
    if (data.value == 0) {
      uint8_t newPatternIndex = activePatternIndex >= bloomIndexRange[0] &&
                                        activePatternIndex < bloomIndexRange[1]
                                    ? activePatternIndex + 1
                                    : bloomIndexRange[0];
      setActivePattern(newPatternIndex);
    }
  } else if (data.action == WHITE_BUTTON) {
    Serial.print("WHITE_BUTTON: ");
    Serial.println(data.value);
    if (data.value == 0) {
      uint8_t newPatternIndex = activePatternIndex >= twinkleIndexRange[0] &&
                                        activePatternIndex < twinkleIndexRange[1]
                                    ? activePatternIndex + 1
                                    : twinkleIndexRange[0];
      setActivePattern(newPatternIndex);
    }
  } else if (data.action == YELLOW_BUTTON) {
    Serial.print("YELLOW_BUTTON: ");
    Serial.println(data.value);
    if (data.value == 0) {
      uint8_t newPatternIndex = activePatternIndex >= spiralIndexRange[0] &&
                                        activePatternIndex < spiralIndexRange[1]
                                    ? activePatternIndex + 1
                                    : spiralIndexRange[0];
      setActivePattern(newPatternIndex);
      Serial.print("newPatternIndex: ");
      Serial.println(newPatternIndex);
    }
  } else if (data.action == BLUE_BUTTON) {
    Serial.print("BLUE_BUTTON: ");
    Serial.println(data.value);
    strobe = data.value;
  } else if (data.action == GREEN_BUTTON) {
    Serial.print("GREEN_BUTTON: ");
    Serial.println(data.value);
    strobe = data.value * 2;

  // Slider actions
  } else if (data.action == SLIDER_1) {
    Serial.print("SLIDER_1: ");
    Serial.println(data.value);
    sliderBrightness = map(data.value, 1000, 0, 0, 255);
  } else if (data.action == SLIDER_2) {
    Serial.print("SLIDER_2: ");
    Serial.println(data.value);
    sliderHue = map(data.value, 0, 1000, 0, 255);
    uint8_t paletteIndex = map(data.value, 0, 1000, 0, palette.getNumPalettes() - 1);
    palette.setPalette(paletteIndex);
  } else if (data.action == SLIDER_3) {
    Serial.print("SLIDER_3: ");
    Serial.println(data.value);
    // affects global `ticks` variable which controls speed of spirals
    sliderSpeed = map(data.value, 1000, 0, 1, 4);

    // set bloom speeds
    uint8_t bloomSpeed = map(data.value, 1000, 0, Bloom::SPEED.MIN, Bloom::SPEED.MAX);
    bloomContinuous.setSpeed(bloomSpeed);
    bloomStartSame.setSpeed(bloomSpeed);
    bloomEndSame.setSpeed(bloomSpeed);
    bloomUpward.setSpeed(bloomSpeed);
    bloomDownward.setSpeed(bloomSpeed);

    // set twinkle speeds
    uint8_t twinkleSpeed = map(data.value, 1000, 0, Twinkle::SPEED.MIN, Twinkle::SPEED.MAX);
    twinkleLow.setSpeed(twinkleSpeed);
    twinkleMedium.setSpeed(twinkleSpeed);
    twinkleHigh.setSpeed(twinkleSpeed);
  } else if (data.action == SLIDER_4) {
    Serial.print("SLIDER_4: ");
    Serial.println(data.value);
    int16_t maxCumulativeRadius[NUM_DISCS];
    int16_t cumulativeRadius = 0;
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      cumulativeRadius += discs[d].maxRadius;
      maxCumulativeRadius[d] = cumulativeRadius;
    }
    int16_t sliderRadius = map(data.value, 0, 1000, 0, cumulativeRadius);
    uint8_t discIndex = 0;
    for (uint8_t d = 0; d < NUM_DISCS - 1; d++) {
      if (sliderRadius > maxCumulativeRadius[d] && sliderRadius < maxCumulativeRadius[d + 1]) {
        discIndex = d + 1;
      }
    }
    sliderRipple.setDiscIndex(discIndex);
    int16_t prevCumulativeRadius = discIndex == 0 ? 0 : maxCumulativeRadius[discIndex - 1];
    sliderRipple.setRadius(sliderRadius - prevCumulativeRadius);
    sliderRippleTimer.reset();
  }
}

void setActivePattern(uint8_t patternIndex) {
  activePatterns[activePatternIndex]->setPercentBrightness(0);
  activePatternIndex = patternIndex;
  activePatterns[activePatternIndex]->setPercentBrightness(100);
}

void loopWithButtonBoxControl() {
  clearLEDs();
  palette.cycle();

  if (strobe == 1) {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      for (uint8_t p = 0; p < discs[d].numLEDs; p++) {
        discs[d].leds[p] = CHSV(sliderHue, 255, 255);
      }
    }
  } else if (strobe == 2) {
    for (uint8_t d = 0; d < NUM_DISCS; d++) {
      for (uint8_t p = 0; p < discs[d].numLEDs; p++) {
        discs[d].leds[p] = CHSV(map(d, 0, NUM_DISCS, 0, 255), 255, 255);
      }
    }
  } else {
    activePatterns[activePatternIndex]->show();
  }

  if (!sliderRippleTimer.complete()) {
    uint8_t percentBrightness = map(millis() - sliderRippleTimer.lastCycleTime, 0, sliderRippleTimer.totalCycleTime, 100, 0);
    sliderRipple.show(Bloom::WIDTH.DFLT, percentBrightness);
  }

  FastLED.setBrightness(sliderBrightness);
  FastLED.show();
  ticks += sliderSpeed;
}

void loopCyclePatternsWithFade() {
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

void loop() {
  //loopCyclePatternsWithFade();
  loopWithButtonBoxControl();
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
