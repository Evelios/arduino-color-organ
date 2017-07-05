#ifndef Microphone_h
#define Microphone_h

class Microphone {
public:
  Microphone() : Microphone(-1) { }
  Microphone(int micPin) {
    pin = micPin;
    sampleWindow = 50;
    sample = 0;
    s_index = 1;
    mic_avg = 1024/2;
    signalMin = 1024;
    signalMax = 0;
    pinMode(pin, INPUT);
  }

  // Spend some time to calibrate the microphone peak values and average value
  void calibrate() {
    long startTime = millis();
    while (millis() - startTime < sampleWindow) {
      sample = analogRead(pin);
      if (sample < 1024) {
        mic_avg = rollAvg(mic_avg, sample, s_index);
        if (sample > signalMax) {
          signalMax = sample;
        } else if (sample < signalMin) {
          signalMin = sample;
        }
        s_index++;
      }
    }
    peak = max(int(mic_avg) - signalMin, signalMax - int(mic_avg));
  }

  // Return a reading from the microphone in the range -1 to 1
  float read() {
    sample = analogRead(pin);
    if (sample > 1024) {
      sample = 1024;
    }

    // Update Peaks
    if (sample > signalMax) {
      signalMax = sample;
      peak = max(int(mic_avg) - signalMin, signalMax - int(mic_avg));
    } else if (sample < signalMin) {
      signalMin = sample;
      peak = max(int(mic_avg) - signalMin, signalMax - int(mic_avg));
    }
    return remap(sample, int(mic_avg) - peak, int(mic_avg) + peak, -1, 1);
  }

private:
  // Calculates a rolling average for a sample where the number of samples are known
  float rollAvg(float avg, float sample, float n) {
    return avg - avg/n + sample/n;
  }

  // Remap (adjust) a value from one range to another range
  float remap(float value, float low1, float high1, float low2, float high2) {
    return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
  }

  int pin;
  unsigned int sampleWindow;
  int sample;
  float mic_avg;
  int signalMin;
  int signalMax;
  int peak;
  int s_index;
};

#endif //Microphone_h
