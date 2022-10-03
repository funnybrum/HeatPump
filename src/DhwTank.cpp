#include "Main.h"

DHWTank::DHWTank(uint8_t lowPin, uint8_t highPin) {
    this->_lowPin = lowPin;
    this->_highPin = highPin;
    this->_mode = DHWT_OFF;
    pinMode(_lowPin, OUTPUT);
    pinMode(_highPin, OUTPUT);
    loop();
}

void DHWTank::begin() {
}

void DHWTank::loop() {
    if (this->_mode == DHWT_OFF) {
        digitalWrite(_lowPin, LOW);
        digitalWrite(_highPin, LOW);
    } else if (this->_mode == DHWT_LOW) {
        digitalWrite(_lowPin, HIGH);
        digitalWrite(_highPin, LOW);
    } else if (this->_mode == DHWT_HIGH) {
        digitalWrite(_lowPin, LOW);
        digitalWrite(_highPin, HIGH);
    }
}

void DHWTank::setMode(DHWTankMode mode) {
    this->_mode = mode;
}

DHWTankMode DHWTank::getMode() {
    return this->_mode;
}
