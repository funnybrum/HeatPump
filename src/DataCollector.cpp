#include "Main.h"
#include "DataCollector.h"

DataCollector::DataCollector():
    InfluxDBCollector(&logger,
                      NULL,
                      &settings.getSettings()->influxDB,
                      &settings.getSettings()->network) {
}

bool DataCollector::shouldCollect() {
    return millis() > 10000;
}

void DataCollector::collectData() {
    append("dhw_tank_low_temp", tempSensors.getDHWTankLowTemp(), 1);
    append("dhw_tank_high_temp", tempSensors.getDHWTankHighTemp(), 1);
    append("ufh_buffer_tank_temp", tempSensors.getBufferTemp(), 1);
    append("tp_heating", HP_HEATING == heatPump.getMode());
    append("tp_cooling", HP_COOLING == heatPump.getMode());
    append("tp_dhw_heating", HP_DHW_HEATING == heatPump.getMode());
    append("ufh_pump", CP_ON == ufhPump.getMode());
    append("dhw_gas_heating_pump", CP_ON == dhwPump.getMode());
    append("voltage", powerMeter.getVoltage(), 1);
    append("power", powerMeter.getPower(), 0);
    append("energy", powerMeter.getEnergy(), 0);
}

bool DataCollector::shouldPush() {
    return false;
}   

void DataCollector::onPush() {
}