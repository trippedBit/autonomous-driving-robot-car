#include "mocks.h"

unsigned long mockMillisValue = 0;
std::map<int, double> analogPinValues;
std::map<int, int> digitalPinValues;
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

void mockPinMode(int pin, PinMode pinMode)
{
    pinModes[pin] = pinMode;
}

unsigned long originalMillis()
{
    return ::millis();
}

void setMockMillis(unsigned long value)
{
    mockMillisValue = value;
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