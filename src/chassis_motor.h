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
    enum ControlPin
    {
        ENABLE_PIN = 0,
        FORWARD_PIN = 1,
        BACKWARD_PIN = 2
    };
    enum MovementDirection
    {
        STOP = 0,
        FORWARD = 1,
        BACKWARD = 2
    };
    ChassisMotor(int enablePin,
                 int forwardPin,
                 int backwardPin);

    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/18
    int getDirectionPinState(ControlPin pin);
    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/18
    int getEnablePinAnalogValue();
    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/15
    int setMovementDirection(MovementDirection direction);
    // Requirement: None
    void setVelocityPWM(int velocityPWM);
};

#endif // CHASSIS_MOTOR_H