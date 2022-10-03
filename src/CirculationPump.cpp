#include "Main.h"

CirculationPump::CirculationPump(uint8_t pin) {
    this->_pin = pin;
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

void CirculationPump::begin() {
}

void CirculationPump::loop() {
    digitalWrite(_pin, (this->_mode == CP_ON)?HIGH:LOW);
}

void CirculationPump::setMode(CirculatonPumpMode mode) {
    this->_mode = mode;
}

CirculatonPumpMode CirculationPump::getMode() {
    return this->_mode;
}