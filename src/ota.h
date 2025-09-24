#ifndef OTA_H
#define OTA_H

#ifndef UNIT_TESTING
#include <ArduinoOTA.h>
#include <HTTPClient.h>
#include <Update.h>
#include <WiFiClient.h>
#endif // UNIT_TESTING

#include "configuration.h"

class OTA
{
private:
    std::string _otaUrl;
    std::string _md5Url;
    std::string _availableVersionUrl;

    /**
     * @brief Downloads the available version information.
     * @return String The available version as a string, or empty if failed.
     */
    std::string downloadAvailableVersion();

    /**
     * @brief Downloads the MD5 hash.
     * @return String The MD5 hash as a string, or empty if failed.
     */
    std::string downloadMD5();

    /**
     * @brief Downloads and applies the firmware update if the MD5 matches.
     * @param expectedMD5 The expected MD5 hash for the firmware file.
     * @return bool True if update was successful, false otherwise.
     */
    bool downloadAndUpdate(std::string expectedMD5);

public:
    /**
     * @brief OTA constructor with hostname, port, OTA URL, and MD5 URL.
     * @param otaUrl URL to the firmware binary file.
     * @param md5Url URL to the MD5 file for the firmware.
     * @param availableVersionUrl URL to the available version information file.
     */
    OTA(std::string otaUrl = "",
        std::string md5Url = "",
        std::string availableVersionUrl = "");

    /**
     * @brief Starts the OTA update process. Only updates if the MD5 matches.
     * @param currentVersion Currently flashed firmware version as string.
     */
    void begin(const char *currentVersion);
};

#endif // OTA_H