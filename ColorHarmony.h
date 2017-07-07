#ifndef ColorHarmony_h
#define ColorHarmony_h

#include <math.h>

class ColorHarmony {
public:

  static float* complementary(float hue) {
    float* colors = new float[2];
    colors[0] = hue;
    colors[1] = 1 - hue;
    return colors;
  }
  
  static float* analogous (float hue, float angle) {
    float* colors = new float[3];
    colors[0] = hue;
    colors[1] = hue + angle;
    colors[2] = hue - angle;
    if (colors[1] < 0)
      colors[1] = 1 + colors[1];
    else if (colors[1] > 1)
      colors[1] = 1 - colors[1];
    if (colors[2] < 0)
      colors[2] = 1 + colors[2];
    else if (colors[2] > 1)
      colors[2] = 1 - colors[2];
    return colors;
  }

  static float* splitComplementary (float hue, float angle) {
    return analogous(hue, angle + 1.0/2.0);
  }

  static float* triad (float hue) {
    return analogous(hue, 1.0/3.0);
  }
};

#endif //ColorHarmony_h

