#ifndef FAULT_MEMORY_H
#define FAULT_MEMORY_H

#include <string>
#include <vector>

#ifndef UNIT_TESTING
#include <EEPROM.h>
#endif // UNIT_TESTING

class FaultMemory
{
public:
    struct Fault
    {
        int id;
        std::string shortName;
        std::string description;
        std::string activeCondition;
        std::string inactiveCondition;
        int eepromAddress;
        int defaultValue;
    };

    // Structure: ID; Short name; Description; Active condition; Inactive condition; EEPROM address; Default value (= inactive)
    std::vector<Fault> faults = {
        {1,
         "Unexpected reset",
         "The system performed an unexpected reset. See https: // docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/misc_system_api.html#_CPPv418esp_reset_reason_t for a list of reasons.",
         "Reason not in [ESP_RST_POWERON, ESP_RST_SW]",
         "Reason in [ESP_RST_POWERON, ESP_RST_SW]",
         0,
         -1},
        {2,
         "Left motor check",
         "Left motor self check failed.",
         "leftMotorCheck == false",
         "leftMotorCheck == true",
         1,
         1},
        {3,
         "Right motor check",
         "Right motor self check failed.",
         "rightMotorCheck == false",
         "rightMotorCheck == true",
         2,
         1},
    };

    FaultMemory();
    int getFaultEepromAddress(int faultID);
    bool isFaultActive(int faultID,
                       bool unittestForceActive = false);
    void setFaultActive(int faultID, bool active);
};

#endif // FAULT_MEMORY_H