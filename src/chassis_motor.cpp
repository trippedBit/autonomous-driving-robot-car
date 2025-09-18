#include "chassis_motor.h"

ChassisMotor::ChassisMotor(int enablePin,
                           int forwardPin,
                           int backwardPin)
{
    _enablePin = enablePin;
    _forwardPin = forwardPin;
    _backwardPin = backwardPin;

#ifndef UNIT_TESTING
    pinMode(_enablePin, OUTPUT);
    analogWrite(_enablePin, 0); // Disable motor at startup
    pinMode(_forwardPin, OUTPUT);
    digitalWrite(_forwardPin, LOW); // Ensure motor is not moving at startup
    pinMode(_backwardPin, OUTPUT);
    digitalWrite(_backwardPin, LOW); // Ensure motor is not moving at startup
#endif                               // UNIT_TESTING
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/15
int ChassisMotor::setMovementDirection(MovementDirection direction)
{
    int returnValue = -1; // Default to error

#ifndef UNIT_TESTING
    Serial.print("Setting pins ");
    Serial.print(_forwardPin);
    Serial.print(" / ");
    Serial.print(_backwardPin);
    Serial.print(" to ");
#endif // UNIT_TESTING

    switch (direction)
    {
    case STOP:
#ifndef UNIT_TESTING
        Serial.println("LOW / LOW");
        digitalWrite(_forwardPin, LOW);
        digitalWrite(_backwardPin, LOW);
#endif // UNIT_TESTING
        returnValue = STOP;
        break;
    case FORWARD:
#ifndef UNIT_TESTING
        Serial.println("HIGH / LOW");
        digitalWrite(_forwardPin, HIGH);
        digitalWrite(_backwardPin, LOW);
#endif // UNIT_TESTING
        returnValue = FORWARD;
        break;
    case BACKWARD:
#ifndef UNIT_TESTING
        Serial.println("LOW / HIGH");
        digitalWrite(_forwardPin, LOW);
        digitalWrite(_backwardPin, HIGH);
#endif // UNIT_TESTING
        returnValue = BACKWARD;
        break;
    default:
// Invalid direction, stop the motor as a safety measure
#ifndef UNIT_TESTING
        Serial.println("LOW / LOW (invalid direction)");
        digitalWrite(_forwardPin, LOW);
        digitalWrite(_backwardPin, LOW);
#endif // UNIT_TESTING
        returnValue = -2;
        break;
    }

    return returnValue;
}