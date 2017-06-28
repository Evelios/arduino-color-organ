#ifndef RGB_LED_H
#define RGB_LED_H

class RGB_Led {

public:
  RGB_Led() {
    rp = -1;
    gp = -1;
    bp = -1;
  }

  RGB_Led(int rpin, int gpin, int bpin) {
    rp = rpin;
    gp = gpin;
    bp = bpin;

    pinMode(rp, OUTPUT);
    pinMode(gp, OUTPUT);
    pinMode(bp, OUTPUT);
  }

  void setColor(int r, int g, int b) {
    analogWrite(rp, r);
    analogWrite(gp, g);
    analogWrite(bp, b);
  }

private:
  int rp;
  int gp;
  int bp;
};

#endif //RGB_LED_H
