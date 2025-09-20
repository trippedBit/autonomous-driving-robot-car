#include <Arduino.h>

#include "src/configuration.h"
#include "src/chassis_motor.h"
#include "src/self_check.h"

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/20
const char *VERSION = "0.1.0";

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/18
bool SELF_CHECK_PASSED = false;

ChassisMotor leftMotor(ENA_PIN,
                       FORWARD1_PIN,
                       BACKWARD1_PIN);
ChassisMotor rightMotor(ENB_PIN,
                        FORWARD2_PIN,
                        BACKWARD2_PIN);

void setup()
{
    Serial.begin(115200);

    Serial.println("Hello, Autonomous Driving Robot Car!");
    Serial.print("Software Version: ");
    Serial.println(VERSION);

    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/18
    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/19
    if (selfCheck(leftMotor,
                  rightMotor))
    {
        SELF_CHECK_PASSED = true;
        Serial.println("Self check passed.");

        // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/13
        int additionalDelay = 10000 - millis();
        Serial.print("Additional delay before switching to loop(): ");
        Serial.println(additionalDelay);
        delay(additionalDelay);
    }
    else
    {
        while (true)
        {
            Serial.println("Self check failed!");
            delay(5000);
        }
    }
}

void loop()
{
    if (SELF_CHECK_PASSED) // Execute loop only if self check passed
    {
        // Just a demo sequence to test the motors - not related to any requirements
        analogWrite(ENA_PIN, 110);
        analogWrite(ENB_PIN, 150);

        leftMotor.setMovementDirection(ChassisMotor::FORWARD);
        delay(5000);
        leftMotor.setMovementDirection(ChassisMotor::STOP);
        delay(5000);
        leftMotor.setMovementDirection(ChassisMotor::BACKWARD);
        delay(5000);
        leftMotor.setMovementDirection(ChassisMotor::STOP);

        delay(5000);

        rightMotor.setMovementDirection(ChassisMotor::FORWARD);
        delay(5000);
        rightMotor.setMovementDirection(ChassisMotor::STOP);
        delay(5000);
        rightMotor.setMovementDirection(ChassisMotor::BACKWARD);
        delay(5000);
        rightMotor.setMovementDirection(ChassisMotor::STOP);

        delay(5000);
    }
}