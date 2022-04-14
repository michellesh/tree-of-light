// Increments a value by incAmount
// if the value goes goes over maxValue, it wraps around starting at 0
uint16_t incWrap(uint16_t value, uint16_t maxValue, uint16_t incAmount = 1) {
  uint16_t newValue = value + incAmount;
  return newValue >= maxValue ? newValue - maxValue : newValue;
}

// Decrements a value by decAmount
// if the value goes under 0, it wraps around starting at maxValue
uint16_t decWrap(uint16_t value, uint16_t maxValue, uint16_t decAmount = 1) {
  uint16_t newValue = value - decAmount;
  return newValue < 0 ? newValue + maxValue : newValue;
}

float mapf(float value, float inMin, float inMax, float outMin, float outMax) {
  float percentage = (value - inMin) / (inMax - inMin);
  return outMin + (outMax - outMin) * percentage;
}

float oscillate(float minValue, float maxValue, uint8_t waveLength = 50) {
  return mapf(sin((float)ticks / waveLength), -1, 1, minValue, maxValue);
}

// This function is like 'triwave8', which produces a
// symmetrical up-and-down triangle sawtooth waveform, except that this
// function produces a triangle wave with a faster attack and a slower decay:
//
//     / \ 
//    /     \ 
//   /         \ 
//  /             \ 
//

uint8_t attackDecayWave8(uint8_t i) {
  if (i < 86) {
    return i * 3;
  } else {
    i -= 86;
    return 255 - (i + (i / 2));
  }
}
