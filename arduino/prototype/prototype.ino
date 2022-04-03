#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>

#include "globals.h"
#include "colors.h"
#include "Disc.h"

Disc discs[NUM_DISCS];

void setup() {
  Serial.begin(115200);
  delay(500);

  uint16_t offset = 0;
  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    Disc disc = {d, NUM_LEDS[d], offset};
    discs[d] = disc;
    offset += disc.numLEDs;
  }

  leds = new CRGB[NUM_LEDS_PIN_1 +
                  NUM_LEDS_PIN_2 +
                  NUM_LEDS_PIN_3 +
                  NUM_LEDS_PIN_4 +
                  NUM_LEDS_PIN_5 +
                  NUM_LEDS_PIN_6 +
                  NUM_LEDS_PIN_7];

  uint16_t totalLEDs = 0;
  FastLED.addLeds<LED_TYPE, PIN_1>(leds, totalLEDs, NUM_LEDS_PIN_1);
  totalLEDs += NUM_LEDS_PIN_1;
  FastLED.addLeds<LED_TYPE, PIN_2>(leds, totalLEDs, NUM_LEDS_PIN_2);
  totalLEDs += NUM_LEDS_PIN_2;
  FastLED.addLeds<LED_TYPE, PIN_3>(leds, totalLEDs, NUM_LEDS_PIN_3);
  totalLEDs += NUM_LEDS_PIN_3;
  FastLED.addLeds<LED_TYPE, PIN_4>(leds, totalLEDs, NUM_LEDS_PIN_4);
  totalLEDs += NUM_LEDS_PIN_4;
  FastLED.addLeds<LED_TYPE, PIN_5>(leds, totalLEDs, NUM_LEDS_PIN_5);
  totalLEDs += NUM_LEDS_PIN_5;
  FastLED.addLeds<LED_TYPE, PIN_6>(leds, totalLEDs, NUM_LEDS_PIN_6);
  totalLEDs += NUM_LEDS_PIN_6;
  FastLED.addLeds<LED_TYPE, PIN_7>(leds, totalLEDs, NUM_LEDS_PIN_7);

  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    discs[d].pixels = &leds[discs[d].offset];
  }

  FastLED.setBrightness(50);
}

void loop() {
  for (uint8_t d = 0; d < NUM_DISCS; d++) {
    for (uint8_t p = 0; p < discs[d].numLEDs; p++) {
      discs[d].pixels[p] = rainbow[d];
    }
  }
  FastLED.show();
}
