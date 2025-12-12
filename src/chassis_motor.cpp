#include "chassis_motor.h"
#include "mocks.h"

ChassisMotor::ChassisMotor(int enablePin,
                           int forwardPin,
                           int backwardPin,
                           float pwmFactor)
{
    _enablePin = enablePin;
    _forwardPin = forwardPin;
    _backwardPin = backwardPin;
    _pwmFactor = pwmFactor; // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/36

    _currentDirection = INVALID; // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/46

    pinMode(_enablePin, OUTPUT);
    analogWrite(_enablePin, 0); // Disable motor at startup
    pinMode(_forwardPin, OUTPUT);
    digitalWrite(_forwardPin, LOW); // Ensure motor is not moving at startup
    pinMode(_backwardPin, OUTPUT);
    digitalWrite(_backwardPin, LOW); // Ensure motor is not moving at startup
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/18
int ChassisMotor::getEnablePinAnalogValue()
{
    return analogRead(_enablePin);
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/18
int ChassisMotor::getDirectionPinState(ControlPin pin)
{
    int pinState = -1; // Default to error

    int pinToCheck = -1; // Invalid pin
    switch (pin)
    {
    case FORWARD_PIN:
        pinToCheck = _forwardPin;
        break;
    case BACKWARD_PIN:
        pinToCheck = _backwardPin;
        break;
    default:
        break;
    }

    if (pinToCheck != -1)
    {
        pinState = digitalRead(pinToCheck);
    }

    return pinState;
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/15
// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/46
int ChassisMotor::setMovementDirection(MovementDirection direction)
{
    MovementDirection returnValue = ERROR; // Default to error

    if (millis() >= 10000)
    {
        Serial.print("Setting pins ");
        Serial.print(_forwardPin);
        Serial.print(" / ");
        Serial.print(_backwardPin);
        Serial.print(" to ");

        switch (direction)
        {
        case STOP:
            Serial.println("LOW / LOW");
            digitalWrite(_forwardPin, LOW);
            digitalWrite(_backwardPin, LOW);

            _directionBeforeStop = _currentDirection; // Store last direction before stop
            returnValue = STOP;
            break;
        case FORWARD:

            Serial.println("HIGH / LOW");
            digitalWrite(_forwardPin, HIGH);
            digitalWrite(_backwardPin, LOW);

            returnValue = FORWARD;
            break;
        case BACKWARD:

            Serial.println("LOW / HIGH");
            digitalWrite(_forwardPin, LOW);
            digitalWrite(_backwardPin, HIGH);

            returnValue = BACKWARD;
            break;
        default:
            // Invalid direction, stop the motor as a safety measure

            Serial.println("LOW / LOW (invalid direction)");
            digitalWrite(_forwardPin, LOW);
            digitalWrite(_backwardPin, LOW);

            returnValue = INVALID;
            break;
        }
    }

    _currentDirection = returnValue;

    return returnValue;
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/46
int ChassisMotor::setMovementDirectionToDirectionBeforeStop()
{
    if (_currentDirection != STOP)
    {
        return ERROR; // Can only set to direction before stop if currently stopped
    }
    return setMovementDirection(_directionBeforeStop);
}

// Requirement: None
float ChassisMotor::setVelocityPWM(int velocityPWM)
{
    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/36)
    Serial.print("Given PWM: ");
    Serial.println(velocityPWM);

    float pwmToApply = velocityPWM * _pwmFactor;
    if (pwmToApply > 255)
    {
        pwmToApply = 255;
    }
    else if (pwmToApply < 0)
    {
        pwmToApply = 0;
    }

    Serial.print("Adjusted PWM (factor ");
    Serial.print(_pwmFactor);
    Serial.print("): ");
    Serial.println(pwmToApply);

    analogWrite(_enablePin, pwmToApply);

    return pwmToApply;
}