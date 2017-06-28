#include <HSBColor.h>
#include "RGB_Led.h"

const int RPin = A16;
const int GPin = A17;
const int BPin = A18;

RGB_Led led;

long loop_tms = 10000;
long start_time;

// hsl and hsv are [0-1] rgb is [0-255]
float hsb[] = {1, 1, 1};
int rgb[]   = {255, 255, 255};

void setup() {

  Serial.begin(9600);

  led = RGB_Led(RPin, GPin, BPin);

  // Set Up Variables
  start_time = millis();

}

void loop() {
  long dt = millis() - start_time;
  
  hsb[0] = (cos(float(dt % loop_tms)/loop_tms * 2*PI) + 1) / 2;
  H2R_HSBtoRGBfloat(hsb[0], hsb[1], hsb[2], rgb);

  led.setColor(rgb[0], rgb[1], rgb[2]);
}

