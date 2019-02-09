#include <SharpIR.h>
#include <Arduino.h>
#include <Servo.h>
#include <Sensors.h>
#include <config.h>

int Sensors::L;
int Sensors::L0;
int Sensors::R;
int Sensors::R0;
int Sensors::median[3][4] = {0};

SharpIR SharpL0(LEFT0,1080);
SharpIR SharpR0(RIGHT0,1080);
SharpIR SharpL(LEFT,20150);
SharpIR SharpR(RIGHT,20150);

/**
 * Reculculation function for IR sensors.
 */
void Sensors::recalculation(){
  L0 = constrain(medianFilter(SharpL0.distance(),0), 7, 80);
  R0 = constrain(medianFilter(SharpR0.distance(),1), 7, 80);
  R = constrain(medianFilter(SharpR.distance(),2), 15, 120);
  L = constrain(medianFilter(SharpL.distance(),3), 15, 120);  
}

/**
 * Median filter.
 * 
 * @param int currentValue
 *   Current value.
 * @param int sensNum
 *   Sensor number.
 * 
 * @return int
 *   Median.
 */
int Sensors::medianFilter(int currentValue, int sensNum){
  for(int i = 1; i < 3; i++){
    median[i-1][sensNum] = median[i][sensNum];
  }
  median[2][sensNum] = currentValue;
  int maxVal = 0; int minVal = 0;
  for(int i=1; i<3; i++){
    if(median[i][sensNum] < median[minVal][sensNum]) minVal = i;
    if(median[i][sensNum] > median[maxVal][sensNum]) maxVal = i;
  }
  for(int i=0; i<3; i++){
    if(i!=maxVal && i!=minVal)
    return median[i][sensNum];
  } 
}
