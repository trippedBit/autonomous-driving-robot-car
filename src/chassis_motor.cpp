#include "chassis_motor.h"

ChassisMotor::ChassisMotor(int enablePin,
                           int forwardPin,
                           int backwardPin,
                           float pwmFactor)
{
    _enablePin = enablePin;
    _forwardPin = forwardPin;
    _backwardPin = backwardPin;
    _pwmFactor = pwmFactor; // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/36

#ifndef UNIT_TESTING
    pinMode(_enablePin, OUTPUT);
    analogWrite(_enablePin, 0); // Disable motor at startup
    pinMode(_forwardPin, OUTPUT);
    digitalWrite(_forwardPin, LOW); // Ensure motor is not moving at startup
    pinMode(_backwardPin, OUTPUT);
    digitalWrite(_backwardPin, LOW); // Ensure motor is not moving at startup
#endif                               // UNIT_TESTING
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/18
int ChassisMotor::getEnablePinAnalogValue()
{
#ifndef UNIT_TESTING
    return analogRead(_enablePin);
#else
    return 0;
#endif
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/18
int ChassisMotor::getDirectionPinState(ControlPin pin)
{
    int pinState = -1; // Default to error

    int pinToCheck = -1; // Invalid pin
    switch (pin)
    {
    case FORWARD:
        pinToCheck = _forwardPin;
        break;
    case BACKWARD:
        pinToCheck = _backwardPin;
        break;
    default:
        break;
    }

    if (pinToCheck != -1)
    {
#ifndef UNIT_TESTING
        pinState = digitalRead(pinToCheck);
#else
        pinState = 0; // Simulate LOW in unit testing mode
#endif // UNIT_TESTING
    }

    return pinState;
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

// Requirement: None
float ChassisMotor::setVelocityPWM(int velocityPWM)
{
    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/36)
#ifndef UNIT_TESTING
    Serial.print("Given PWM: ");
    Serial.println(velocityPWM);
#endif // UNIT_TESTING

    float pwmToApply = velocityPWM * _pwmFactor;
    if (pwmToApply > 255)
    {
        pwmToApply = 255;
    }
    else if (pwmToApply < 0)
    {
        pwmToApply = 0;
    }

#ifndef UNIT_TESTING
    Serial.print("Adjusted PWM (factor ");
    Serial.print(_pwmFactor);
    Serial.print("): ");
    Serial.println(pwmToApply);

    analogWrite(_enablePin, pwmToApply);
#endif // UNIT_TESTING

    return pwmToApply;
}