#pragma once

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>

#include "user_interface.h"

#include "DS18B20.h"
#include "HeatPump.h"
#include "CirculationPump.h"
#include "DhwTank.h"
#include "UFHPumpThermostat.h"
#include "DataCollector.h"

#include "esp8266-base.h"

#define HTTP_PORT 80
#define HOSTNAME "therma-v"

extern Logger logger;
extern Settings settings;
extern WiFiManager wifi;
extern DS18B20 tempSensors;
extern HeatPump heatPump;
extern CirculationPump ufhPump;
extern CirculationPump dhwPump;
extern DHWTank dhwTank;
extern DataCollector dataCollector;