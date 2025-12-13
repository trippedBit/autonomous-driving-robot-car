#include "mocks.h"

std::map<int, double> analogPinValues;
std::map<int, int> digitalPinValues;
unsigned long mockMillisValue = 0;
unsigned long mockPulseInValue = 0;
std::map<int, PinMode> pinModes;

double mockAnalogRead(int pin)
{
    return analogPinValues[pin];
}

void mockAnalogWrite(int pin, double value)
{
    analogPinValues[pin] = value;
}

int mockDigitalRead(int pin)
{
    return digitalPinValues[pin];
}

void mockDigitalWrite(int pin, int state)
{
    digitalPinValues[pin] = state;
}

void mockDoNothing(unsigned long value)
{
    // do nothing
}

void mockPinMode(int pin, PinMode pinMode)
{
    pinModes[pin] = pinMode;
}

void setMockMillis(unsigned long value)
{
    mockMillisValue = value;
}

void setMockPulseIn(unsigned long desiredDistanceInMillimeter)
{
    mockPulseInValue = ((desiredDistanceInMillimeter / DISTANCE_METER_TO_MILLIMETER) / SPEED_OF_SOUND_METER_PER_SECOND * 2) / PULSE_MICROSECONDS_TO_SECONDS;
}

void MockSerial::print(std::string text)
{
    std::cout << text << std::endl;
}

void MockSerial::print(int value)
{
    std::cout << std::to_string(value) << std::endl;
}

void MockSerial::println(std::string text)
{
    print(text);
}

void MockSerial::println(double value)
{
    std::cout << std::to_string(value) << std::endl;
}