#include "../build/_deps/catch2-src/src/catch2/catch_test_macros.hpp"

#include "../src/motor_control.h"

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/15
TEST_CASE("Movement calculation for right turn is correct", "[motor_control]")
{
    ChassisMotor leftMotor(1, 2, 3);
    ChassisMotor rightMotor(4, 5, 6);

    std::string returnValue = applyRandomDirectionAndSpeed(leftMotor,
                                                           rightMotor,
                                                           25,
                                                           0);
    REQUIRE(returnValue == "radians [rad]: 0.436332 | distanceMM [mm]: 130.899689 | circumference [MM]: 210.486710 | revolutions per second [rps]: 0.333333 | velocity [mm/s]: 70.162239 | activeMilliSeconds [ms]: 1865.671509");
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/15
TEST_CASE("Movement calculation for left turn is correct", "[motor_control]")
{
    ChassisMotor leftMotor(1, 2, 3);
    ChassisMotor rightMotor(4, 5, 6);

    std::string returnValue = applyRandomDirectionAndSpeed(leftMotor,
                                                           rightMotor,
                                                           -25,
                                                           0);
    REQUIRE(returnValue == "radians [rad]: 0.436332 | distanceMM [mm]: 130.899689 | circumference [MM]: 210.486710 | revolutions per second [rps]: 0.333333 | velocity [mm/s]: 70.162239 | activeMilliSeconds [ms]: 1865.671509");
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/46
TEST_CASE("Obstacle detection", "[motor_control]")
{
    ChassisMotor leftMotor(1, 2, 3);
    ChassisMotor rightMotor(4, 5, 6);

    SECTION("Obstacle within range - default unittest value")
    {
        bool returnValue = obstacleDetection(leftMotor,
                                             rightMotor);
        REQUIRE(returnValue == true);
    }

    SECTION("Obstacle within range - 299mm")
    {
        bool returnValue = obstacleDetection(leftMotor,
                                             rightMotor,
                                             299);
        REQUIRE(returnValue == true);
    }

    SECTION("Obstacle within range - 0mm")
    {
        bool returnValue = obstacleDetection(leftMotor,
                                             rightMotor,
                                             0);
        REQUIRE(returnValue == true);
    }

    SECTION("Obstacle within range - -1mm")
    {
        bool returnValue = obstacleDetection(leftMotor,
                                             rightMotor,
                                             -1);
        REQUIRE(returnValue == true);
    }

    SECTION("Obstacle outside range - 301mm")
    {
        bool returnValue = obstacleDetection(leftMotor,
                                             rightMotor,
                                             301);
        REQUIRE(returnValue == false);
    }
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/33
TEST_CASE("Edge detection", "[motor_control]")
{
    ChassisMotor leftMotor(1, 2, 3);
    ChassisMotor rightMotor(4, 5, 6);

    float edgeDistanceCathedeBMillimeter = sqrt(pow(EDGE_DISTANCE_THRESHOLD_MILLIMETER, 2) - pow(EDGE_SENSOR_POS_Z_MILLIMETER, 2));

    SECTION("Distance below edge threshold - default unittest value")
    {
        bool returnValue = edgeDetection(leftMotor,
                                         rightMotor);
        REQUIRE(returnValue == false);
    }

    SECTION("Distance below edge threshold - edgeDistanceCathedeBMillimeter - 1")
    {
        bool returnValue = edgeDetection(leftMotor,
                                         rightMotor,
                                         edgeDistanceCathedeBMillimeter - 1);
        REQUIRE(returnValue == false);
    }

    SECTION("Distance below edge threshold - 0mm")
    {
        bool returnValue = edgeDetection(leftMotor,
                                         rightMotor,
                                         0);
        REQUIRE(returnValue == false);
    }

    SECTION("Distance below edge threshold - -1mm")
    {
        bool returnValue = edgeDetection(leftMotor,
                                         rightMotor,
                                         -1);
        REQUIRE(returnValue == false);
    }

    SECTION("Distance at edge threshold - edgeDistanceCathedeBMillimeter")
    {
        bool returnValue = edgeDetection(leftMotor,
                                         rightMotor,
                                         edgeDistanceCathedeBMillimeter);
        REQUIRE(returnValue == false);
    }

    SECTION("Distance above edge threshold - edgeDistanceCathedeBMillimeter + 1")
    {
        bool returnValue = edgeDetection(leftMotor,
                                         rightMotor,
                                         edgeDistanceCathedeBMillimeter + 1);
        REQUIRE(returnValue == true);
    }
}