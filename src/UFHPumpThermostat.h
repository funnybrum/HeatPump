#pragma once

class UFHPumpThermostat {
    public:
        UFHPumpThermostat();
        void begin();
        void loop();
    private:
        uint32_t _pump_off_timestamp = 0;
};
