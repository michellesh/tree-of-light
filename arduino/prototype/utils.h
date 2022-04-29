float mapf(float value, float inMin, float inMax, float outMin, float outMax) {
  float percentage = (value - inMin) / (inMax - inMin);
  return outMin + (outMax - outMin) * percentage;
}

int oscillateLinear(int min, int max, uint16_t waveLength = 400) {
  int middle = (min + max) / 2;
  uint16_t x = ticks % waveLength;
  return x < waveLength / 4 ? map(x, 0, waveLength / 4, middle, max)
         : x < waveLength / 2
             ? map(x, waveLength / 4, waveLength / 2, max, middle)
         : x < waveLength * 3 / 4
             ? map(x, waveLength / 2, waveLength * 3 / 4, middle, min)
             : map(x, waveLength * 3 / 4, waveLength, min, middle);
}

float oscillate(float minValue, float maxValue, uint8_t waveLength = 50) {
  return mapf(sin((float)ticks * PI / waveLength), -1, 1, minValue, maxValue);
}

float sawtooth(float minValue, float maxValue, uint8_t waveLength = 50) {
  float t = (float)ticks / waveLength;
  return mapf(t - floor(t), 0, 1, minValue, maxValue);
}

float square(float minValue, float maxValue, uint8_t waveLength = 50) {
  return ticks % (waveLength * 2) < waveLength ? minValue : maxValue;
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
