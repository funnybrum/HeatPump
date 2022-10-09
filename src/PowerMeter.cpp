#include "Main.h"


PowerMeter::PowerMeter(uint32_t samplingIntervalMs) {
    _samplingIntervalMs = samplingIntervalMs;
    _lastReadMs = millis() - _samplingIntervalMs;

    for (int i = 0; i < 5; i++) {
        uint8_t crc_byte = crc(_commands[i].cmd, 6);
        _commands[i].cmd[6] = crc_byte;
        _commands[i].value = -1;
    }
}

void PowerMeter::begin() {
    _lastReadMs = millis() - _samplingIntervalMs;
}

bool PowerMeter::isInitialized() {
    return _commands[0].value >= -0.5;
}

void PowerMeter::loop() {
    if (isInitialized()) {
        if (millis() - _lastReadMs >= _samplingIntervalMs) {
            for (uint8_t i = 1; i < 5; i++) {
                _commands[i].pending = true;
            }
            _lastReadMs = millis();
        }
    } else {
        if (!_commands[0].inProgress && !_commands[0].pending) {
            _commands[0].pending = true;
        }
    }
    sendLoop();
    receiveLoop();
}

float PowerMeter::getPower() {
    return _commands[3].value;
}

float PowerMeter::getVoltage() {
    return _commands[1].value;
}

float PowerMeter::getCurrent() {
    return _commands[2].value;
}

float PowerMeter::getEnergy() {
    return _commands[4].value;
}

uint8_t PowerMeter::crc(uint8_t *data, uint8_t sz) {
    uint16_t crc = 0;
    for(uint8_t i=0; i<sz; i++)
        crc += *data++;
    return (uint8_t)(crc & 0xFF);
}

void PowerMeter::sendLoop() {
    for (uint8_t i = 0; i < 5; i++) {
        if (_commands[i].inProgress) {
            // A command is being executed. One command at a time.
            return;
        }
    }

    Command *cmd = NULL;
    for (uint8_t i = 0; i < 5; i++) {
        if (_commands[i].pending) {
            cmd = _commands + i;
            break;
        }
    }

    if (cmd == NULL) {
        // No pending commands.
        return;
    }

    while (Serial.available()) {
        Serial.read();
    }

    Serial.write(cmd->cmd, 7);

    cmd->inProgress = true;
    cmd->pending = false;
    // Set the command timeout.
    // 100ms+ main loop, 20 loops = 2+ second
    cmd->countdown = 20; 
}

void PowerMeter::receiveLoop() {
    Command *cmd = NULL;
    for (uint8_t i = 0; i < 5; i++) {
        if (_commands[i].inProgress) {
            cmd = _commands + i;
            break;
        }
    }


    if (cmd == NULL) {
        // No command in progress
        return;
    }

    if (Serial.available() < 7) {
        // Still not enough data in the buffer. Decrease the countdown and
        // if the command has timed out - break its execution.
        cmd->countdown--;
        if (cmd->countdown == 0) {
            logger.log("Timed out on %02X", cmd->cmd[0]);
            cmd->inProgress = false;
        }
        return;
    }

    // Read the command and verify the CRC.
    cmd->inProgress = false;

    uint8_t data[7];
    Serial.readBytes(data, 7);
    if (crc(data, 6) != data[6]) {
        logger.log("CRC failed on %02X", cmd->cmd[0]);
        logger.log("[%02X, %02X, %02X, %02X, %02X, %02X, %02X]", data[0], data[1], data[2], data[3], data[4], data[5], data[6]);
        return;
    }

    // Parse the command value. For integer commands this are 3 bytes
    // representing the integer value. For non-integer command thies
    // are 3 bytes - 2 representing the integar part and 1 for the decimal.
    if (cmd->isInteger) {
        cmd->value = (data[1]<<16) + (data[2]<<8) + data[3];
    } else {
        cmd->value = (data[1]<<8) + data[2] + (data[3]/100.0);
    }
}