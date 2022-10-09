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
UFHPumpThermostat uhfPumpThermostat = UFHPumpThermostat();
PowerMeter powerMeter = PowerMeter();

void setup()
{ 
    Serial.begin(9600);
    while (! Serial) {
        delay(1);
    }
    settings.begin();
    wifi.begin();
    webServer.begin();
    tempSensors.begin();
    powerMeter.begin();
    dataCollector.begin();
    
    heatPump.begin();
    ufhPump.begin();
    dhwPump.begin();
    dhwTank.begin();
    uhfPumpThermostat.begin();

    wifi.connect();
}

void loop() {
    wifi.loop();
    webServer.loop();
    settings.loop();
    tempSensors.loop();
    powerMeter.loop();
    dataCollector.loop();
    heatPump.loop();
    ufhPump.loop();
    dhwPump.loop();
    dhwTank.loop();
    uhfPumpThermostat.loop();

    delay(100);
}
