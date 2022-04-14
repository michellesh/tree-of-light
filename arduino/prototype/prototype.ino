#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>

#include "globals.h"
#include "colors.h"
#include "utils.h"
#include "Disc.h"
#include "Palette.h"

Disc discs[NUM_DISCS];
Palette palette;
CRGB *leds;

#include "Range.h"
#include "Ripple.h"
#include "Spin.h"
#include "Twinkle.h"

Ripple ripple;
Spin spin;
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
    Disc disc = {d, NUM_LEDS_DISC[d], offset, &leds[offset],
                 MAX_RADIUS_DISC[d]};

    discs[d] = disc;
    offset += disc.numLEDs;
  }

  // FastLED.setBrightness(50);

  palette = palette.setNextColorPalette();
}

void loop() {
  palette = palette.cycle();

  //ripple = ripple.show();

  //twinkle = twinkle.show();

  spin = spin.width(spin.WIDTH.DFLT)
             .speed(5)
             .offset(spin.OFFSET.DFLT)
             .show();

  ticks++;
}
