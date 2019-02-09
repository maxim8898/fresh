#include <Arduino.h>

class Logic{
public:
    static const int lengthListInter = 3;
    static int Integral[lengthListInter][2];
    static int median[5];
    static bool init();
    static void drive(int longTime, int speed, int angle);
    static double addInter(int left, int right);
    static int sign(double value);
    static int minValue(int x, int y);
    static bool isSpeedNull(byte currentValue);
};
