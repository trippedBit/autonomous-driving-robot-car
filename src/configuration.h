#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <array>
#include <math.h>
#include <string>

extern bool LOOP_FUNCTION_ENTERED; // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/39

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/38
#ifndef OTA_FIRMWARE_URL_MACRO
#define OTA_FIRMWARE_URL_MACRO "not set";
#endif // OTA_FIRMWARE_URL_MACRO

#ifndef OTA_FIRMWARE_MD5_URL_MACRO
#define OTA_FIRMWARE_MD5_URL_MACRO "not set";
#endif // OTA_FIRMWARE_MD5_URL_MACRO

#ifndef OTA_FIRMWARE_VERSION_URL_MACRO
#define OTA_FIRMWARE_VERSION_URL_MACRO "not set";
#endif // OTA_FIRMWARE_URL_MACRO

#ifndef WIFI_NAME_MACRO
#define WIFI_NAME_MACRO "not set";
#endif // WIFI_NAME_MACRO

#ifndef WIFI_PASSWORD_MACRO
#define WIFI_PASSWORD_MACRO "not set";
#endif // WIFI_PASSWORD_MACRO

#ifndef WIFI_IP_MACRO
#define WIFI_IP_MACRO {0, 0, 0, 0};
#endif // WIFI_IP_MACRO

#ifndef WIFI_DNS_MACRO
#define WIFI_DNS_MACRO {0, 0, 0, 0};
#endif // WIFI_DNS_MACRO

#ifndef WIFI_GATEWAY_MACRO
#define WIFI_GATEWAY_MACRO {0, 0, 0, 0};
#endif // WIFI_GATEWAY_MACRO

#ifndef WIFI_SUBNET_MACRO
#define WIFI_SUBNET_MACRO {0, 0, 0, 0};
#endif // WIFI_SUBNET_MACRO

#ifdef __has_include
#if __has_include("user_configuration.h")
#include "user_configuration.h"
#endif // __has_include
#endif // __has_include

const std::string OTA_FIRMWARE_URL = OTA_FIRMWARE_URL_MACRO;         // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/40
const std::string OTA_FIRMWARE_MD5_URL = OTA_FIRMWARE_MD5_URL_MACRO; // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/40
const std::string OTA_FIRMWARE_VERSION_URL = OTA_FIRMWARE_VERSION_URL_MACRO;
const std::string WIFI_NAME = WIFI_NAME_MACRO;
const std::string WIFI_PASSWORD = WIFI_PASSWORD_MACRO;
const std::array<int, 4> WIFI_IP = WIFI_IP_MACRO;
const std::array<int, 4> WIFI_DNS = WIFI_DNS_MACRO;
const std::array<int, 4> WIFI_GATEWAY = WIFI_GATEWAY_MACRO;
const std::array<int, 4> WIFI_SUBNET = WIFI_SUBNET_MACRO;

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

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/31
const int SENSOR_TRIGGER_PIN = -1;
const int SENSOR_TRIGGER_PIN_LOW_TIME_MICROSECONDS = 5;
const int SENSOR_TRIGGER_PIN_HIGH_TIME_MICROSECONDS = 10;
const int SENSOR_ECHO_PIN = -1;
const unsigned long SPEED_OF_SOUND_MILLIMETER_PER_MICROSECOND = 0.34346; // 343,46 m/s at 20°C
const int DISTANCE_THRESHOLD_MILLIMETER = 30000;                         // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/32

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/36
const float LEFT_MOTOR_PWM_FACTOR = 1;
const float RIGHT_MOTOR_PWM_FACTOR = 0.90;

#endif // CONFIGURATION_H