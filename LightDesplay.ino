const int RPin = A16;
const int GPin = A17;
const int BPin = A18;

// Ideally should be values between 0 and 1 inclusive
float RVal = 0;
float GVal = 0;
float BVal = 0;

long loop_tms = 10000;
long start_time;


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
  
  RVal = ( cos(float(dt % loop_tms)/loop_tms * 2*PI         ) + 1) / 2;
  GVal = ( cos(float(dt % loop_tms)/loop_tms * 2*PI + 2*PI/3) + 1) / 2;
  BVal = ( cos(float(dt % loop_tms)/loop_tms * 2*PI + 4*PI/3) + 1) / 2;

  analogWrite(RPin, rerange(RVal));
  analogWrite(GPin, rerange(GVal));
  analogWrite(BPin, rerange(BVal));
}

// Input  [0,1] float
// Output [0,255] int
int rerange(float i) {
  return constrain(int(i * 255), 0, 255);
}


