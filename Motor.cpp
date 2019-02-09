#include <Arduino.h>
#include <Servo.h>
#include <math.h>
#include "config.h"
#include "Motor.h"
#include "PID.h"
#include "Speedometer.h"

Servo Motor::motor;

/**
 * Initialization function.
 */
void Motor::init(){
  motor.attach(MOTOR_PIN, 544, 2400);
  motor.writeMicroseconds(SPEED_ZERO);
  delay(3000);
}

/**
 * Set speed (in microseconds).
 * 
 * @param int speed
 *   Speed value.
 */
void Motor::setSpeed(int speed){
  motor.writeMicroseconds(/*PID::computeSpeed*/(speed));
}

/**
 * Set speed (in km/h).
 * 
 * @param float speed
 *   Speed value.
 */
void Motor::setSpeed(float speed){
  motor.writeMicroseconds(PID::computeSpeed(Motor::speedConverter(speed)));
}

/**
 * Convert from km/h to microseconds.
 * 0,1148x^4 - 1,964x^3 + 10,041x^2 - 8,8379x + 1546,7
 * 
 * @param float speed
 *   Speed in km/h.
 * 
 * @return int
 *   Speed in microseconds.
 */
int Motor::speedConverter(float speed){
  return trunc(pow(speed,4)*0.1148 - pow(speed,3)*1.964 + pow(speed,2)*10.041 - speed*8.8379 + 1546.7); 
}

/**
 * Get speed.
 * 
 * @return int
 *   Speed value.
 */
int Motor::getSpeed(){
  int currentSpeed = Motor::speedConverter((float)Speedometer::getSpeed());
  return trunc(currentSpeed);
}
