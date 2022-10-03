#pragma once

enum CirculatonPumpMode {
    CP_OFF,
    CP_ON
};

class CirculationPump {
    public:
        CirculationPump(uint8_t pin);
        void begin();
        void loop();
        void setMode(CirculatonPumpMode mode);
        CirculatonPumpMode getMode();
    private:
        uint8_t _pin;
        CirculatonPumpMode _mode = CP_OFF;
};
