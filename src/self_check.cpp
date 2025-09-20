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
#ifndef UNIT_TESTING
        Serial.println("Left motor check passed");
#endif // UNIT_TESTING
        leftMotorCheck = true;
    }

    bool rightMotorCheck = false;
    if (rightMotor.getEnablePinAnalogValue() == 0 &&
        rightMotor.getDirectionPinState(ChassisMotor::FORWARD_PIN) == 0 &&
        rightMotor.getDirectionPinState(ChassisMotor::BACKWARD_PIN) == 0)
    {
#ifndef UNIT_TESTING
        Serial.println("Right motor check passed");
#endif // UNIT_TESTING
        rightMotorCheck = true;
    }

    if (unittestForceFailLeftMotor)
    {
#ifndef UNIT_TESTING
        Serial.println("Forcing left motor check fail");
#endif // UNIT_TESTING
        leftMotorCheck = false;
    }
    else if (unittestForceFailRightMotor)
    {
#ifndef UNIT_TESTING
        Serial.println("Forcing right motor check fail");
#endif // UNIT_TESTING
        rightMotorCheck = false;
    }

    return leftMotorCheck &&
           rightMotorCheck;
}