#ifndef WIFI_WRAPPER_H
#define WIFI_WRAPPER_H

#include <array>
#include <string>

#ifndef UNIT_TESTING
#include <WiFi.h>
#endif // UNIT_TESTING

class WiFiWrapper
{
private:
    std::string _WIFI_NAME;
    std::string _WIFI_PASSWORD;
    std::array<int, 4> _ip;
    std::array<int, 4> _dns;
    std::array<int, 4> _gateway;
    std::array<int, 4> _subnet;

public:
    WiFiWrapper(std::string WIFI_NAME,
                std::string WIFI_PASSWORD,
                std::array<int, 4> ip,
                std::array<int, 4> dns,
                std::array<int, 4> gateway,
                std::array<int, 4> subnet);
    void connectWiFi(void);
};

#endif // WIFI_WRAPPER_H
