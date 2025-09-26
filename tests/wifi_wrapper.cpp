#include "../build/_deps/catch2-src/src/catch2/catch_test_macros.hpp"

#include "../src/configuration.h"
#include "../src/wifi_wrapper.h"

// Requirement: None
TEST_CASE("WiFi initialization", "[wifi_wrapper]")
{
    WiFiWrapper wifiWrapper(WIFI_NAME,
                            WIFI_PASSWORD,
                            WIFI_IP,
                            WIFI_DNS,
                            WIFI_GATEWAY,
                            WIFI_SUBNET);
    REQUIRE(true);
}

TEST_CASE("connectWiFi() dummy call", "[wifi_wrapper]")
{
    WiFiWrapper wifiWrapper(WIFI_NAME,
                            WIFI_PASSWORD,
                            WIFI_IP,
                            WIFI_DNS,
                            WIFI_GATEWAY,
                            WIFI_SUBNET);
    wifiWrapper.connectWiFi();
    REQUIRE(true);
}