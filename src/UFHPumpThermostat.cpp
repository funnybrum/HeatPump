#include "Main.h"

#define POST_RUN 10 * 60 * 1000

UFHPumpThermostat::UFHPumpThermostat() {    
}

void UFHPumpThermostat::begin() {
}

void UFHPumpThermostat::loop() {
    bool is_pump_needed = HP_HEATING == heatPump.getMode() || HP_COOLING == heatPump.getMode();
    if (is_pump_needed) {
        if (CP_OFF == ufhPump.getMode()) {
            ufhPump.setMode(CP_ON);
            _started_by_thermostat = true;
            _pump_off_timestamp = 0;
        }
    } else {
        if (CP_ON == ufhPump.getMode() && _started_by_thermostat) {
            // Pump was started by the "thermostat" logic

            if (_pump_off_timestamp == 0) {
                // Initiate countdown for turning off the pump
                _pump_off_timestamp = millis();
            }

            // Check if the countdown has passed
            if (millis() - POST_RUN > _pump_off_timestamp) {
                logger.log("Circulation pump off by thermostat");
                ufhPump.setMode(CP_OFF);
                _pump_off_timestamp = 0;
                _started_by_thermostat = false;
            }
        }
    } 
}