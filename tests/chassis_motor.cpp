#include "../build/_deps/catch2-src/src/catch2/catch_test_macros.hpp"

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