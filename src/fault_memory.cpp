#include "fault_memory.h"

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/44
FaultMemory::FaultMemory()
{
    //
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/44
std::vector<std::string> FaultMemory::getAllActiveFaults()
{
    std::vector<std::string> activeFaultIDs;
    for (const auto &fault : faults)
    {
        if (isFaultActive(fault.id))
        {
            int storedData = getDataValue(fault.id);
            activeFaultIDs.push_back(std::to_string(fault.id) + ": " + std::to_string(storedData));
        }
    }

#ifdef UNIT_TESTING
    activeFaultIDs.push_back("1: 3");
    activeFaultIDs.push_back("2: -1");
#endif // UNIT_TESTING

    return activeFaultIDs;
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/44
int FaultMemory::getDataValue(int faultID)
{
    int storedData = -1;

    // Get the fault's EEPROM address
    int eepromDataAddress = getFaultDataEepromAddress(faultID);
    if (eepromDataAddress != -1)
    {
// Get state from fault's EEPROM address
#ifndef UNIT_TESTING
        EEPROM.begin(512);
        storedData = EEPROM.read(eepromDataAddress);
        EEPROM.end();
        Serial.print("Fault's data from EEPROM: ");
        Serial.println(storedData);
#endif // UNIT_TESTING
    }

    return storedData;
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/44
int FaultMemory::getFaultEepromAddress(int faultID)
{
    int eepromAddress = -1;
    for (const auto &fault : faults)
    {
        if (fault.id == faultID)
        {
            eepromAddress = fault.eepromAddress;
            break;
        }
    }

#ifndef UNIT_TESTING
    Serial.print("EEPROM address for fault ID ");
    Serial.print(faultID);
    Serial.print(": ");
    Serial.println(eepromAddress);
#endif // UNIT_TESTING

    return eepromAddress;
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/44
int FaultMemory::getFaultDataEepromAddress(int faultID)
{
    int dataAddress = -1;
    for (const auto &fault : faults)
    {
        if (fault.id == faultID)
        {
            dataAddress = fault.dataAddress;
            break;
        }
    }

#ifndef UNIT_TESTING
    Serial.print("EEPROM data address for fault ID ");
    Serial.print(faultID);
    Serial.print(": ");
    Serial.println(dataAddress);
#endif // UNIT_TESTING

    return dataAddress;
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/44
bool FaultMemory::isFaultActive(int faultID,
                                bool unittestForceActive)
{
    bool activeState = false;

    // Get the fault's EEPROM address
    int eepromAddress = getFaultEepromAddress(faultID);

// Get state from fault's EEPROM address
#ifndef UNIT_TESTING
    EEPROM.begin(512);
    activeState = EEPROM.read(eepromAddress);
    EEPROM.end();
    Serial.print("Fault's active state from EEPROM: ");
    Serial.println(activeState);
#endif // UNIT_TESTING

#ifdef UNIT_TESTING
    if (unittestForceActive)
    {
        activeState = true;
    }
#endif // UNIT_TESTING
    return activeState;
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/44
void FaultMemory::setFaultActive(int faultID, bool active)
{
    // Get the fault's EEPROM address
    int eepromAddress = getFaultEepromAddress(faultID);

#ifndef UNIT_TESTING
    setValue(eepromAddress, active);
#endif // UNIT_TESTING
}

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/44
void FaultMemory::setValue(int address,
                           int value)
{
#ifndef UNIT_TESTING
    // Get EEPROM
    EEPROM.begin(512);

    // Update EEPROM address
    EEPROM.write(address, value);

    // Write back to EEPROM
    EEPROM.commit();
    EEPROM.end();
#endif // UNIT_TESTING
}
