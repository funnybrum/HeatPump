#pragma once

enum DHWTankMode {
    DHWT_OFF=0,
    DHWT_LOW=1,
    DHWT_HIGH=2
};

class DHWTank {
    public:
        DHWTank(uint8_t lowPin=D5, uint8_t highPin=D6);
        void begin();
        void loop();
        void setMode(DHWTankMode mode);
        DHWTankMode getMode();
    private:
        uint8_t _lowPin, _highPin;
        DHWTankMode _mode = DHWT_OFF;
};
