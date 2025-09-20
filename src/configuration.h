#ifndef CONFIGURATION_H
#define CONFIGURATION_H

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