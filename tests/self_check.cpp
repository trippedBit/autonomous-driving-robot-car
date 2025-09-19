#include "../build/_deps/catch2-src/src/catch2/catch_test_macros.hpp"

#include "../src/chassis_motor.h"
#include "../src/self_check.h"

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/18
// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/19
TEST_CASE("Self-check function exists and returns true", "[self_check]")
{
    ChassisMotor leftMotor(5, 6, 7);
    ChassisMotor rightMotor(8, 9, 10);
    bool result = selfCheck(leftMotor,
                            rightMotor);
    REQUIRE(result == true);
}