#include "Main.h"

Logger logger = Logger();
Settings settings = Settings();

WiFiManager wifi = WiFiManager(&logger, &settings.getSettings()->network);
DataCollector dataCollector = DataCollector();
WebServer webServer = WebServer(&logger, &settings.getSettings()->network);
DS18B20 tempSensors = DS18B20(D4, 1000);
HeatPump heatPump = HeatPump();
CirculationPump ufhPump = CirculationPump(D7);
CirculationPump dhwPump = CirculationPump(D8);
DHWTank dhwTank = DHWTank();

void setup()
{ 
    Serial.begin(74880);
    while (! Serial) {
        delay(1);
    }
    settings.begin();
    wifi.begin();
    webServer.begin();
    tempSensors.begin();
    dataCollector.begin();
    
    heatPump.begin();
    ufhPump.begin();
    dhwPump.begin();
    dhwTank.begin();

    wifi.connect();
}

void loop() {
    wifi.loop();
    webServer.loop();
    settings.loop();
    tempSensors.loop();
    dataCollector.loop();
    heatPump.loop();
    ufhPump.loop();
    dhwPump.loop();
    dhwTank.loop();

    delay(100);
}
