void setLED(uint8_t discIndex, uint8_t pixelIndex, CRGB color) {
  switch (discIndex) {
    case 0:
      // 5 petals on pin 1
      // 1 petal on pin 2
      if (pixelIndex < 5 * PG_NUM_LEDS[0]) {
        LEDS_PIN_1[pixelIndex] = color;
      } else {
        LEDS_PIN_2[pixelIndex - 5 * PG_NUM_LEDS[0]] = color;
      }
      break;
    case 1:
      // 4 petals on pin 2
      // 2 petals on pin 3
      if (pixelIndex < 4 * PG_NUM_LEDS[1]) {
        LEDS_PIN_2[pixelIndex + PG_NUM_LEDS[0]] = color;
      } else {
        LEDS_PIN_3[pixelIndex - 4 * PG_NUM_LEDS[1]] = color;
      }
      break;
    case 2:
      // 4 petals on pin 3
      // 2 petals on pin 4
      if (pixelIndex < 4 * PG_NUM_LEDS[2]) {
        LEDS_PIN_3[pixelIndex + 2 * PG_NUM_LEDS[1]] = color;
      } else {
        LEDS_PIN_4[pixelIndex - 4 * PG_NUM_LEDS[2]] = color;
      }
      break;
    case 3:
      // 5 petals on pin 4
      // 1 petal on pin 5
      if (pixelIndex < 5 * PG_NUM_LEDS[3]) {
        LEDS_PIN_4[pixelIndex + 2 * PG_NUM_LEDS[2]] = color;
      } else {
        LEDS_PIN_5[pixelIndex - 5 * PG_NUM_LEDS[3]] = color;
      }
      break;
    case 4:
      // 6 petals on pin 5
      LEDS_PIN_5[pixelIndex + PG_NUM_LEDS[3]] = color;
      break;
    case 5:
      // 1 petal on pin 5
      // 5 petals on pin 6
      if (pixelIndex < PG_NUM_LEDS[5]) {
        LEDS_PIN_5[pixelIndex + PG_NUM_LEDS[3] + 6 * PG_NUM_LEDS[4]] = color;
      } else {
        LEDS_PIN_6[pixelIndex - PG_NUM_LEDS[5]] = color;
      }
      break;
    case 6:
      // 6 petals on pin 6
      LEDS_PIN_6[pixelIndex + 5 * PG_NUM_LEDS[5]] = color;
      break;
    case 7:
      // 6 petals on pin 7
      LEDS_PIN_7[pixelIndex] = color;
      break;
    case 8:
      // 6 petals on pin 7
      LEDS_PIN_7[pixelIndex + 6 * PG_NUM_LEDS[7]] = color;
      break;
    default:
      break;
  }
}
