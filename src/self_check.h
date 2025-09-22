#ifndef SELF_CHECK_H
#define SELF_CHECK_H

#include "chassis_motor.h"

class SelfCheck
{
public:
    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/29
    bool SELF_CHECK_PASSED = false;

    bool leftMotorCheck = false;
    int leftMotorForwardPinState = -1;
    int leftMotorBackwardPinState = -1;

    bool rightMotorCheck = false;
    int rightMotorForwardPinState = -1;
    int rightMotorBackwardPinState = -1;

    SelfCheck();

    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/19
    bool selfCheck(ChassisMotor leftMotor,
                   ChassisMotor rightMotor,
                   bool unittestForceFailLeftMotor = false,
                   bool unittestForceFailRightMotor = false);
};

#endif // SELF_CHECK_H