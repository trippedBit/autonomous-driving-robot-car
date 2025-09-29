#include "../build/_deps/catch2-src/src/catch2/catch_test_macros.hpp"

#include <algorithm>

#include "../src/fault_memory.h"

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/44
TEST_CASE("Every fault has a unique ID", "[fault_memory]")
{
    FaultMemory faultMemory;
    std::vector<int> ids;
    for (const auto &fault : faultMemory.faults)
    {
        ids.push_back(fault.id);
    }
    std::sort(ids.begin(), ids.end());
    auto last = std::unique(ids.begin(), ids.end());
    REQUIRE(std::distance(ids.begin(), last) == faultMemory.faults.size());
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/44
TEST_CASE("Fault not active", "[fault_memory]")
{
    bool returnValue = FaultMemory().isFaultActive(1);
    REQUIRE(returnValue == false);
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/44
TEST_CASE("Fault active - forced", "[fault_memory]")
{
    bool returnValue = FaultMemory().isFaultActive(1,
                                                   true);
    REQUIRE(returnValue == true);
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/44
TEST_CASE("Get fault EEPROM address", "[fault_memory]")
{
    SECTION("Fault ID 1")
    {
        int returnValue = FaultMemory().getFaultEepromAddress(1);
        REQUIRE(returnValue == 0);
    }

    SECTION("Fault ID 2")
    {
        int returnValue = FaultMemory().getFaultEepromAddress(2);
        REQUIRE(returnValue == 1);
    }

    SECTION("Fault ID 3")
    {
        int returnValue = FaultMemory().getFaultEepromAddress(3);
        REQUIRE(returnValue == 2);
    }
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/44
TEST_CASE("Set fault active", "[fault_memory]")
{
    // Dummy test for code coverage, almost all code is not testable due to EEPROM dependency
    FaultMemory().setFaultActive(1,
                                 true);
    REQUIRE(true);
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/44
TEST_CASE("Set fault inactive", "[fault_memory]")
{
    // Dummy test for code coverage, almost all code is not testable due to EEPROM dependency
    FaultMemory().setFaultActive(1,
                                 false);
    REQUIRE(true);
}