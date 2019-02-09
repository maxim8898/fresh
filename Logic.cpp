#include <Arduino.h>
#include "Logic.h"
#include "Motor.h"
#include "Servos.h"
#include "Speedometer.h"
#include "config.h"

int Logic::Integral[Logic::lengthListInter][2];
int Logic::median[5] = {0};

bool Logic::init() {
  Motor::init();
  Servos::init();
  Speedometer::init();
  Serial.begin(9600);
}

void Logic::drive(int longTime, int speed, int angle) {
  unsigned long time = millis();
  while((millis() - time) < longTime) {
    Motor::setSpeed(speed);
    Servos::setAngle(angle);
  }
  Motor::setSpeed(SPEED_ZERO);
  Servos::setAngle(90);
}

double Logic::addInter(int left, int right) {
  for (int i = lengthListInter - 1; i > 0; i--) {
    Logic::Integral[i][0] = Logic::Integral[i - 1][0];
    Logic::Integral[i][1] = Logic::Integral[i - 1][1];
  }
  Logic::Integral[0][0] = left;
  Logic::Integral[0][1] = right;
  int lInter = 0;
  int rInter = 0;
  for (int i = 0; i < Logic::lengthListInter; i++) {
    lInter += Logic::Integral[i][0];
    rInter += Logic::Integral[i][1];
  }
  return rInter / lInter;
}

int Logic::sign(double value) {
  if (value >= 0) return 1;
  else return -1;
}

int Logic::minValue(int x, int y) {
  if (x <= y) return x;
  else return y;
}

bool Logic::isSpeedNull(byte currentValue) {  ////???????????????????????
  int summ = 0;
  for (byte i = 0; i < 5; i++) {
    summ += Logic::median[i];
  }
  if (summ == 0)
    return true;
  else 
    return false;
}
