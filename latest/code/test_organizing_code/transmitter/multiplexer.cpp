#include <arduino.h>
#include <multiplexer.h>

void multiplexer::setPinSelectors(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3)
{
    selector[0] = pin0;
    selector[1] = pin1;
    selector[2] = pin2;
    selector[3] = pin3; 
}
void multiplexer::setSignalPort(uint8_t value)
{
    signalPort = value;
} 
void setControlPortStatus(uint8_t port)
{
    pinMode(selector[0], port >> 0&1);
    pinMode(selector[1], port >> 1&1);
    pinMode(selector[2], port >> 2&1);
    pinMode(selector[3], port >> 3&1);
}
void multiplexer::getControlPortStatus()
{
    bool portIn;
    selector[4];
} 
uint8_t getSignalPort()
{
    uint8_t pin;
    pin = signalPort;
    return pin; 
}