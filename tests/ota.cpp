#include "../build/_deps/catch2-src/src/catch2/catch_test_macros.hpp"

#include "../src/configuration.h"
#include "../src/ota.h"

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/37
// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/40
TEST_CASE("Perform OTA update - all ok", "[ota]")
{
    OTA ota("Firmware URL",
            "MD5 URL",
            "Availabe version information URL");
    LOOP_FUNCTION_ENTERED = false;
    int returnValue = ota.begin("0.0.0b",
                                "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    REQUIRE(returnValue == 0);
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/37
// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/39
TEST_CASE("Perform OTA update - loop function entered", "[ota]")
{
    OTA ota("Firmware URL",
            "MD5 URL",
            "Availabe version information URL");
    LOOP_FUNCTION_ENTERED = true;
    int returnValue = ota.begin("0.0.0a");
    REQUIRE(returnValue == -2);
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/37
TEST_CASE("Perform OTA update - URL not set", "[ota]")
{
    std::string firmwareURL = "";
    std::string md5URL = "";
    std::string availableVersionURL = "";

    SECTION("All URLs not set")
    {
        OTA ota(firmwareURL,
                md5URL,
                availableVersionURL);
        LOOP_FUNCTION_ENTERED = false;
        int returnValue = ota.begin("0.0.0a");
        REQUIRE(returnValue == -3);
    }

    SECTION("Only firmware URL set")
    {
        firmwareURL = "a";
        OTA ota(firmwareURL,
                md5URL,
                availableVersionURL);
        LOOP_FUNCTION_ENTERED = false;
        int returnValue = ota.begin("0.0.0a");
        REQUIRE(returnValue == -3);
    }

    SECTION("Only md5 URL set")
    {
        md5URL = "a";
        OTA ota(firmwareURL,
                md5URL,
                availableVersionURL);
        LOOP_FUNCTION_ENTERED = false;
        int returnValue = ota.begin("0.0.0a");
        REQUIRE(returnValue == -3);
    }

    SECTION("Only available version URL set")
    {
        availableVersionURL = "a";
        OTA ota(firmwareURL,
                md5URL,
                availableVersionURL);
        LOOP_FUNCTION_ENTERED = false;
        int returnValue = ota.begin("0.0.0a");
        REQUIRE(returnValue == -3);
    }

    SECTION("Firmware URL and md5 URL set")
    {
        firmwareURL = "a";
        md5URL = "b";
        OTA ota(firmwareURL,
                md5URL,
                availableVersionURL);
        LOOP_FUNCTION_ENTERED = false;
        int returnValue = ota.begin("0.0.0a");
        REQUIRE(returnValue == -3);
    }

    SECTION("Firmware URL and available version URL set")
    {
        firmwareURL = "a";
        availableVersionURL = "b";
        OTA ota(firmwareURL,
                md5URL,
                availableVersionURL);
        LOOP_FUNCTION_ENTERED = false;
        int returnValue = ota.begin("0.0.0a");
        REQUIRE(returnValue == -3);
    }

    SECTION("md5 URL and available version URL set")
    {
        md5URL = "a";
        availableVersionURL = "b";
        OTA ota(firmwareURL,
                md5URL,
                availableVersionURL);
        LOOP_FUNCTION_ENTERED = false;
        int returnValue = ota.begin("0.0.0a");
        REQUIRE(returnValue == -3);
    }

    SECTION("Firmware URL and md5 URL set")
    {
        firmwareURL = "a";
        md5URL = "b";
        OTA ota(firmwareURL,
                md5URL,
                availableVersionURL);
        LOOP_FUNCTION_ENTERED = false;
        int returnValue = ota.begin("0.0.0a");
        REQUIRE(returnValue == -3);
    }
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/37
TEST_CASE("Perform OTA update - no new version available", "[ota]")
{
    OTA ota("Firmware URL",
            "MD5 URL",
            "Availabe version information URL");
    LOOP_FUNCTION_ENTERED = false;
    int returnValue = ota.begin("0.0.0a");
    REQUIRE(returnValue == -4);
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/37
// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/40
TEST_CASE("Perform OTA update - invalid or missing MD5", "[ota]")
{
    OTA ota("Firmware URL",
            "MD5 URL",
            "Availabe version information URL");
    LOOP_FUNCTION_ENTERED = false;
    int returnValue = ota.begin("0.0.0b",
                                "");
    REQUIRE(returnValue == -5);
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/37
// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/40
TEST_CASE("Perform OTA update - error during update", "[ota]")
{
    OTA ota("Firmware URL",
            "MD5 URL",
            "Availabe version information URL");
    LOOP_FUNCTION_ENTERED = false;
    int returnValue = ota.begin("0.0.0b",
                                "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
                                true);
    REQUIRE(returnValue == -6);
}
