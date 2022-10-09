#pragma once

struct Command {
    uint8_t cmd[7];
    bool pending;
    bool inProgress;
    uint8_t countdown;
    float value;
    bool isInteger;
};

class PowerMeter {
    public:
        // Each value takes ~650ms to read. 4 values take ~3 seconds.
        // Going for sampling interval smaller than 2.5 seconds will likely
        // result in failure to read all points. 
        PowerMeter(uint32_t samplingIntervalMs=5000);
        void begin();
        void loop();
        float getPower();
        float getVoltage();
        float getCurrent();
        float getEnergy();
    private:
        uint8_t crc(uint8_t *data, uint8_t size);
        void sendLoop();
        void receiveLoop();
        bool isInitialized();

        Command _commands[5] = {
            Command{{0xB4, 0x80, 0x80, 0x80, 0x80, 0x00, 0x1F}, true,  false, 0, -1.0f, false}, // set address
            Command{{0xB0, 0x80, 0x80, 0x80, 0x80, 0x00, 0x1F}, false, false, 0, -1.0f, false},  // get voltage
            Command{{0xB1, 0x80, 0x80, 0x80, 0x80, 0x00, 0x1F}, false, false, 0, -1.0f, false},  // get current
            Command{{0xB2, 0x80, 0x80, 0x80, 0x80, 0x00, 0x1F}, false, false, 0, -1.0f, false},  // get power
            Command{{0xB3, 0x80, 0x80, 0x80, 0x80, 0x00, 0x1F}, false, false, 0, -1.0f, true}    // get energy
        };

        uint32_t _lastReadMs;
        uint32_t _samplingIntervalMs;
};