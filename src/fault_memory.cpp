#include "fault_memory.h"

// Requirement: https://github.com/trippedBit/autonomous-driving-robot-car/issues/44
FaultMemory::FaultMemory()
{
    //
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
    // Get EEPROM
    EEPROM.begin(512);

    // Update fault's EEPROM state
    EEPROM.write(eepromAddress, active);

    // Write back to EEPROM
    EEPROM.commit();
    EEPROM.end();
#endif // UNIT_TESTING
}
