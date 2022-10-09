#include "Main.h"

uint8_t buffer_sensor_addr[8] = {0x28, 0x88, 0xC3, 0x96, 0xF0, 0x01, 0x3C, 0x85};
uint8_t dhw_high_sensor_addr[8] = {0x28, 0xB9, 0x10, 0x96, 0xF0, 0x01, 0x3C, 0x4F};
uint8_t dhw_low_sensor_addr[8] = {0x28, 0xFF, 0x64, 0x02, 0x19, 0x6C, 0x31, 0x72};
uint8_t inflow_sensor_addr[8] = {0x28, 0xF5, 0x60, 0x96, 0xF0, 0x01, 0x3C, 0x2A};
uint8_t outflow_sensor_addr[8] = {0x28, 0x53, 0x1C, 0x96, 0xF0, 0x01, 0x3C, 0x88};

DS18B20::DS18B20(uint8_t pin, uint32_t samplingIntervalMs) {
    _sensors = new DallasTemperature(new OneWire(pin));
}

void DS18B20::begin() {
    _sensors->begin();
    _lastReadMs = millis() - _samplingIntervalMs;

    uint8_t deviceCount = _sensors->getDeviceCount();
    DeviceAddress addr;
    char addr_str[64];
    _sensors->requestTemperatures();

    for (int i = 0; i < deviceCount; i++) {
        _sensors->getAddress(addr, i);
        sprintf(addr_str, "{0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X}", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], addr[6], addr[7]);
        logger.log("Sensor %d, address %s, temp %.1f", i, addr_str, _sensors->getTempCByIndex(i));
    }

    loop();
}

void DS18B20::loop() {
    if (millis() - _lastReadMs >= _samplingIntervalMs) {
        _sensors->requestTemperatures();
        _dhw_high_temp = _sensors->getTempC(dhw_high_sensor_addr);
        _dhw_low_temp = _sensors->getTempC(dhw_low_sensor_addr);
        _buffer_temp = _sensors->getTempC(buffer_sensor_addr);
        _inflow_temp = _sensors->getTempC(inflow_sensor_addr);
        _outflow_temp = _sensors->getTempC(outflow_sensor_addr);
        _lastReadMs += _samplingIntervalMs;
    }
}

float DS18B20::getInflowTemp() {
    return _inflow_temp;
}

float DS18B20::getOutflowTemp() {
    return _outflow_temp;
}

float DS18B20::getDHWTankLowTemp() {
    return _dhw_low_temp;
}

float DS18B20::getDHWTankHighTemp() {
    return _dhw_high_temp;
}

float DS18B20::getBufferTemp() {
    return _buffer_temp;
}
