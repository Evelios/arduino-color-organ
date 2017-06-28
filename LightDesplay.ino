#include <HSBColor.h>

const int RPin = A16;
const int GPin = A17;
const int BPin = A18;

long loop_tms = 10000;
long start_time;

// hsl and hsv are [0-1] rgb is [0-255]
float hsb[] = {1, 1, 1};
int rgb[]   = {255, 255, 255};

void setup() {

  Serial.begin(9600);
  
  // Set Up LED Pins
  pinMode(RPin, OUTPUT);
  pinMode(GPin, OUTPUT);
  pinMode(BPin, OUTPUT);

  // Set Up Variables
  start_time = millis();

}

void loop() {
  long dt = millis() - start_time;
  
  hsb[0] = (cos(float(dt % loop_tms)/loop_tms * 2*PI) + 1) / 2;
  H2R_HSBtoRGBfloat(hsb[0], hsb[1], hsb[2], rgb);

  analogWrite(RPin, rgb[0]);
  analogWrite(GPin, rgb[1]);
  analogWrite(BPin, rgb[2]);
}

