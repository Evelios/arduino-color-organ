#include <Filters.h>
#include <HSBColor.h>
#include "Microphone.h"
#include "RGB_Led.h"

// Pin Variables
const int micPin = A1;
const int RPin = A16;
const int GPin = A17;
const int BPin = A18;

// Microphone and Filters
Microphone mic;

// Led Variables
RGB_Led led;

long loop_tms = 10000;
long startTime;

// Color Variables
// hsl and hsv are [0-1] rgb is [0-255]
float hsb[] = {1, 1, 1};
int rgb[]   = {255, 255, 255};

void setup() {

  Serial.begin(9600);
  while(!Serial) {}

  // Set Up Objects
  led = RGB_Led(RPin, GPin, BPin);  
  mic = Microphone(micPin);
  mic.calibrate();

  // Set Up Variables
  startTime = millis();
}

void loop() {  
  long dt = millis() - startTime;
  
  hsb[0] = (cos(float(dt % loop_tms)/loop_tms * 2*PI) + 1) / 2;
  H2R_HSBtoRGBfloat(hsb[0], hsb[1], hsb[2], rgb);

  Serial.println(mic.read());

  led.setColor(rgb[0], rgb[1], rgb[2]);
}



