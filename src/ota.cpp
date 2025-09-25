#include "ota.h"

/**
 * @brief Constructor for OTA class.
 *
 * Initializes OTA with the given OTA URL and MD5 URL.
 *
 * @param otaUrl URL for downloading the firmware.
 * @param md5Url URL for downloading the MD5 hash.
 * @param availableVersionUrl URL to the available version information file.
 */
OTA::OTA(std::string otaUrl,
         std::string md5Url,
         std::string availableVersionUrl)
{
  _otaUrl = otaUrl;
  _md5Url = md5Url;
  _availableVersionUrl = availableVersionUrl;
}

/**
 * @brief Downloads the available version information.
 * @return String The available version as a string, or empty if failed.
 */
std::string OTA::downloadAvailableVersion()
{
  std::string returnValue = "";

#ifndef UNIT_TESTING
  HTTPClient http;
  http.begin(_availableVersionUrl.c_str());
  int httpCode = http.GET();
  if (httpCode == 200)
  {
    std::string version = std::string(http.getString().c_str());

    Serial.print("Downloaded version before extracting (>VERSION<): >");
    Serial.print(version.c_str());
    Serial.println("<");
    Serial.print("Version length before extracting: ");
    Serial.println(std::to_string(version.length()).c_str());

    // Remove leading characters
    std::string substring = "VERSION = \"";
    std::size_t foundIndex = version.find(substring);
    if (foundIndex != std::string::npos)
    {
      foundIndex = foundIndex + substring.length();
      Serial.print("Trimming leading characters: ");
      Serial.println(std::to_string(foundIndex).c_str());
      Serial.print("First character to keep: ");
      Serial.println(version[foundIndex]);
      version = version.substr(foundIndex);
    }

    // Remove trailing characters
    substring = "\"";
    foundIndex = version.rfind(substring);
    if (foundIndex != std::string::npos)
    {
      Serial.print("Trimming trailing characters: ");
      Serial.println(std::to_string(foundIndex).c_str());
      Serial.print("Last character to keep: ");
      Serial.println(version[foundIndex] - 1);
      version = version.substr(0, foundIndex);
    }

    Serial.print("Downloaded version (>version<): >");
    Serial.print(version.c_str());
    Serial.println("<");
    Serial.print("Version length: ");
    Serial.println(std::to_string(version.length()).c_str());
    returnValue = version;
  }
  else
  {
    Serial.print("Failed to download version file. HTTP code: ");
    Serial.println(std::to_string(httpCode).c_str());
  }
  http.end();
#endif // UNIT_TESTING

  return returnValue;
}

/**
 * @brief Downloads the MD5 hash from the specified URL.
 *
 * @return The downloaded MD5 hash as a string, or an empty string if the download fails.
 */
std::string OTA::downloadMD5()
{
  std::string returnValue = "";

#ifndef UNIT_TESTING
  HTTPClient http;
  http.begin(_md5Url.c_str());
  int httpCode = http.GET();
  if (httpCode == 200)
  {
    std::string md5 = std::string(http.getString().c_str());

    Serial.print("Downloaded MD5 before trimming (>MD5<): >");
    Serial.print(md5.c_str());
    Serial.println("<");
    Serial.print("MD5 length before trimming: ");
    Serial.println(std::to_string(md5.length()).c_str());

    // Remove leading whitespace
    std::size_t foundIndex = md5.find_first_not_of(" \t\r\n");
    if (foundIndex != std::string::npos)
    {
      Serial.print("Trimming leading whitespace, first non-whitespace at index: ");
      Serial.println(std::to_string(foundIndex).c_str());
      Serial.print("First character to keep: ");
      Serial.println(md5[foundIndex]);
      md5 = md5.substr(foundIndex);
    }

    // Remove trailing whitespace
    foundIndex = md5.find_last_not_of(" \t\r\n");
    if (foundIndex != std::string::npos)
    {
      Serial.print("Trimming trailing whitespace, last non-whitespace at index: ");
      Serial.println(std::to_string(foundIndex).c_str());
      Serial.print("Last character to keep: ");
      Serial.println(md5[foundIndex]);
      md5 = md5.substr(0, foundIndex + 1);
    }

    Serial.print("Downloaded MD5 (>MD5<): >");
    Serial.print(md5.c_str());
    Serial.println("<");
    Serial.print("MD5 length: ");
    Serial.println(std::to_string(md5.length()).c_str());
    returnValue = md5;
  }
  else
  {
    Serial.print("Failed to download MD5 file. HTTP code: ");
    Serial.println(std::to_string(httpCode).c_str());
  }
  http.end();
#endif // UNIT_TESTING

  return returnValue;
}

/**
 * @brief Downloads the firmware and performs the OTA update.
 *
 * @param expectedMD5 The expected MD5 hash of the firmware.
 * @return True if the update is successful and the MD5 hash matches, false otherwise.
 */
bool OTA::downloadAndUpdate(std::string expectedMD5)
{
  bool returnValue = false;

#ifndef UNIT_TESTING
  Serial.print("Starting firmware download from: ");
  Serial.println(_otaUrl.c_str());
  HTTPClient http;
  http.begin(_otaUrl.c_str());
  int httpCode = http.GET();
  if (httpCode == 200)
  {
    int len = http.getSize();
    WiFiClient *stream = http.getStreamPtr();
    if (!Update.begin(len))
    {
      Serial.println("Not enough space for OTA update");
      http.end();
    }
    Update.setMD5(expectedMD5.c_str());
    size_t written = Update.writeStream(*stream);
    if (written == len && Update.end())
    {
      if (Update.md5String() == expectedMD5.c_str()) // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/40
      {
        Serial.println("OTA update successful and MD5 verified. Rebooting...");
        http.end();
        returnValue = true;
      }
      else
      {
        Serial.println("MD5 mismatch after update!");
      }
    }
    else
    {
      Serial.print("OTA update failed: ");
      Serial.println(Update.getError());
    }
  }
  else
  {
    Serial.print("Failed to download firmware. HTTP code: ");
    Serial.println(httpCode);
  }
  http.end();
#endif // UNIT_TESTING

  return returnValue;
}

/**
 * @brief Begins OTA update process and sets up OTA event handlers.
 * @param currentVersion Currently flashed firmware version as string.
 * @param unittestMD5 String MD5 to use during unittests.
 * @param unittestErrorDuringUpdate bool Indicates an error during update.
 * @return int Return code
 */
int OTA::begin(const char *currentVersion,
               std::string unittestMD5,
               bool unittestErrorDuringUpdate)
{
  if (!LOOP_FUNCTION_ENTERED) // Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/39
  {
#ifndef UNIT_TESTING
    Serial.println("Starting OTA update process");
#endif // UNIT_TESTING
    if (_otaUrl.length() > 0 && _md5Url.length() > 0 && _availableVersionUrl.length() > 0)
    {
      std::string availableVersion = downloadAvailableVersion();
#ifndef UNIT_TESTING
      Serial.print("Current version / available version: ");
      Serial.print(currentVersion);
      Serial.print(" / ");
      Serial.println(availableVersion.c_str());
#else
      availableVersion = "0.0.0a";
#endif // UNIT_TESTING

      if (currentVersion != availableVersion)
      {
        std::string md5 = downloadMD5();
#ifdef UNIT_TESTING
        md5 = unittestMD5;
#endif // UNIT_TESTING
        if (md5.length() == 32)
        {
          bool errorDuringUpdate = downloadAndUpdate(md5);
#ifdef UNIT_TESTING
          errorDuringUpdate = unittestErrorDuringUpdate;
#endif // UNIT_TESTING
          if (!errorDuringUpdate)
          {
#ifndef UNIT_TESTING
            ESP.restart();
#endif // UNIT_TESTING
            return 0;
          }
          else
          {
#ifndef UNIT_TESTING
            Serial.println("An error occured during update execution.");
#endif // UNIT_TESTING
            return -6;
          }
        }
        else
        {
#ifndef UNIT_TESTING
          Serial.println("Invalid or missing MD5 hash. OTA update aborted.");
#endif // UNIT_TESTING
          return -5;
        }
      }
      else
      {
#ifndef UNIT_TESTING
        Serial.println("No new version available, skipping OTA update.");
#endif // UNIT_TESTING
        return -4;
      }
    }
    else
    {
#ifndef UNIT_TESTING
      Serial.println("OTA URL or MD5 URL or Version URL not set. OTA update aborted.");
#endif // UNIT_TESTING
      return -3;
    }
  }
  else
  {
#ifndef UNIT_TESTING
    Serial.println("Loop function entered, skipping OTA update.");
#endif // UNIT_TESTING
    return -2;
  }
  // #endif       // UNIT_TESTING
  return -1; // Dummy end, should never be reached
}