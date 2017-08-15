#include <HSBColor.h>
#include "Microphone.h"
#include "RGB_Led.h"
#include "ColorHarmony.h"

// Constants
const int freqBassMid = 250;    //hz
const int freqMidTreble = 2000; //hz

// Pin Variables
const int micPin = A1;
const int RPin1 = 10;
const int GPin1 = 9;
const int BPin1 = 8;
const int RPin2 = 7;
const int GPin2 = 6;
const int BPin2 = 5;
const int RPin3 = 4;
const int GPin3 = 3;
const int BPin3 = 2;


// Microphone and Filters
Microphone mic;
float sample = 0;

// Led Variables
RGB_Led led1;
RGB_Led led2;
RGB_Led led3;

long loop_tms = 10000;
long startTime;

// Color Variables
// hsl and hsv are [0-1] rgb is [0-255]
float hue = 1;
float hsb1[]  = {1, 1, 1};
float hsb2[]  = {1, 1, 1};
float hsb3[]  = {1, 1, 1};
int rgb[]     = {255, 255, 255};
int rgb1[]    = {255, 255, 255};
int rgb2[]    = {255, 255, 255};
int rgb3[]    = {255, 255, 255};

void setup() {

  Serial.begin(9600);
//  while (!Serial) {}

  // Set Up Objects
  led1 = RGB_Led(RPin1, GPin1, BPin1);
  led2 = RGB_Led(RPin2, GPin2, BPin2);
  led3 = RGB_Led(RPin3, GPin3, BPin3);

  mic = Microphone(micPin);
  mic.calibrate();

  // Set Up Variables
  startTime = millis();
}

void loop() {
  long dt = millis() - startTime;

  // Read and filter the microphone
  sample = abs(mic.read());

  hue = (cos(float(dt % loop_tms) / loop_tms * 2 * PI) + 1) / 2;
  float* hues = ColorHarmony::triad(hue);

  // Assign Hue Values
  hsb1[0] = hues[0];
  hsb2[0] = hues[1];
  hsb3[0] = hues[2];

  // Assign Brightness valuse
  hsb1[2] = sample;
  hsb2[2] = sample;
  hsb3[2] = sample;
  
  // Convert over to the RGB space
  H2R_HSBtoRGBfloat(hsb1[0], hsb1[1], hsb1[2], rgb1);
  H2R_HSBtoRGBfloat(hsb2[0], hsb2[1], hsb2[2], rgb2);
  H2R_HSBtoRGBfloat(hsb3[0], hsb3[1], hsb3[2], rgb3);

  // Assign LED colors
  led1.setColor(rgb1);
  led2.setColor(rgb2);
  led3.setColor(rgb3);

  // Clean Up
  delete hues;
  hues = NULL;
}



