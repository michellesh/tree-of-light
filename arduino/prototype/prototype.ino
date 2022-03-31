#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>

#define LED_TYPE    NEOPIXEL
#define NUM_DISCS  9

#define NUM_LEDS_PIN_1  200
#define NUM_LEDS_PIN_2  184
#define NUM_LEDS_PIN_3  196
#define NUM_LEDS_PIN_4  202
#define NUM_LEDS_PIN_5  198
#define NUM_LEDS_PIN_6  190
#define NUM_LEDS_PIN_7  114

CRGB LEDS_PIN_1[NUM_LEDS_PIN_1];
CRGB LEDS_PIN_2[NUM_LEDS_PIN_2];
CRGB LEDS_PIN_3[NUM_LEDS_PIN_3];
CRGB LEDS_PIN_4[NUM_LEDS_PIN_4];
CRGB LEDS_PIN_5[NUM_LEDS_PIN_5];
CRGB LEDS_PIN_6[NUM_LEDS_PIN_6];
CRGB LEDS_PIN_7[NUM_LEDS_PIN_7];

// The number of LEDs per "petal group" indexed by disc number.
// eg. PG_NUM_LEDS[0] is number of LEDs in one "petal group" on disc 0
uint8_t PG_NUM_LEDS[] = {40, 36, 31, 28, 25, 20, 15, 12, 7};
uint8_t DISC_NUM_LEDS[] = {240, 216, 186, 168, 150, 120, 90, 72, 42};

CRGB colors[] = {
  CRGB::White,
  CRGB::Purple,
  CRGB::Violet,
  CRGB::Blue,
  CRGB::Teal,
  CRGB::Green,
  CRGB::Yellow,
  CRGB::Orange,
  CRGB::Red,
};

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
}

void loop() {
  for (uint16_t discIndex = 0; discIndex < NUM_DISCS; discIndex++) {
    for (uint16_t i = 0; i < DISC_NUM_LEDS[discIndex]; i++) {
      setLED(discIndex, i, colors[discIndex]);
    }
  }
  FastLED.show();
}
