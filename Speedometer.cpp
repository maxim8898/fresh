#include <Arduino.h>
#include "Servo.h"
#include "config.h"
#include "Speedometer.h"
#include "Motor.h"
#include "PID.h"

unsigned long Speedometer::timeS;
unsigned long Speedometer::time;
int Speedometer::timePeriod;
int Speedometer::counter = 0;
int Speedometer::median[3] = {0}; 

/**
 * Initializing spedometer.
 */
void Speedometer::init(){
   attachInterrupt(0, change, FALLING);
   time = millis();
   timeS = millis();
   timePeriod = 1000;
}

/**
 * Get speed.
 */
double Speedometer::getSpeed(){
  if (millis()-time > 700) return 0;
  return (10/(timePeriod*0.001))*0.036;
}

/**
 * Attach interrupt method.
 */
void Speedometer::change(){
  
  if(millis()-time > MIN_TIME_PERIOD){
    if(counter%2 == 0){
      timePeriod = medianFilter((int)(millis()-timeS));
      timeS = millis();
    }
    counter++;
  }
  
  time = millis();
}

/**
 * Median filter.
 * 
 * @param int currentValue
 *   Current value.
 *   
 * @return int
 *   Median value.
 */
int Speedometer::medianFilter(int currentValue){
  for(byte i = 1; i < 3; i++){
    median[i-1] = median[i];
  }
  median[2] = currentValue;
  byte maxVal = 0; byte minVal = 0;
  for(byte i=1; i<3; i++){
    if(median[i] < median[minVal]) minVal = i;
    if(median[i] > median[maxVal]) maxVal = i;
  }
  for(byte i=0; i<3; i++){
    if(i!=maxVal && i!=minVal)
    return median[i];
  } 
}
