#include <Arduino.h>

class Logic{
public:
    static const int lengthListInter = 3;
    static int Integral[lengthListInter][2];
    static int median[5];
    static double addInter(int left, int right);
    static int sign(double value);
    static int minValue(int x, int y);
    static bool isSpeedNull(byte currentValue);
};