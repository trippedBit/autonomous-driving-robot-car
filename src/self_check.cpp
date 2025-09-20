#include "self_check.h"

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/18
// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/19
bool selfCheck(ChassisMotor leftMotor,
               ChassisMotor rightMotor,
               bool unittestForceFailLeftMotor,
               bool unittestForceFailRightMotor)
{
    // Perform self-check routines here
    // Return true if all checks pass, false otherwise
    bool leftMotorCheck = false;
    if (leftMotor.getEnablePinAnalogValue() == 0 &&
        leftMotor.getDirectionPinState(ChassisMotor::FORWARD_PIN) == 0 &&
        leftMotor.getDirectionPinState(ChassisMotor::BACKWARD_PIN) == 0)
    {
        leftMotorCheck = true;
    }

    bool rightMotorCheck = false;
    if (rightMotor.getEnablePinAnalogValue() == 0 &&
        rightMotor.getDirectionPinState(ChassisMotor::FORWARD_PIN) == 0 &&
        rightMotor.getDirectionPinState(ChassisMotor::BACKWARD_PIN) == 0)
    {
        rightMotorCheck = true;
    }

    if (unittestForceFailLeftMotor)
    {
        leftMotorCheck = false;
    }
    else if (unittestForceFailRightMotor)
    {
        rightMotorCheck = false;
    }

    return leftMotorCheck &&
           rightMotorCheck;
}