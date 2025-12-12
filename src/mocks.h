#ifndef MOCKS_H
#define MOCKS_H

#include <iostream>
#include <map>

enum class PinMode
{
    OUTPUT,
    INPUT
};

// Variables
extern unsigned long mockMillisValue;
extern std::map<int, double> analogPinValues;
extern std::map<int, int> digitalPinValues;
extern std::map<int, PinMode> pinModes;

// classless functions
double mockAnalogRead(int pin);
void mockAnalogWrite(int pin, double value);
int mockDigitalRead(int pin);
void mockDigitalWrite(int pin, int state);
void mockPinMode(int pin, PinMode pinMode);
void setMockMillis(unsigned long value);

// classes
class MockSerial
{
public:
    void print(std::string text);
    void print(int value);
    void println(std::string text);
    void println(double value);
};

#ifdef UNIT_TESTING
#define analogRead(pin) mockAnalogRead(pin)
#define analogWrite(pin, value) mockAnalogWrite(pin, value)
#define digitalRead(pin) mockDigitalRead(pin)
#define digitalWrite(pin, value) mockDigitalWrite(pin, value)
#define millis() mockMillisValue
#define HIGH 1
#define LOW 0
#define OUTPUT PinMode::OUTPUT
#define pinMode(pin, pinMode) mockPinMode(pin, pinMode)
#define Serial MockSerial()

#else
#define analogRead(pin) analogRead(pin)
#define analogWrite(pin, value) analogWrite(pin, value)
#define digitalRead(pin) digitalRead(pin)
#define digitalWrite(pin, value) digitalWrite(pin, value)
#define millis() originalMillis()
#define HIGH HIGH
#define LOW LOW
#define OUTPUT OUTPUT
#define pinMode(pin, pinMode) pinMode(pin, pinMode)
#define Serial Serial
#endif // UNIT_TESTING

#endif // MOCKS_H