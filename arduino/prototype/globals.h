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

//                 DISC:   0    1    2    3    4    5   6   7   8
uint8_t NUM_LEDS[] =    {240, 216, 186, 168, 150, 120, 90, 72, 42};
uint8_t NUM_INNER_1[] = {  8,   8,   7,   6,   5,   4,  3,  2,  1};
uint8_t NUM_INNER_2[] = { 10,   9,   7,   7,   6,   5,  4,  3,  2};
uint8_t NUM_OUTER[] =   {  6,   5,   5,   4,   4,   3,  2,  2,  1};

// returns the number of LEDs per "petal group"
uint8_t pgNumLEDs(uint8_t discIndex) {
  return NUM_LEDS[discIndex] / 6;
}

void setPinLED(uint8_t discIndex, uint8_t pixelIndex, CRGB color) {
  switch (discIndex) {
    case 0:
      // 5 petals on pin 1
      // 1 petal on pin 2
      if (pixelIndex < 5 * pgNumLEDs(0)) {
        LEDS_PIN_1[pixelIndex] = color;
      } else {
        LEDS_PIN_2[pixelIndex - 5 * pgNumLEDs(0)] = color;
      }
      break;
    case 1:
      // 4 petals on pin 2
      // 2 petals on pin 3
      if (pixelIndex < 4 * pgNumLEDs(1)) {
        LEDS_PIN_2[pixelIndex + pgNumLEDs(0)] = color;
      } else {
        LEDS_PIN_3[pixelIndex - 4 * pgNumLEDs(1)] = color;
      }
      break;
    case 2:
      // 4 petals on pin 3
      // 2 petals on pin 4
      if (pixelIndex < 4 * pgNumLEDs(2)) {
        LEDS_PIN_3[pixelIndex + 2 * pgNumLEDs(1)] = color;
      } else {
        LEDS_PIN_4[pixelIndex - 4 * pgNumLEDs(2)] = color;
      }
      break;
    case 3:
      // 5 petals on pin 4
      // 1 petal on pin 5
      if (pixelIndex < 5 * pgNumLEDs(3)) {
        LEDS_PIN_4[pixelIndex + 2 * pgNumLEDs(2)] = color;
      } else {
        LEDS_PIN_5[pixelIndex - 5 * pgNumLEDs(3)] = color;
      }
      break;
    case 4:
      // 6 petals on pin 5
      LEDS_PIN_5[pixelIndex + pgNumLEDs(3)] = color;
      break;
    case 5:
      // 1 petal on pin 5
      // 5 petals on pin 6
      if (pixelIndex < pgNumLEDs(5)) {
        LEDS_PIN_5[pixelIndex + pgNumLEDs(3) + 6 * pgNumLEDs(4)] = color;
      } else {
        LEDS_PIN_6[pixelIndex - pgNumLEDs(5)] = color;
      }
      break;
    case 6:
      // 6 petals on pin 6
      LEDS_PIN_6[pixelIndex + 5 * pgNumLEDs(5)] = color;
      break;
    case 7:
      // 6 petals on pin 7
      LEDS_PIN_7[pixelIndex] = color;
      break;
    case 8:
      // 6 petals on pin 7
      LEDS_PIN_7[pixelIndex + 6 * pgNumLEDs(7)] = color;
      break;
    default:
      break;
  }
}
