#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>
#include "secrets.h"
#include "globals.h"
#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  uint8_t discIndex = getDiscIndex();
  initArrays();
  initLEDs(discIndex);
}

void loop() {
  for(uint16_t disc = 0; disc < NUM_DISCS; disc++) {
    for(uint16_t strip = 0; strip < NUM_STRIPS_PER_DISC; strip++) {
      for(uint16_t pixel = 0; pixel < getNumLeds(disc); pixel++) {
        setLED(disc, strip, pixel, CRGB::Blue);
      }
    }
  }
  FastLED.show();
  delay(2000);
  for(uint16_t disc = 0; disc < NUM_DISCS; disc++) {
    for(uint16_t strip = 0; strip < NUM_STRIPS_PER_DISC; strip++) {
      for(uint16_t pixel = 0; pixel < getNumLeds(disc); pixel++) {
        setLED(disc, strip, pixel, CRGB::Black);
      }
    }
  }
  FastLED.show();
  delay(2000);
}
