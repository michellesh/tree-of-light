int getNumLeds(int discIndex) {
  return discIndex == 0 ? NUM_LEDS_DISC_0
         : discIndex == 1 ? NUM_LEDS_DISC_1
         : discIndex == 2 ? NUM_LEDS_DISC_2
         : discIndex == 3 ? NUM_LEDS_DISC_3
         : discIndex == 4 ? NUM_LEDS_DISC_4
         : discIndex == 5 ? NUM_LEDS_DISC_5
         : discIndex == 6 ? NUM_LEDS_DISC_6
                          : NUM_LEDS_DISC_7;
}

void setLED(int disc, int strip, int pixel, CRGB color) {
  if (disc == 0) {
    switch (strip) {
      case 0: DISC_0_STRIP_00[pixel] = color; break;
      case 1: DISC_0_STRIP_01[pixel] = color; break;
      case 2: DISC_0_STRIP_02[pixel] = color; break;
      case 3: DISC_0_STRIP_03[pixel] = color; break;
      case 4: DISC_0_STRIP_04[pixel] = color; break;
      case 5: DISC_0_STRIP_05[pixel] = color; break;
      case 6: DISC_0_STRIP_06[pixel] = color; break;
      case 7: DISC_0_STRIP_07[pixel] = color; break;
      case 8: DISC_0_STRIP_08[pixel] = color; break;
      case 9: DISC_0_STRIP_09[pixel] = color; break;
      case 10: DISC_0_STRIP_10[pixel] = color; break;
      case 11: DISC_0_STRIP_11[pixel] = color; break;
      case 12: DISC_0_STRIP_12[pixel] = color; break;
      case 13: DISC_0_STRIP_13[pixel] = color; break;
      case 14: DISC_0_STRIP_14[pixel] = color; break;
      case 15: DISC_0_STRIP_15[pixel] = color; break;
    }
  } else if (disc == 1) {
    switch (strip) {
      case 0: DISC_1_STRIP_00[pixel] = color; break;
      case 1: DISC_1_STRIP_01[pixel] = color; break;
      case 2: DISC_1_STRIP_02[pixel] = color; break;
      case 3: DISC_1_STRIP_03[pixel] = color; break;
      case 4: DISC_1_STRIP_04[pixel] = color; break;
      case 5: DISC_1_STRIP_05[pixel] = color; break;
      case 6: DISC_1_STRIP_06[pixel] = color; break;
      case 7: DISC_1_STRIP_07[pixel] = color; break;
      case 8: DISC_1_STRIP_08[pixel] = color; break;
      case 9: DISC_1_STRIP_09[pixel] = color; break;
      case 10: DISC_1_STRIP_10[pixel] = color; break;
      case 11: DISC_1_STRIP_11[pixel] = color; break;
      case 12: DISC_1_STRIP_12[pixel] = color; break;
      case 13: DISC_1_STRIP_13[pixel] = color; break;
      case 14: DISC_1_STRIP_14[pixel] = color; break;
      case 15: DISC_1_STRIP_15[pixel] = color; break;
    }
  } else if (disc == 2) {
    switch (strip) {
      case 0: DISC_2_STRIP_00[pixel] = color; break;
      case 1: DISC_2_STRIP_01[pixel] = color; break;
      case 2: DISC_2_STRIP_02[pixel] = color; break;
      case 3: DISC_2_STRIP_03[pixel] = color; break;
      case 4: DISC_2_STRIP_04[pixel] = color; break;
      case 5: DISC_2_STRIP_05[pixel] = color; break;
      case 6: DISC_2_STRIP_06[pixel] = color; break;
      case 7: DISC_2_STRIP_07[pixel] = color; break;
      case 8: DISC_2_STRIP_08[pixel] = color; break;
      case 9: DISC_2_STRIP_09[pixel] = color; break;
      case 10: DISC_2_STRIP_10[pixel] = color; break;
      case 11: DISC_2_STRIP_11[pixel] = color; break;
      case 12: DISC_2_STRIP_12[pixel] = color; break;
      case 13: DISC_2_STRIP_13[pixel] = color; break;
      case 14: DISC_2_STRIP_14[pixel] = color; break;
      case 15: DISC_2_STRIP_15[pixel] = color; break;
    }
  } else if (disc == 3) {
    switch (strip) {
      case 0: DISC_3_STRIP_00[pixel] = color; break;
      case 1: DISC_3_STRIP_01[pixel] = color; break;
      case 2: DISC_3_STRIP_02[pixel] = color; break;
      case 3: DISC_3_STRIP_03[pixel] = color; break;
      case 4: DISC_3_STRIP_04[pixel] = color; break;
      case 5: DISC_3_STRIP_05[pixel] = color; break;
      case 6: DISC_3_STRIP_06[pixel] = color; break;
      case 7: DISC_3_STRIP_07[pixel] = color; break;
      case 8: DISC_3_STRIP_08[pixel] = color; break;
      case 9: DISC_3_STRIP_09[pixel] = color; break;
      case 10: DISC_3_STRIP_10[pixel] = color; break;
      case 11: DISC_3_STRIP_11[pixel] = color; break;
      case 12: DISC_3_STRIP_12[pixel] = color; break;
      case 13: DISC_3_STRIP_13[pixel] = color; break;
      case 14: DISC_3_STRIP_14[pixel] = color; break;
      case 15: DISC_3_STRIP_15[pixel] = color; break;
    }
  } else if (disc == 4) {
    switch (strip) {
      case 0: DISC_4_STRIP_00[pixel] = color; break;
      case 1: DISC_4_STRIP_01[pixel] = color; break;
      case 2: DISC_4_STRIP_02[pixel] = color; break;
      case 3: DISC_4_STRIP_03[pixel] = color; break;
      case 4: DISC_4_STRIP_04[pixel] = color; break;
      case 5: DISC_4_STRIP_05[pixel] = color; break;
      case 6: DISC_4_STRIP_06[pixel] = color; break;
      case 7: DISC_4_STRIP_07[pixel] = color; break;
      case 8: DISC_4_STRIP_08[pixel] = color; break;
      case 9: DISC_4_STRIP_09[pixel] = color; break;
      case 10: DISC_4_STRIP_10[pixel] = color; break;
      case 11: DISC_4_STRIP_11[pixel] = color; break;
      case 12: DISC_4_STRIP_12[pixel] = color; break;
      case 13: DISC_4_STRIP_13[pixel] = color; break;
      case 14: DISC_4_STRIP_14[pixel] = color; break;
      case 15: DISC_4_STRIP_15[pixel] = color; break;
    }
  } else if (disc == 5) {
    switch (strip) {
      case 0: DISC_5_STRIP_00[pixel] = color; break;
      case 1: DISC_5_STRIP_01[pixel] = color; break;
      case 2: DISC_5_STRIP_02[pixel] = color; break;
      case 3: DISC_5_STRIP_03[pixel] = color; break;
      case 4: DISC_5_STRIP_04[pixel] = color; break;
      case 5: DISC_5_STRIP_05[pixel] = color; break;
      case 6: DISC_5_STRIP_06[pixel] = color; break;
      case 7: DISC_5_STRIP_07[pixel] = color; break;
      case 8: DISC_5_STRIP_08[pixel] = color; break;
      case 9: DISC_5_STRIP_09[pixel] = color; break;
      case 10: DISC_5_STRIP_10[pixel] = color; break;
      case 11: DISC_5_STRIP_11[pixel] = color; break;
      case 12: DISC_5_STRIP_12[pixel] = color; break;
      case 13: DISC_5_STRIP_13[pixel] = color; break;
      case 14: DISC_5_STRIP_14[pixel] = color; break;
      case 15: DISC_5_STRIP_15[pixel] = color; break;
    }
  } else if (disc == 6) {
    switch (strip) {
      case 0: DISC_6_STRIP_00[pixel] = color; break;
      case 1: DISC_6_STRIP_01[pixel] = color; break;
      case 2: DISC_6_STRIP_02[pixel] = color; break;
      case 3: DISC_6_STRIP_03[pixel] = color; break;
      case 4: DISC_6_STRIP_04[pixel] = color; break;
      case 5: DISC_6_STRIP_05[pixel] = color; break;
      case 6: DISC_6_STRIP_06[pixel] = color; break;
      case 7: DISC_6_STRIP_07[pixel] = color; break;
      case 8: DISC_6_STRIP_08[pixel] = color; break;
      case 9: DISC_6_STRIP_09[pixel] = color; break;
      case 10: DISC_6_STRIP_10[pixel] = color; break;
      case 11: DISC_6_STRIP_11[pixel] = color; break;
      case 12: DISC_6_STRIP_12[pixel] = color; break;
      case 13: DISC_6_STRIP_13[pixel] = color; break;
      case 14: DISC_6_STRIP_14[pixel] = color; break;
      case 15: DISC_6_STRIP_15[pixel] = color; break;
    }
  } else {
    switch (strip) {
      case 0: DISC_7_STRIP_00[pixel] = color; break;
      case 1: DISC_7_STRIP_01[pixel] = color; break;
      case 2: DISC_7_STRIP_02[pixel] = color; break;
      case 3: DISC_7_STRIP_03[pixel] = color; break;
      case 4: DISC_7_STRIP_04[pixel] = color; break;
      case 5: DISC_7_STRIP_05[pixel] = color; break;
      case 6: DISC_7_STRIP_06[pixel] = color; break;
      case 7: DISC_7_STRIP_07[pixel] = color; break;
      case 8: DISC_7_STRIP_08[pixel] = color; break;
      case 9: DISC_7_STRIP_09[pixel] = color; break;
      case 10: DISC_7_STRIP_10[pixel] = color; break;
      case 11: DISC_7_STRIP_11[pixel] = color; break;
      case 12: DISC_7_STRIP_12[pixel] = color; break;
      case 13: DISC_7_STRIP_13[pixel] = color; break;
      case 14: DISC_7_STRIP_14[pixel] = color; break;
      case 15: DISC_7_STRIP_15[pixel] = color; break;
    }
  }
}
