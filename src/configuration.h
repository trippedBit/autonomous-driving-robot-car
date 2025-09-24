#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <math.h>
#include <string>

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/38
#ifndef OTA_FIRMWARE_URL_MACRO
#define OTA_FIRMWARE_URL_MACRO "not set";
#endif // OTA_FIRMWARE_URL
#ifndef OTA_FIRMWARE_MD5_URL_MACRO
#define OTA_FIRMWARE_MD5_URL_MACRO "not set";
#endif // OTA_FIRMWARE_MD5_URL

#ifdef __has_include
#if __has_include("user_configuration.h")
#include "user_configuration.h"
#endif // __has_include
#endif // __has_include

const std::string OTA_FIRMWARE_URL = OTA_FIRMWARE_URL_MACRO;
const std::string OTA_FIRMWARE_MD5_URL = OTA_FIRMWARE_MD5_URL_MACRO;

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/14
const int RANDOM_PIN = 35;               // GPIO35 used to create a random seed using a not-connected pin.
const int WHEEL_DISTANCE_MM = 300;       // Distance between wheels in centimeters (= turn radius).
const float WHEEL_RPM_VELOCITY_MIN = 20; // Measured RPM with VELOCITY_MIN; needs to be updated when VELOCITY_MIN is changed
const float WHEEL_RPS_VELOCITY_MIN = WHEEL_RPM_VELOCITY_MIN / 60.0;
const int WHEEL_DIAMETER_MM = 67; // Measured wheel diameter
const float WHEEL_CIRCUMFERENCE_MM = M_PI * WHEEL_DIAMETER_MM;

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/15
const int ENA_PIN = 0;        // IO0 / GPIO0 / PWM1 / ENA on L298N
const int FORWARD1_PIN = 12;  // TDI / GPIO12 / IN1 on L298N
const int BACKWARD1_PIN = 32; // IO32 / GPIO32 / IN2 on L298N

const int ENB_PIN = 4;        // IO4 / GPIO4 / PWM2 / ENB on L298N
const int FORWARD2_PIN = 16;  // IO16 / GPIO16 / IN3 on L298N
const int BACKWARD2_PIN = 17; // IO17 / GPIO17 / IN4 on L298N

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/17
// Values 0-255 are possible. Minimum value depends on used motor and friction between wheel and surface.
const int VELOCITY_MIN = 150;
const int VELOCITY_MID = 200;
const int VELOCITY_MAX = 250;

#endif // CONFIGURATION_H