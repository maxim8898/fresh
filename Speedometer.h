#include <Arduino.h>
#include <Servo.h>

class Speedometer{
public:
  static void init();
  static void change();
  static double getSpeed();
  static int medianFilter(int currentValue);
  static unsigned long time;
  static unsigned long timeS;
  static int timePeriod;
  static int counter;
  static int median[3];  
};
