#include <Arduino.h>
#include "Servo.h"
#include "config.h"
#include "Motor.h"
#include "Servos.h"
#include "PID.h"

Servo Servos::servos;
short Servos::currentAngle;

/**
 * Initializing servos.
 */
void Servos::init(){
  servos.attach(9, 950, 2040);
  servos.write(90);
  currentAngle = 0;
}

/**
 * Set angle value.
 * 
 * @param short value
 *   Angle.
 */
void Servos::setAngle(short value){
  servos.write(90 + value); 
  currentAngle = value;
}

/**
 * Get angle value.
 * 
 * @return short
 *   Angle.
 */
short Servos::getAngle(){
  return currentAngle;
}
