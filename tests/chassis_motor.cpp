#include "../build/_deps/catch2-src/src/catch2/catch_test_macros.hpp"

#include "../src/chassis_motor.h"

TEST_CASE("Chassis motor can be created", "[chassis_motor]")
{
    ChassisMotor motor(5, 6, 7);
    REQUIRE(true); // If we reach this point, the motor was created successfully
}

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