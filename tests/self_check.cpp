#include "../build/_deps/catch2-src/src/catch2/catch_test_macros.hpp"

#include "../src/self_check.h"

TEST_CASE("Self-check function exists and returns true", "[self_check]")
{
    // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/19
    bool result = selfCheck();
    REQUIRE(result == true);
}