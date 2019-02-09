#include <Servo.h>

class Sensors{
  public:
    static int L;
    static int L0;
    static int R;
    static int R0;
    static void recalculation();
  private:
    static int median[3][4];
    static int medianFilter(int currentValue, int sensNum);
    static int averageElem(int first, int second, int third);
};
