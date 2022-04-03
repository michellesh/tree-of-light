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

  FastLED.addLeds<LED_TYPE, 2>(LEDS_PIN_1, NUM_LEDS_PIN_1);
  FastLED.addLeds<LED_TYPE, 4>(LEDS_PIN_2, NUM_LEDS_PIN_2);
  FastLED.addLeds<LED_TYPE, 5>(LEDS_PIN_3, NUM_LEDS_PIN_3);
  FastLED.addLeds<LED_TYPE, 12>(LEDS_PIN_4, NUM_LEDS_PIN_4);
  FastLED.addLeds<LED_TYPE, 13>(LEDS_PIN_5, NUM_LEDS_PIN_5);
  FastLED.addLeds<LED_TYPE, 14>(LEDS_PIN_6, NUM_LEDS_PIN_6);
  FastLED.addLeds<LED_TYPE, 18>(LEDS_PIN_7, NUM_LEDS_PIN_7);

  for (uint16_t d = 0; d < NUM_DISCS; d++) {
    Disc disc = {d, NUM_LEDS[d], NUM_INNER_1[d], NUM_INNER_2[d], NUM_OUTER[d]};
    discs[d] = disc;

    for (uint8_t p = 0; p < disc.numLEDs; p++) {
      discs[d].setLED(p, rainbow[d]);
    }
  }

  FastLED.setBrightness(50);
}

void loop() {
  FastLED.show();
}
