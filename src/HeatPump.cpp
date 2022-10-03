#include "Main.h"

HeatPump::HeatPump(uint8_t l1_coolingPin, uint8_t l2_heatingPin, uint8_t l3_DHWPin) {
    this->_coolPin = l1_coolingPin;
    this->_heatPin = l2_heatingPin;
    this->_dhwPin = l3_DHWPin;
    setMode(HP_OFF);

    pinMode(_coolPin, OUTPUT);
    digitalWrite(_coolPin, LOW);
    pinMode(_heatPin, OUTPUT);
    digitalWrite(_heatPin,LOW);
    pinMode(_dhwPin, OUTPUT);
    digitalWrite(_dhwPin, LOW);
}

void HeatPump::setMode(HeatPumpMode mode) {
    this->_mode = mode;
}

void HeatPump::begin() {
}

void HeatPump::loop() {
    if (this->_mode != HP_COOLING) {
        digitalWrite(_coolPin, LOW);
    }

    if (this->_mode != HP_HEATING) {
        digitalWrite(_heatPin, LOW);
    }

    if (this->_mode != HP_DHW_HEATING) {
        digitalWrite(_dhwPin, LOW);
    }

    delay(10);

    if (this->_mode == HP_COOLING) {
        digitalWrite(_coolPin, HIGH);
    }

    if (this->_mode == HP_HEATING) {
        digitalWrite(_heatPin, HIGH);
    }

    if (this->_mode == HP_DHW_HEATING) {
        digitalWrite(_dhwPin, HIGH);
    }
}

HeatPumpMode HeatPump::getMode() {
    return this->_mode;
}