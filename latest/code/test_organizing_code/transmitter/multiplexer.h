#ifndef multiplexer_h
#define multiplexer_h

#include <arduino.h>

class multiplexer
{
    public:
        multiplexer(uint8_t signalPort);
        void setPinSelectors(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3);
        void setSignalPort(uint8_t value);
        void setControlPortStatus(uint8_t port);
        void getControlPortStatus(); 
        uint8_t getSignalPort();

    private:
        uint8_t selector[4];
        uint8_t signalPort;
};

#endif