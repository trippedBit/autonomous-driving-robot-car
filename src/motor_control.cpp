#include "motor_control.h"

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/14
std::string applyRandomDirectionAndSpeed(ChassisMotor leftMotor,
                                         ChassisMotor rightMotor,
                                         int directionAngle,
                                         int velocityPWM)
{
    // 1. stop both motors
    leftMotor.setVelocityPWM(0);
    rightMotor.setVelocityPWM(0);

#ifndef UNIT_TESTING
    delay(5000);
#endif // UNIT_TESTING

    // 2. perform turn
    // 2.1. if negative : left turn; if positive: right turn
    // 2.2. enable needed motor for x seconds (how to calculate?) with VELOCITY_MIN
    // 2.3. stop needed motor
    float radians = abs(M_PI / 180 * directionAngle);
#ifndef UNIT_TESTING
    Serial.print("Calculated radians: ");
    Serial.println(radians);
#endif // UNIT_TESTING

    float distanceMM = WHEEL_DISTANCE_MM * radians;
#ifndef UNIT_TESTING
    Serial.print("Calculated distance: ");
    Serial.println(distanceMM);
#endif // UNIT_TESTING

    float velocityMMPS = WHEEL_RPS_VELOCITY_MIN * WHEEL_CIRCUMFERENCE_MM;
#ifndef UNIT_TESTING
    Serial.print("Calculated velocity [mm/s]: ");
    Serial.println(velocityMMPS);
#endif // UNIT_TESTING

    float activeMilliSeconds = (distanceMM / velocityMMPS) * 1000;
#ifndef UNIT_TESTING
    Serial.print("Calculated activeMilliSeconds [ms]: ");
    Serial.println(activeMilliSeconds);
#endif // UNIT_TESTING

    if (directionAngle < 0)
    {
// left turn, right motor needed
#ifndef UNIT_TESTING
        Serial.print("Activating right motor for milliseconds with PWM: ");
        Serial.print(activeMilliSeconds);
        Serial.print(" | ");
        Serial.println(VELOCITY_MIN);
#endif // UNIT_TESTING
        rightMotor.setVelocityPWM(VELOCITY_MIN);
#ifndef UNIT_TESTING
        delay(activeMilliSeconds);
#endif // UNIT_TESTING
        rightMotor.setVelocityPWM(0);
    }
    else
    {
// right turn, left motor needed
#ifndef UNIT_TESTING
        Serial.print("Activating left motor for milliseconds with PWM: ");
        Serial.print(activeMilliSeconds);
        Serial.print(" | ");
        Serial.println(VELOCITY_MIN);
#endif // UNIT_TESTING
        leftMotor.setVelocityPWM(VELOCITY_MIN);
#ifndef UNIT_TESTING
        delay(activeMilliSeconds);
#endif // UNIT_TESTING
        leftMotor.setVelocityPWM(0);
    }

#ifndef UNIT_TESTING
    delay(5000);
#endif // UNIT_TESTING

// 3. enable both motors mith new velocity
#ifndef UNIT_TESTING
    Serial.print("Activating both motors with PWM: ");
    Serial.println(VELOCITY_MIN);
#endif // UNIT_TESTING
    leftMotor.setVelocityPWM(velocityPWM);
    rightMotor.setVelocityPWM(velocityPWM);

    return "radians [rad]: " + std::to_string(radians) + " | " +
           "distanceMM [mm]: " + std::to_string(distanceMM) + " | " +
           "circumference [MM]: " + std::to_string(WHEEL_CIRCUMFERENCE_MM) + " | " +
           "revolutions per second [rps]: " + std::to_string(WHEEL_RPS_VELOCITY_MIN) + " | " +
           "velocity [mm/s]: " + std::to_string(velocityMMPS) + " | " +
           "activeMilliSeconds [ms]: " + std::to_string(activeMilliSeconds);
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/46
bool obstacleDetection(ChassisMotor leftMotor,
                       ChassisMotor rightMotor,
                       int unittestMeasuredDistanceMillimeter)
{
#ifndef UNIT_TESTING
    pinMode(SENSOR_TRIGGER_PIN, OUTPUT);
    digitalWrite(SENSOR_TRIGGER_PIN, LOW); // Set pin low for a clean start when setting high
    delayMicroseconds(SENSOR_TRIGGER_PIN_LOW_TIME_MICROSECONDS);
    digitalWrite(SENSOR_TRIGGER_PIN, HIGH);                       // Start trigger
    delayMicroseconds(SENSOR_TRIGGER_PIN_HIGH_TIME_MICROSECONDS); // Trigger must be high for at least 10 microseconds.
    digitalWrite(SENSOR_TRIGGER_PIN, LOW);

    // Get echo pulse
    pinMode(SENSOR_ECHO_PIN, INPUT);
    float pulseLengthMicroseconds = pulseIn(SENSOR_ECHO_PIN, HIGH);
    Serial.print("Measured pulse length [µs]: ");
    Serial.println(pulseLengthMicroseconds);

    // Convert to seconds
    float pulseLengthSeconds = pulseLengthMicroseconds * PULSE_MICROSECONDS_TO_SECONDS;
    Serial.print("Measured pulse length [s]: ");
    Serial.println(pulseLengthSeconds);

    // Calculate distance in meters
    float distanceMeter = (pulseLengthSeconds / 2) * (SPEED_OF_SOUND_METER_PER_SECOND); // Divided by two because pulse needs to travel to obstacle and back.
    Serial.print("Measured distance [m]: ");
    Serial.println(distanceMeter);

    // Convert to millimeters
    float distanceMillimeter = distanceMeter * DISTANCE_METER_TO_MILLIMETER;
    Serial.print("Measured distance [mm]: ");
    Serial.println(distanceMillimeter);
#else
    float distanceMillimeter = 0.0;
    if (unittestMeasuredDistanceMillimeter != 0)
    {
        distanceMillimeter = unittestMeasuredDistanceMillimeter;
    }
#endif // UNIT_TESTING

    // Stop motors in case of an obstacle
    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/46
    if (distanceMillimeter < DISTANCE_THRESHOLD_MILLIMETER)
    {
#ifndef UNIT_TESTING
        Serial.println("Obstacle detected, stopping motors");
        digitalWrite(LED, HIGH);
        leftMotor.setMovementDirection(ChassisMotor::STOP);
        rightMotor.setMovementDirection(ChassisMotor::STOP);
#endif // UNIT_TESTING

        return true;
    }
    else
    {
#ifndef UNIT_TESTING
        Serial.println("No obstacle detected, reactivating motors");
        digitalWrite(LED, LOW);
        leftMotor.setMovementDirectionToDirectionBeforeStop();
        rightMotor.setMovementDirectionToDirectionBeforeStop();
#endif // UNIT_TESTING
    }

    return false;
}