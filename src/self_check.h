#ifndef SELF_CHECK_H
#define SELF_CHECK_H

#include "chassis_motor.h"

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/19
bool selfCheck(ChassisMotor leftMotor,
               ChassisMotor rightMotor,
               bool unittestForceFailLeftMotor = false,
               bool unittestForceFailRightMotor = false);

#endif // SELF_CHECK_H