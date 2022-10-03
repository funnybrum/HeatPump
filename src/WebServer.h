#pragma once

#include "Main.h"
#include "WebServerBase.h"
#include "WebPages.h"

class WebServer: public WebServerBase {
    public:
        WebServer(Logger* logger, NetworkSettings* networkSettings);
        void registerHandlers();
        void handle_root();
        void handle_get();
        void handle_settings();
        void handle_reset();

        void handle_pumpHeat();
        void handle_pumpCool();
        void handle_pumpDHWHeat();
        void handle_pumpOff();

        void handle_ufhPumpOn();
        void handle_ufhPumpOff();

        void handle_dhwPumpOn();
        void handle_dhwPumpOff();

        void handle_dhwTankOff();
        void handle_dhwTankLow();
        void handle_dhwTankHigh();
};
