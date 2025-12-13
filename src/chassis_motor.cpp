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

    pinMode(_enablePin, OUTPUT);
    analogWrite(_enablePin, 0); // Disable motor at startup
    pinMode(_forwardPin, OUTPUT);
    digitalWrite(_forwardPin, LOW); // Ensure motor is not moving at startup
    pinMode(_backwardPin, OUTPUT);
    digitalWrite(_backwardPin, LOW); // Ensure motor is not moving at startup
}

ChassisMotor::MovementDirection ChassisMotor::getCurrentDirection()
{
    MovementDirection returnValue = INVALID_DIRECTION;
    int forwardPinState = getDirectionPinState(FORWARD_PIN);
    int backwardPinState = getDirectionPinState(BACKWARD_PIN);

    std::cout << "Forward pin state: " << std::to_string(forwardPinState) << std::endl;
    std::cout << "Backward pin state: " << std::to_string(backwardPinState) << std::endl;

    if (forwardPinState == HIGH && backwardPinState == LOW)
    {
        returnValue = FORWARD_DIRECTION;
    }
    else if (forwardPinState == LOW && backwardPinState == HIGH)
    {
        returnValue = BACKWARD_DIRECTION;
    }

    return returnValue;
}

int ChassisMotor::getDirectionPinNumber(ControlPin pin)
{
    if (pin == FORWARD_PIN)
    {
        return _forwardPin;
    }
    else if (pin == BACKWARD_PIN)
    {
        return _backwardPin;
    }

    return -1;
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
    MovementDirection returnValue = ERROR_DIRECTION; // Default to error

    if (millis() >= 10000)
    {
        Serial.print("Setting pins ");
        Serial.print(_forwardPin);
        Serial.print(" / ");
        Serial.print(_backwardPin);
        Serial.print(" to ");

        switch (direction)
        {
        case STOP_DIRECTION:
            Serial.println("LOW / LOW");
            digitalWrite(_forwardPin, LOW);
            digitalWrite(_backwardPin, LOW);

            _directionBeforeStop = getCurrentDirection(); // Store last direction before stop
            returnValue = STOP_DIRECTION;
            break;
        case FORWARD_DIRECTION:

            Serial.println("HIGH / LOW");
            digitalWrite(_forwardPin, HIGH);
            digitalWrite(_backwardPin, LOW);

            returnValue = FORWARD_DIRECTION;
            break;
        case BACKWARD_DIRECTION:

            Serial.println("LOW / HIGH");
            digitalWrite(_forwardPin, LOW);
            digitalWrite(_backwardPin, HIGH);

            returnValue = BACKWARD_DIRECTION;
            break;
        default:
            // Invalid direction, stop the motor as a safety measure

            Serial.println("LOW / LOW (invalid direction)");
            digitalWrite(_forwardPin, LOW);
            digitalWrite(_backwardPin, LOW);

            returnValue = INVALID_DIRECTION;
            break;
        }
    }

    return returnValue;
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/46
int ChassisMotor::setMovementDirectionToDirectionBeforeStop()
{
    if (getCurrentDirection() != STOP_DIRECTION)
    {
        return ERROR_DIRECTION; // Can only set to direction before stop if currently stopped
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