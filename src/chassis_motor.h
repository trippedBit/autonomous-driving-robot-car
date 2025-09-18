#ifndef CHASSIS_MOTOR_H
#define CHASSIS_MOTOR_H

#ifndef UNIT_TESTING
#include <Arduino.h>
#endif // UNIT_TESTING

#include "configuration.h"

class ChassisMotor
{
private:
    int _enablePin;
    int _forwardPin;
    int _backwardPin;

public:
    enum MovementDirection
    {
        STOP = 0,
        FORWARD = 1,
        BACKWARD = 2
    };
    ChassisMotor(int enablePin,
                 int forwardPin,
                 int backwardPin);
    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/15
    int setMovementDirection(MovementDirection direction);
};

#endif // CHASSIS_MOTOR_H