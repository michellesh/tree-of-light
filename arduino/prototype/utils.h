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

float oscillate(float minValue, float maxValue) {
  return mapf(sin((float)ticks / 50), -1, 1, minValue, maxValue);
}
