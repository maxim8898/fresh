#include <Arduino.h>
#include <Servo.h>
#include "config.h"
#include "Motor.h"
#include "PID.h"

double PID::P;
double PID::I;
double PID::D;
double PID::prevI = 0;
double PID::prevError = 0;

/**
 * The function that computes speed via PID regulator.
 * 
 * @param int wantSpeed
 *   Desired speed.
 * 
 * @return int
 *   Speed value after PID regulator.
 */
int PID::computeSpeed(int wantSpeed){
  int currentError = wantSpeed - Motor::getSpeed();
  P = currentError * PID_P;
  I = currentError * PID_I + prevI;
  D = (currentError - prevError) * PID_D;
  prevI = I;
  prevError = currentError;
  int result = constrain(wantSpeed + trunc(P + I + D), 1300, 1650);
  return result;
}
