#include "Main.h"

#define POST_RUN 10 * 60 * 1000

UFHPumpThermostat::UFHPumpThermostat() {    
}

void UFHPumpThermostat::begin() {
}

void UFHPumpThermostat::loop() {
    if (HP_HEATING == heatPump.getMode()) {
        if (CP_OFF == ufhPump.getMode()) {
            if (tempSensors.getBufferTemp() > 25) {
                ufhPump.setMode(CP_ON);
                _pump_off_timestamp = 0;
            }
        }
    } else {
        if (CP_ON == ufhPump.getMode()) {
            if (_pump_off_timestamp == 0) {
                _pump_off_timestamp = millis();
            }
            if (tempSensors.getBufferTemp() < 25 ||
                millis() - POST_RUN > _pump_off_timestamp) {
                // Two options:
                // 1) The buffer temp has fallen below 25C
                // 2) The pump was running for more than 10 minutes after the heat pump was turned off
                ufhPump.setMode(CP_OFF);
                _pump_off_timestamp = 0;
            }
        }
    }
}