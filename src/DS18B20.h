#pragma once

#include "stdint.h"
#include <DallasTemperature.h>

class DS18B20 {
    public:
        DS18B20(uint8_t pin, uint32_t samplingIntervalMs=1000);
        void begin();
        void loop();
        float getInflowTemp();
        float getOutflowTemp();
        float getBufferTemp();
        float getDHWTankLowTemp();
        float getDHWTankHighTemp();

    private:
        uint32_t _lastReadMs;
        uint32_t _samplingIntervalMs;
        DallasTemperature* _sensors;
        float _buffer_temp;
        float _dhw_high_temp;
        float _dhw_low_temp;
        float _inflow_temp;
        float _outflow_temp;
};
