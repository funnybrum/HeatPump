#pragma once

#include "SettingsBase.h"
#include "WiFi.h"

struct SettingsData {
    NetworkSettings network;
};

struct Empty {};

class Settings: public SettingsBase<SettingsData, Empty> {
    public:
        Settings();
        SettingsData* getSettings();

    protected:
        void initializeSettings();
        Empty* getRTCSettings();

    private:
        SettingsData settingsData;
};
