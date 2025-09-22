#include "self_check.h"

SelfCheck::SelfCheck()
{
    // nothing todo
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/19
// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/29
bool SelfCheck::selfCheck(ChassisMotor leftMotor,
                          ChassisMotor rightMotor,
                          bool unittestForceFailLeftMotor,
                          bool unittestForceFailRightMotor)
{
    // Perform self-check routines here
    // Return true if all checks pass, false otherwise
    leftMotorCheck = false;
    leftMotorForwardPinState = leftMotor.getDirectionPinState(ChassisMotor::FORWARD_PIN);
    leftMotorBackwardPinState = leftMotor.getDirectionPinState(ChassisMotor::BACKWARD_PIN);
    if (leftMotorForwardPinState == 0 &&
        leftMotorBackwardPinState == 0)
    {
#ifndef UNIT_TESTING
        Serial.println("Left motor check passed");
#endif // UNIT_TESTING
        leftMotorCheck = true;
    }
    else
    {
#ifndef UNIT_TESTING
        Serial.println("Left motor check failed");
        Serial.print("FORWARD_PIN state | BACKWARD_PIN state: ");
        Serial.print(leftMotorForwardPinState);
        Serial.print(" | ");
        Serial.println(leftMotorBackwardPinState);
#endif // UNIT_TESTING
    }

    bool rightMotorCheck = false;
    rightMotorForwardPinState = rightMotor.getDirectionPinState(ChassisMotor::FORWARD_PIN);
    rightMotorBackwardPinState = rightMotor.getDirectionPinState(ChassisMotor::BACKWARD_PIN);
    if (rightMotorForwardPinState == 0 &&
        rightMotorBackwardPinState == 0)
    {
#ifndef UNIT_TESTING
        Serial.println("Right motor check passed");
#endif // UNIT_TESTING
        rightMotorCheck = true;
    }
    else
    {
#ifndef UNIT_TESTING
        Serial.println("Right motor check failed");
        Serial.print("FORWARD_PIN state | BACKWARD_PIN state: ");
        Serial.print(rightMotorForwardPinState);
        Serial.print(" | ");
        Serial.println(rightMotorBackwardPinState);
#endif // UNIT_TESTING
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

    return SELF_CHECK_PASSED = leftMotorCheck &&
                               rightMotorCheck;
}