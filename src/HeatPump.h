#pragma once

enum HeatPumpMode {
    HP_HEATING,
    HP_COOLING,
    HP_DHW_HEATING,
    HP_OFF
};

class HeatPump {
    public:
        HeatPump(uint8_t l1_coolingPin=D1, uint8_t l2_heatingPin=D2, uint8_t l3_DHWPin=D3);
        void begin();
        void loop();
        void setMode(HeatPumpMode mode);
        HeatPumpMode getMode();
    private:
        uint8_t _heatPin;
        uint8_t _coolPin;
        uint8_t _dhwPin;
        HeatPumpMode _mode = HP_OFF;
};
