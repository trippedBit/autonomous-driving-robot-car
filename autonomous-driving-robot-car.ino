#include <Arduino.h>

#include "src/configuration.h"
#include "src/chassis_motor.h"
#include "src/motor_control.h"
#include "src/self_check.h"
#include "src/ota.h"
#include "src/wifi_wrapper.h"

#include "src/VERSION.h"

bool LOOP_FUNCTION_ENTERED = true; // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/39
const int LED = 2;

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/14
int timeDirectionMovement = 2000;

ChassisMotor leftMotor(ENA_PIN,
                       FORWARD1_PIN,
                       BACKWARD1_PIN);
ChassisMotor rightMotor(ENB_PIN,
                        FORWARD2_PIN,
                        BACKWARD2_PIN);

SelfCheck selfCheck;

WiFiWrapper wifiWrapper(WIFI_NAME,
                        WIFI_PASSWORD,
                        WIFI_IP,
                        WIFI_DNS,
                        WIFI_GATEWAY,
                        WIFI_SUBNET);

OTA ota(OTA_FIRMWARE_URL,
        OTA_FIRMWARE_MD5_URL,
        OTA_FIRMWARE_VERSION_URL);

void setup()
{
    pinMode(LED, OUTPUT);

    Serial.begin(115200);

    Serial.println("Hello, Autonomous Driving Robot Car!");
    Serial.print("Software Version: ");
    Serial.println(VERSION);

    Serial.println("OTA URLs (firmware / MD5 / version):");
    Serial.println(OTA_FIRMWARE_URL.c_str());
    Serial.println(OTA_FIRMWARE_MD5_URL.c_str());
    Serial.println(OTA_FIRMWARE_VERSION_URL.c_str());

    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/14
    randomSeed(analogRead(RANDOM_PIN));

    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/13
    while (millis() < 10000)
    {
        // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/19
        // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/29
        if (!selfCheck.SELF_CHECK_PASSED)
        {
            selfCheck.selfCheck(leftMotor,
                                rightMotor);

            Serial.print("Left motor states: ");
            Serial.print(selfCheck.leftMotorForwardPinState);
            Serial.print(" | ");
            Serial.println(selfCheck.leftMotorBackwardPinState);

            Serial.print("Right motor states: ");
            Serial.print(selfCheck.rightMotorForwardPinState);
            Serial.print(" | ");
            Serial.println(selfCheck.rightMotorBackwardPinState);

            delay(500); // Next check in 500ms
        }
        else
        {
            // Check passed, now connect to WiFi.
            wifiWrapper.connectWiFi();

            // Now perform OTA update if available.
            LOOP_FUNCTION_ENTERED = false; // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/39
            ota.begin(VERSION);

            // Just wait until 10s are over.
            int additionalDelay = 10000 - millis();
            Serial.print("Additional delay before switching to loop(): ");
            Serial.println(additionalDelay);
            if (additionalDelay > 0)
            {
                delay(additionalDelay);
            }
        }
    }

    if (!selfCheck.SELF_CHECK_PASSED)
    {
        Serial.println("Startup phase over and self check failed");
        while (true)
        {
            digitalWrite(LED, HIGH);
            delay(500);
            digitalWrite(LED, LOW);
            delay(500);
        }
    }
    else
    {
        Serial.println("Startup phase over, check passed, enabling motors");
        leftMotor.setMovementDirection(ChassisMotor::FORWARD);
        rightMotor.setMovementDirection(ChassisMotor::FORWARD);
    }
}

void loop()
{
    if (!LOOP_FUNCTION_ENTERED) // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/39
    {
        LOOP_FUNCTION_ENTERED = true;
    }

    if (selfCheck.SELF_CHECK_PASSED) // Execute loop only if self check passed
    {
        // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/14
        int direction = random(-180,
                               180);
        Serial.print("Random direction: ");
        Serial.println(direction);
        int velocityPWM = random(VELOCITY_MIN,
                                 VELOCITY_MAX);
        Serial.print("Random velocity (PWM): ");
        Serial.println(velocityPWM);

        applyRandomDirectionAndSpeed(leftMotor,
                                     rightMotor,
                                     direction,
                                     velocityPWM);

        delay(timeDirectionMovement);
    }
}