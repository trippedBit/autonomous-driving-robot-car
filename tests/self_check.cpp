#include "../build/_deps/catch2-src/src/catch2/catch_test_macros.hpp"

#include "../src/chassis_motor.h"
#include "../src/self_check.h"

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/19
// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/29
TEST_CASE("Self-check function exists and returns true", "[self_check]")
{
    ChassisMotor leftMotor(5, 6, 7);
    ChassisMotor rightMotor(8, 9, 10);
    SelfCheck selfCheck;
    bool result = selfCheck.selfCheck(leftMotor,
                                      rightMotor);
    REQUIRE(result == true);
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/19
// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/29
TEST_CASE("Self-check function fails due to left motor check", "[self_check]")
{
    ChassisMotor leftMotor(5, 6, 7);
    ChassisMotor rightMotor(8, 9, 10);
    // Force failed check
    SelfCheck selfCheck;
    bool result = selfCheck.selfCheck(leftMotor,
                                      rightMotor,
                                      true);
    REQUIRE(result == false);
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/19
// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/29
TEST_CASE("Self-check function fails due to right motor check", "[self_check]")
{
    ChassisMotor leftMotor(5, 6, 7);
    ChassisMotor rightMotor(8, 9, 10);
    // Force failed check
    SelfCheck selfCheck;
    bool result = selfCheck.selfCheck(leftMotor,
                                      rightMotor,
                                      false,
                                      true);
    REQUIRE(result == false);
}