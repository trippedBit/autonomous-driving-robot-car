#include "../build/_deps/catch2-src/src/catch2/catch_test_macros.hpp"
#include "../build/_deps/catch2-src/src/catch2/matchers/catch_matchers_floating_point.hpp"

#include "../src/motor_control.h"
#include "../src/mocks.h"

TEST_CASE("TEST_0001 - First movement delay", "[motor_control]")
{
    ChassisMotor leftMotor(ENA_PIN,
                           FORWARD1_PIN,
                           BACKWARD1_PIN);
    ChassisMotor rightMotor(ENB_PIN,
                            FORWARD2_PIN,
                            BACKWARD2_PIN);

    std::array<ChassisMotor, 2> motors = {leftMotor,
                                          rightMotor};

    // Step 1
    for (ChassisMotor &motor : motors)
    {
        REQUIRE(motor.getDirectionPinState(motor.FORWARD_PIN) == ChassisMotor::STOP_DIRECTION);
        REQUIRE(motor.getDirectionPinState(motor.BACKWARD_PIN) == ChassisMotor::STOP_DIRECTION);
    }

    // Step 2
    for (ChassisMotor &motor : motors)
    {
        motor.setMovementDirection(ChassisMotor::FORWARD_DIRECTION);

        REQUIRE(motor.getDirectionPinState(motor.FORWARD_PIN) == ChassisMotor::STOP_DIRECTION);
        REQUIRE(motor.getDirectionPinState(motor.BACKWARD_PIN) == ChassisMotor::STOP_DIRECTION);
    }

    // Step 3
    setMockMillis(9900);
    std::cout << "Waited " << millis() << "ms (simulated)..." << std::endl;
    for (ChassisMotor &motor : motors)
    {
        REQUIRE(motor.getDirectionPinState(motor.FORWARD_PIN) == ChassisMotor::STOP_DIRECTION);
        REQUIRE(motor.getDirectionPinState(motor.BACKWARD_PIN) == ChassisMotor::STOP_DIRECTION);
    }

    // Step 4
    setMockMillis(10000);
    for (ChassisMotor &motor : motors)
    {
        REQUIRE(motor.getDirectionPinState(motor.FORWARD_PIN) == ChassisMotor::STOP_DIRECTION);
        REQUIRE(motor.getDirectionPinState(motor.BACKWARD_PIN) == ChassisMotor::STOP_DIRECTION);
    }

    // Step 5
    for (ChassisMotor &motor : motors)
    {
        motor.setMovementDirection(ChassisMotor::FORWARD_DIRECTION);

        REQUIRE(motor.getDirectionPinState(motor.FORWARD_PIN) == ChassisMotor::FORWARD_DIRECTION);
        REQUIRE(motor.getDirectionPinState(motor.BACKWARD_PIN) == ChassisMotor::STOP_DIRECTION);
    }
}

TEST_CASE("TEST_0002 - Motor pin variables are defined", "[motor_control]")
{

    static_assert(std::is_same<decltype(ENA_PIN), const int>::value, "ENA_PIN is not of type const int");
    static_assert(std::is_same<decltype(FORWARD1_PIN), const int>::value, "FORWARD1_PIN is not of type const int");
    static_assert(std::is_same<decltype(BACKWARD1_PIN), const int>::value, "BACKWARD1_PIN is not of type const int");

    static_assert(std::is_same<decltype(ENB_PIN), const int>::value, "ENB_PIN is not of type const int");
    static_assert(std::is_same<decltype(FORWARD2_PIN), const int>::value, "FORWARD2_PIN is not of type const int");
    static_assert(std::is_same<decltype(BACKWARD2_PIN), const int>::value, "BACKWARD2_PIN is not of type const int");
}

TEST_CASE("TEST_0003 - Setting motor pin states set proper motor direction", "[motor_control]")
{
    // Step 1 is part of the header file.

    // Step 2
    ChassisMotor motor1(ENA_PIN,
                        FORWARD1_PIN,
                        BACKWARD1_PIN);
    ChassisMotor motor2(ENB_PIN,
                        FORWARD2_PIN,
                        BACKWARD2_PIN);

    std::array<ChassisMotor, 2> motors = {motor1,
                                          motor2};

    for (ChassisMotor &motor : motors)
    {
        int forwardPin = motor.getDirectionPinNumber(ChassisMotor::FORWARD_PIN);
        int backwardPin = motor.getDirectionPinNumber(ChassisMotor::BACKWARD_PIN);

        // Step 3
        std::cout << "Setting forward pin " << std::to_string(forwardPin) << std::endl;
        std::cout << "Setting backward pin " << std::to_string(backwardPin) << std::endl;
        digitalWrite(forwardPin, LOW);
        digitalWrite(backwardPin, LOW);
        CHECK(motor.getCurrentDirection() == ChassisMotor::FORWARD_DIRECTION);

        // Step 4
        digitalWrite(forwardPin, HIGH);
        digitalWrite(backwardPin, LOW);
        std::cout << "Now checking current direction..." << std::endl;
        REQUIRE(motor.getCurrentDirection() == ChassisMotor::FORWARD_DIRECTION);

        // Step 5
        digitalWrite(forwardPin, LOW);
        digitalWrite(backwardPin, HIGH);
        REQUIRE(motor.getCurrentDirection() == ChassisMotor::BACKWARD_DIRECTION);

        // Step 6
        digitalWrite(forwardPin, HIGH);
        digitalWrite(backwardPin, HIGH);
        CHECK(motor.getCurrentDirection() == ChassisMotor::FORWARD_DIRECTION);
    }
}

TEST_CASE("TEST_0004 - Setting motor direction sets proper direction pin states", "[motor_control]")
{
    // Step 1 is part of the header file.

    // Step 2
    ChassisMotor motor1(ENA_PIN,
                        FORWARD1_PIN,
                        BACKWARD1_PIN);
    ChassisMotor motor2(ENB_PIN,
                        FORWARD2_PIN,
                        BACKWARD2_PIN);

    std::array<ChassisMotor, 2> motors = {motor1,
                                          motor2};
    for (ChassisMotor &motor : motors)
    {
        int forwardPin = motor.getDirectionPinNumber(ChassisMotor::FORWARD_PIN);
        int backwardPin = motor.getDirectionPinNumber(ChassisMotor::BACKWARD_PIN);

        motor.setMovementDirection(ChassisMotor::INVALID_DIRECTION);
        CHECK(motor.getDirectionPinState(ChassisMotor::FORWARD_PIN) == HIGH);
        CHECK(motor.getDirectionPinState(ChassisMotor::BACKWARD_PIN) == HIGH);

        motor.setMovementDirection(ChassisMotor::ERROR_DIRECTION);
        CHECK(motor.getDirectionPinState(ChassisMotor::FORWARD_PIN) == HIGH);
        CHECK(motor.getDirectionPinState(ChassisMotor::BACKWARD_PIN) == HIGH);

        motor.setMovementDirection(ChassisMotor::STOP_DIRECTION);
        CHECK(motor.getDirectionPinState(ChassisMotor::FORWARD_PIN) == HIGH);
        CHECK(motor.getDirectionPinState(ChassisMotor::BACKWARD_PIN) == HIGH);

        motor.setMovementDirection(ChassisMotor::FORWARD_DIRECTION);
        REQUIRE(motor.getDirectionPinState(ChassisMotor::FORWARD_PIN) == HIGH);
        REQUIRE(motor.getDirectionPinState(ChassisMotor::BACKWARD_PIN) == LOW);

        motor.setMovementDirection(ChassisMotor::BACKWARD_DIRECTION);
        REQUIRE(motor.getDirectionPinState(ChassisMotor::FORWARD_PIN) == LOW);
        REQUIRE(motor.getDirectionPinState(ChassisMotor::BACKWARD_PIN) == HIGH);
    }
}

TEST_CASE("TEST_0005 - Parameter DISTANCE_THRESHOLD_MILLIMETER is defined in configuration", "[motor_control]")
{
    static_assert(std::is_same<decltype(DISTANCE_THRESHOLD_MILLIMETER), const int>::value, "DISTANCE_THRESHOLD_MILLIMETER is not of type const int");
}

TEST_CASE("TEST_0006 - Obstacle detection based on parameter", "[motor_control]")
{
    ChassisMotor motor1(ENA_PIN,
                        FORWARD1_PIN,
                        BACKWARD1_PIN);
    ChassisMotor motor2(ENB_PIN,
                        FORWARD2_PIN,
                        BACKWARD2_PIN);

    // Step 2
    setMockPulseIn(500);
    bool obstacleDetected = obstacleDetection(motor1,
                                              motor2);
    REQUIRE(obstacleDetected == false);

    // Step 3
    setMockPulseIn(301);
    obstacleDetected = obstacleDetection(motor1,
                                         motor2);
    REQUIRE(obstacleDetected == false);

    // Step 4
    setMockPulseIn(299);
    obstacleDetected = obstacleDetection(motor1,
                                         motor2);
    REQUIRE(obstacleDetected == true);

    // Step 5
    setMockPulseIn(300);
    obstacleDetected = obstacleDetection(motor1,
                                         motor2);
    REQUIRE(obstacleDetected == true);
}

TEST_CASE("TEST_0007 - parameters LEFT_MOTOR_PWM_FACTOR and RIGHT_MOTOR_PWM_FACTOR are defined in configuration", "[motor_control]")
{

    static_assert(std::is_same<decltype(LEFT_MOTOR_PWM_FACTOR), const float>::value, "LEFT_MOTOR_PWM_FACTOR is not of type const float");
    static_assert(std::is_same<decltype(RIGHT_MOTOR_PWM_FACTOR), const float>::value, "RIGHT_MOTOR_PWM_FACTOR is not of type const float");

    REQUIRE_THAT(LEFT_MOTOR_PWM_FACTOR, Catch::Matchers::WithinAbs(1.0f, 0.001f));
    REQUIRE_THAT(RIGHT_MOTOR_PWM_FACTOR, Catch::Matchers::WithinAbs(0.9f, 0.001f));
}

TEST_CASE("TEST_0008 - resulting PWM is limited to range 0-255 (default factor 1.0)", "[motor_control]")
{
    ChassisMotor motor1(ENA_PIN,
                        FORWARD1_PIN,
                        BACKWARD1_PIN,
                        1.0);

    REQUIRE_THAT(motor1.setVelocityPWM(-1), Catch::Matchers::WithinAbs(0.0f, 0.001f));
    REQUIRE_THAT(motor1.setVelocityPWM(0), Catch::Matchers::WithinAbs(0.0f, 0.001f));
    REQUIRE_THAT(motor1.setVelocityPWM(1), Catch::Matchers::WithinAbs(1.0f, 0.001f));
    REQUIRE_THAT(motor1.setVelocityPWM(254), Catch::Matchers::WithinAbs(254.0f, 0.001f));
    REQUIRE_THAT(motor1.setVelocityPWM(255), Catch::Matchers::WithinAbs(255.0f, 0.001f));
    REQUIRE_THAT(motor1.setVelocityPWM(256), Catch::Matchers::WithinAbs(255.0f, 0.001f));
}

TEST_CASE("TEST_0009 - resulting PWM is limited to range 0-255 (default factor 0.9)", "[motor_control]")
{
    ChassisMotor motor1(ENA_PIN,
                        FORWARD1_PIN,
                        BACKWARD1_PIN,
                        0.9);

    REQUIRE_THAT(motor1.setVelocityPWM(-1), Catch::Matchers::WithinAbs(0.0f, 0.001f));
    REQUIRE_THAT(motor1.setVelocityPWM(0), Catch::Matchers::WithinAbs(0.0f, 0.001f));
    REQUIRE_THAT(motor1.setVelocityPWM(1), Catch::Matchers::WithinAbs(0.9f, 0.001f));
    REQUIRE_THAT(motor1.setVelocityPWM(283), Catch::Matchers::WithinAbs(254.7f, 0.001f));
    REQUIRE_THAT(motor1.setVelocityPWM(284), Catch::Matchers::WithinAbs(255.0f, 0.001f));
}

TEST_CASE("TEST_0010 - resulting PWM is limited to range 0-255 (default factor 0.1)", "[motor_control]")
{
    ChassisMotor motor1(ENA_PIN,
                        FORWARD1_PIN,
                        BACKWARD1_PIN,
                        0.1);

    REQUIRE_THAT(motor1.setVelocityPWM(-1), Catch::Matchers::WithinAbs(0.0f, 0.001f));
    REQUIRE_THAT(motor1.setVelocityPWM(0), Catch::Matchers::WithinAbs(0.0f, 0.001f));
    REQUIRE_THAT(motor1.setVelocityPWM(1), Catch::Matchers::WithinAbs(0.1f, 0.001f));
    REQUIRE_THAT(motor1.setVelocityPWM(2549), Catch::Matchers::WithinAbs(254.9f, 0.001f));
    REQUIRE_THAT(motor1.setVelocityPWM(2550), Catch::Matchers::WithinAbs(255.0f, 0.001f));
    REQUIRE_THAT(motor1.setVelocityPWM(2551), Catch::Matchers::WithinAbs(255.0f, 0.001f));
}