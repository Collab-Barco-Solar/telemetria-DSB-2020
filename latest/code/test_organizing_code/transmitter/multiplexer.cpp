class multiplexer
{
    public:

        void setPinSelectors(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3)
        {
            multiplexer::selectors[0] = pin0;
            multiplexer::selectors[1] = pin1;
            multiplexer::selectors[2] = pin2;
            multiplexer::selectors[3] = pin3; 
        }
        void getControlPortStatus(bool portIn)
        {
            digitalWrite(, value);
        }   
        void setSignalPort(uint8_t value)
        {

        }
        uint8_t getSignalPort()
        {
            uint8_t pin;
            multiplexer::selectors[pos];
            return pin; 
        }

    private:

        uint8_t selectors[4];
        uint8_t SignalPort;
};

