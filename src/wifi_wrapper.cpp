#include "wifi_wrapper.h"

/**
 * @brief Constructor for WiFiWrapper class.
 *
 * Initializes WiFi credentials and network configuration.
 *
 * @param WIFI_NAME WiFi SSID.
 * @param WIFI_PASSWORD WiFi password.
 * @param ip Static IP address.
 * @param dns DNS server address.
 * @param gateway Gateway address.
 * @param subnet Subnet mask.
 */
WiFiWrapper::WiFiWrapper(std::string WIFI_NAME,
                         std::string WIFI_PASSWORD,
                         std::array<int, 4> ip,
                         std::array<int, 4> dns,
                         std::array<int, 4> gateway,
                         std::array<int, 4> subnet)
{
    _WIFI_NAME = WIFI_NAME;         // Store the WiFi name
    _WIFI_PASSWORD = WIFI_PASSWORD; // Store the WiFi password
    _ip = ip;                       // Store the static IP address
    _dns = dns;                     // Store the DNS server address
    _gateway = gateway;             // Store the gateway address
    _subnet = subnet;               // Store the subnet mask
}

/**
 * @brief Connects to the configured WiFi network and logs connection details.
 *
 * No parameters. No return value.
 */
void WiFiWrapper::connectWiFi(void)
{
#ifndef UNIT_TESTING
    IPAddress ip(_ip[0], _ip[1], _ip[2], _ip[3]);
    IPAddress dns(_dns[0], _dns[1], _dns[2], _dns[3]);
    IPAddress gateway(_gateway[0], _gateway[1], _gateway[2], _gateway[3]);
    IPAddress subnet(_subnet[0], _subnet[1], _subnet[2], _subnet[3]);

    WiFi.config(ip, dns, gateway, subnet);
    WiFi.begin(_WIFI_NAME.c_str(), _WIFI_PASSWORD.c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Trying to connect to WiFi with following configuration...");
        Serial.print("WiFi IP: ");
        Serial.println(ip);
        Serial.print("WiFi DNS: ");
        Serial.println(dns);
        Serial.print("WiFi Gateway: ");
        Serial.println(gateway);
        Serial.print("WiFi Subnet: ");
        Serial.println(subnet);
        delay(1000);
    }
#endif // UNIT_TESTING
}
