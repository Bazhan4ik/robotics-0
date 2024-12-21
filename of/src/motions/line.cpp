#include "main.h"


float prevError = 0;
float lateralPID(const float error) {
  float kP = 5;
  float kD = 50;


  const float derivative = error - prevError;
  prevError = error;

  return error * kP + derivative * kD;
}
float prevErrorAng = 0;
float angularPID(const float error) {
  float kP = 5;
  float kD = 50;


  const float derivative = error - prevErrorAng;
  prevErrorAng = error;

  return error * kP + derivative * kD;
}

void lateralPIDreset() {
  prevError = 0;
}
void angularPIDreset() {
  prevError = 0;
}






