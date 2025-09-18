#include <Arduino.h>

#include "src/configuration.h"
#include "src/chassis_motor.h"

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

    delay(10000);
}

void loop()
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