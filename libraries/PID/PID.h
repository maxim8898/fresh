#include <Arduino.h>
#include <Servo.h>

class PID{
  public:
    static int computeSpeed(int wantSpeed);
  private:
    static double P;
    static double I;
    static double D;
    static double prevI;
    static double prevError;
    static int wantSpeed;
};
