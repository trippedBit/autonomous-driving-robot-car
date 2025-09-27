#ifndef CHASSIS_MOTOR_H
#define CHASSIS_MOTOR_H

#ifndef UNIT_TESTING
#include <Arduino.h>
#endif // UNIT_TESTING

#include "configuration.h"

class ChassisMotor
{
public:
    enum ControlPin
    {
        ENABLE_PIN = 0,
        FORWARD_PIN = 1,
        BACKWARD_PIN = 2
    };
    enum MovementDirection
    {
        INVALID = -2,
        ERROR = -1,
        STOP = 0,
        FORWARD = 1,
        BACKWARD = 2
    };
    ChassisMotor(int enablePin,
                 int forwardPin,
                 int backwardPin,
                 float pwmFactor = 1);

    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/18
    int getDirectionPinState(ControlPin pin);
    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/18
    int getEnablePinAnalogValue();
    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/15
    int setMovementDirection(MovementDirection direction);
    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/46
    int setMovementDirectionToDirectionBeforeStop();
    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/36
    float setVelocityPWM(int velocityPWM);

private:
    int _enablePin;
    int _forwardPin;
    int _backwardPin;
    float _pwmFactor; // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/36

    MovementDirection _currentDirection;    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/46
    MovementDirection _directionBeforeStop; // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/46
};

#endif // CHASSIS_MOTOR_H