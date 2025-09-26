#include "../build/_deps/catch2-src/src/catch2/catch_test_macros.hpp"

#include "../src/configuration.h"
#include "../src/chassis_motor.h"

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/15
TEST_CASE("Chassis motor can be created", "[chassis_motor]")
{
    ChassisMotor motor(5, 6, 7);
    REQUIRE(true); // If we reach this point, the motor was created successfully
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/15
TEST_CASE("Chassis motor can set movement direction", "[chassis_motor]")
{
    ChassisMotor motor(5, 6, 7);

    SECTION("Set to STOP")
    {
        int result = motor.setMovementDirection(ChassisMotor::STOP);
        REQUIRE(result == ChassisMotor::STOP);
    }

    SECTION("Set to FORWARD")
    {
        int result = motor.setMovementDirection(ChassisMotor::FORWARD);
        REQUIRE(result == ChassisMotor::FORWARD);
    }

    SECTION("Set to BACKWARD")
    {
        int result = motor.setMovementDirection(ChassisMotor::BACKWARD);
        REQUIRE(result == ChassisMotor::BACKWARD);
    }

    SECTION("Set to invalid direction")
    {
        int result = motor.setMovementDirection(static_cast<ChassisMotor::MovementDirection>(999));
        REQUIRE(result == -2); // Expect error code for invalid direction
    }
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/15
TEST_CASE("Chassis motor default pin configuration", "[chassis_motor]")
{
    REQUIRE(ENA_PIN == 0);
    REQUIRE(FORWARD1_PIN == 12);
    REQUIRE(BACKWARD1_PIN == 32);

    REQUIRE(ENB_PIN == 4);
    REQUIRE(FORWARD2_PIN == 16);
    REQUIRE(BACKWARD2_PIN == 17);
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/18
TEST_CASE("Chassis motor enable pin analog value", "[chassis_motor]")
{
    ChassisMotor motor(5, 6, 7);
    REQUIRE(motor.getEnablePinAnalogValue() == 0);
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/18
TEST_CASE("Chassis motor direction pin state", "[chassis_motor]")
{
    ChassisMotor motor(5, 6, 7);
    int pinState = motor.getDirectionPinState(ChassisMotor::BACKWARD_PIN);
    REQUIRE(pinState == 0);

    pinState = motor.getDirectionPinState(ChassisMotor::FORWARD_PIN);
    REQUIRE(pinState == 0);

    pinState = motor.getDirectionPinState(static_cast<ChassisMotor::ControlPin>(999));
    REQUIRE(pinState == -1);
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/17
TEST_CASE("Chassis motor velocities", "[chassis_motor]")
{
    REQUIRE(VELOCITY_MIN == 150);
    REQUIRE(VELOCITY_MID == 200);
    REQUIRE(VELOCITY_MAX == 250);
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/36
TEST_CASE("Chassis motor initialization with default PWM factor", "[chassis_motor]")
{
    ChassisMotor motor(5, 6, 7);
    REQUIRE(true);
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/36
TEST_CASE("Chassis motor initialization with non-default PWM factor", "[chassis_motor]")
{
    ChassisMotor motor(5, 6, 7, 0.9);
    REQUIRE(true);
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/36
TEST_CASE("Chassis motor calculated PWM with default PWM factor", "[chassis_motor]")
{
    ChassisMotor motor(5, 6, 7);
    float result = motor.setVelocityPWM(200);
    REQUIRE(result == 200.0f); // Default factor is 1, so PWM should be unchanged
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/36
TEST_CASE("Chassis motor calculated PWM with non-default PWM factor", "[chassis_motor]")
{
    ChassisMotor motor(5, 6, 7, 0.9);
    float result = motor.setVelocityPWM(200);
    REQUIRE(result == 180.0f);
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/36
TEST_CASE("Chassis motor calculated PWM above upper limit", "[chassis_motor]")
{
    ChassisMotor motor(5, 6, 7, 2);
    float result = motor.setVelocityPWM(200);
    REQUIRE(result == 255.0f); // Calculated PWM is limited to range 0-255
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/36
TEST_CASE("Chassis motor calculated PWM below lower limit", "[chassis_motor]")
{
    ChassisMotor motor(5, 6, 7, -2);
    float result = motor.setVelocityPWM(200);
    REQUIRE(result == 0.0f); // Calculated PWM is limited to range 0-255
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/36
TEST_CASE("Chassis motor calculated PWM with factor zero", "[chassis_motor]")
{
    ChassisMotor motor(5, 6, 7, 0);
    float result = motor.setVelocityPWM(200);
    REQUIRE(result == 0.0f); // Calculated PWM is limited to range 0-255
}
