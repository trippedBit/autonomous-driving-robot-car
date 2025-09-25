#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <math.h>
#include <string>

#include "configuration.h"
#include "chassis_motor.h"

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/14
std::string applyRandomDirectionAndSpeed(ChassisMotor leftMotor,
                                         ChassisMotor rightMotor,
                                         int directionAngle,
                                         int velocityPWM);

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/32
bool obstacleDetection(ChassisMotor leftMotor,
                       ChassisMotor rightMotor,
                       int unittestMeasuredDistanceMillimeter = 0);

#endif // MOTOR_CONTROL_H