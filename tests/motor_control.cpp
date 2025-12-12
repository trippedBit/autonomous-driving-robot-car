#include "../build/_deps/catch2-src/src/catch2/catch_test_macros.hpp"

#include "../src/motor_control.h"
#include "../src/mocks.h"

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

TEST_CASE("First movement delay", "[motor_control]")
{
    SECTION("Delay for first movement - TEST_0001")
    {
        ChassisMotor leftMotor(1,
                               2,
                               3);
        ChassisMotor rightMotor(4,
                                5,
                                6);

        std::array<ChassisMotor, 2> motors = {leftMotor,
                                              rightMotor};

        // Step 1
        for (ChassisMotor &motor : motors)
        {
            REQUIRE(motor.getDirectionPinState(motor.FORWARD_PIN) == ChassisMotor::STOP);
            REQUIRE(motor.getDirectionPinState(motor.BACKWARD_PIN) == ChassisMotor::STOP);
        }

        // Step 2
        for (ChassisMotor &motor : motors)
        {
            motor.setMovementDirection(ChassisMotor::FORWARD);

            REQUIRE(motor.getDirectionPinState(motor.FORWARD_PIN) == ChassisMotor::STOP);
            REQUIRE(motor.getDirectionPinState(motor.BACKWARD_PIN) == ChassisMotor::STOP);
        }

        // Step 3
        setMockMillis(9900);
        std::cout << "Waited " << millis() << "ms (simulated)..." << std::endl;
        for (ChassisMotor &motor : motors)
        {
            REQUIRE(motor.getDirectionPinState(motor.FORWARD_PIN) == ChassisMotor::STOP);
            REQUIRE(motor.getDirectionPinState(motor.BACKWARD_PIN) == ChassisMotor::STOP);
        }

        // Step 4
        setMockMillis(10000);
        for (ChassisMotor &motor : motors)
        {
            REQUIRE(motor.getDirectionPinState(motor.FORWARD_PIN) == ChassisMotor::STOP);
            REQUIRE(motor.getDirectionPinState(motor.BACKWARD_PIN) == ChassisMotor::STOP);
        }

        // Step 5
        for (ChassisMotor &motor : motors)
        {
            motor.setMovementDirection(ChassisMotor::FORWARD);

            REQUIRE(motor.getDirectionPinState(motor.FORWARD_PIN) == ChassisMotor::FORWARD);
            REQUIRE(motor.getDirectionPinState(motor.BACKWARD_PIN) == ChassisMotor::STOP);
        }
    }
}