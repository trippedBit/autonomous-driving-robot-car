#include <Arduino.h>

#include <rom/rtc.h> // For reset reason

#include "src/configuration.h"
#include "src/chassis_motor.h"
#include "src/fault_memory.h"
#include "src/motor_control.h"
#include "src/self_check.h"
#include "src/ota.h"
#include "src/wifi_wrapper.h"

#include "src/VERSION.h"

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/14
int timeDirectionMovement = 2000;

ChassisMotor rightMotor(ENA_PIN,
                        FORWARD1_PIN,
                        BACKWARD1_PIN,
                        RIGHT_MOTOR_PWM_FACTOR);
ChassisMotor leftMotor(ENB_PIN,
                       FORWARD2_PIN,
                       BACKWARD2_PIN,
                       LEFT_MOTOR_PWM_FACTOR);

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

    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/44
    // Clear faults for motor checks, they will be set again if check fails.
    FaultMemory().setValue(1, FaultMemory::INACTIVE);
    FaultMemory().setValue(2, FaultMemory::INACTIVE);

    int resetReasonFaultAddressCPU1 = FaultMemory().getFaultEepromAddress(1);
    int resetReasonDataAddressCPU1 = FaultMemory().getFaultDataEepromAddress(1);

    int resetReason = rtc_get_reset_reason(0);
    if (resetReason != ESP_RST_POWERON &&
        resetReason != ESP_RST_SW &&
        resetReason != EXT_CPU_RESET)
    {
        Serial.print("Unexpected Reset reason CPU1: ");
        Serial.println(resetReason);

        // Set fault for unexpected reset
        FaultMemory().setFaultActive(resetReasonFaultAddressCPU1,
                                     true);

        FaultMemory().setValue(resetReasonDataAddressCPU1,
                               resetReason);
    }
    else
    {
        Serial.print("Reset reason CPU1: ");
        Serial.println(resetReason);
    }

    int resetReasonFaultAddressCPU2 = FaultMemory().getFaultEepromAddress(4);
    int resetReasonDataAddressCPU2 = FaultMemory().getFaultDataEepromAddress(4);

    resetReason = rtc_get_reset_reason(1);
    if (resetReason != ESP_RST_POWERON &&
        resetReason != ESP_RST_SW &&
        resetReason != EXT_CPU_RESET)
    {
        Serial.print("Unexpected Reset reason CPU2: ");
        Serial.println(resetReason);

        // Set fault for unexpected reset
        FaultMemory().setFaultActive(resetReasonFaultAddressCPU2,
                                     true);

        FaultMemory().setValue(resetReasonDataAddressCPU2,
                               resetReason);
    }
    else
    {
        Serial.print("Reset reason CPU2: ");
        Serial.println(resetReason);
    }

    std::vector<std::string> activeFaults = FaultMemory().getAllActiveFaults();
    if (activeFaults.size() == 0)
    {
        Serial.println("No active faults on startup");
    }
    else
    {
        Serial.println("");
        Serial.print("Active faults on startup: ");
        for (const auto &fault : activeFaults)
        {
            Serial.println(fault.c_str());
        }
        Serial.println("");
    }

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
    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/44
    // Process user input.
    if (Serial.available() > 0)
    {
        String receivedCommand = Serial.readStringUntil('\n');
        receivedCommand.trim();
        int lastIndex = receivedCommand.lastIndexOf("_");
        String command = receivedCommand.substring(0,
                                                   lastIndex);
        String parameter = receivedCommand.substring(lastIndex + 1);
        Serial.print("Received command: ");
        Serial.println(command);
        Serial.print("Received parameter: ");
        Serial.println(parameter);

        int parameterAsInt = parameter.toInt();
        if (command == "FM_DEL")
        {
            if (parameter != "0" && parameterAsInt == 0)
            {
                // Given parameter is anything but "0" and conversion to int resulted in 0.
                // This means the parameter is invalid.
                Serial.println("Invalid parameter, must be integer");
            }
            else
            {
                // parameterAsInt is either 0 and parameter was "0", therefore valid conversion,
                // or parameter is a valid integer unequal 0.
                FaultMemory().setFaultActive(parameterAsInt,
                                             false);
            }
        }
        else if (command == "FM_SET")
        {
            if (parameter != "0" && parameterAsInt == 0)
            {
                // Given parameter is anything but "0" and conversion to int resulted in 0.
                // This means the parameter is invalid.
                Serial.println("Invalid parameter, must be integer");
            }
            else
            {
                // parameterAsInt is either 0 and parameter was "0", therefore valid conversion,
                // or parameter is a valid integer unequal 0.
                FaultMemory().setFaultActive(parameterAsInt,
                                             true);
            }
        }
        else if (command == "FM_STAT")
        {
            if (parameter != "0" && parameterAsInt == 0)
            {
                // Given parameter is anything but "0" and conversion to int resulted in 0.
                // This means the parameter is invalid.
                Serial.println("Invalid parameter, must be integer");
            }
            else
            {
                // parameterAsInt is either 0 and parameter was "0", therefore valid conversion,
                // or parameter is a valid integer unequal 0.
                Serial.print("Fault ");
                Serial.print(parameter);
                Serial.print(" status: ");
                Serial.println(FaultMemory().isFaultActive(parameterAsInt) ? "active" : "inactive");
            }
        }
        else
        {
            Serial.println("Unknown command");
        }
    }

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

        int remainingMillis = timeDirectionMovement;
        while (remainingMillis > 0)
        {
            int millisWhileLoopStart = millis();

            obstacleDetection(leftMotor,
                              rightMotor);
            edgeDetection(leftMotor,
                          rightMotor);

            remainingMillis = timeDirectionMovement - (millis() - millisWhileLoopStart);
        }
    }
}