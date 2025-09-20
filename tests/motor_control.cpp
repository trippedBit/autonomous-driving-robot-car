#include "../build/_deps/catch2-src/src/catch2/catch_test_macros.hpp"

#include "../src/motor_control.h"

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/15
TEST_CASE("Chassis motor can be created", "[motor_control]")
{
    ChassisMotor leftMotor(1, 2, 3);
    ChassisMotor rightMotor(4, 5, 6);

    std::string returnValue = applyRandomDirectionAndSpeed(leftMotor,
                                                           rightMotor,
                                                           25,
                                                           0);
    REQUIRE(returnValue == "radians [rad]: 0.436332 | distanceMM [mm]: 130.899689 | circumference [MM]: 210.486710 | revolutions per second [rps]: 0.333333 | velocity [mm/s]: 70.162239 | activeMilliSeconds [ms]: 1865.671509");
}
