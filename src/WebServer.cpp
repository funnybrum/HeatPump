#include "Main.h"

char buffer[4096];

WebServer::WebServer(Logger* logger, NetworkSettings* networkSettings)
    :WebServerBase(networkSettings, logger) {
}

void WebServer::registerHandlers() {
    server->on("/", std::bind(&WebServer::handle_root, this));
    server->on("/settings", std::bind(&WebServer::handle_settings, this));
    server->on("/get", std::bind(&WebServer::handle_get, this));

    server->on("/heat-pump/heat", std::bind(&WebServer::handle_pumpHeat, this));
    server->on("/heat-pump/cool", std::bind(&WebServer::handle_pumpCool, this));
    server->on("/heat-pump/dhw-heat", std::bind(&WebServer::handle_pumpDHWHeat, this));
    server->on("/heat-pump/off", std::bind(&WebServer::handle_pumpOff, this));

    server->on("/ufh-pump/on", std::bind(&WebServer::handle_ufhPumpOn, this));
    server->on("/ufh-pump/off", std::bind(&WebServer::handle_ufhPumpOff, this));

    server->on("/dhw-pump/on", std::bind(&WebServer::handle_dhwPumpOn, this));
    server->on("/dhw-pump/off", std::bind(&WebServer::handle_dhwPumpOff, this));

    server->on("/dhw-tank/off", std::bind(&WebServer::handle_dhwTankOff, this));
    server->on("/dhw-tank/low", std::bind(&WebServer::handle_dhwTankLow, this));
    server->on("/dhw-tank/high", std::bind(&WebServer::handle_dhwTankHigh, this));
}

void WebServer::handle_root() {
    server->sendHeader("Location","/settings");
    server->send(303);
}

void WebServer::handle_settings() {
    wifi.parse_config_params(this);
    dataCollector.parse_config_params(this);

    char network_settings[strlen_P(NETWORK_CONFIG_PAGE) + 32];
    wifi.get_config_page(network_settings);

    char influx_settings[strlen_P(INFLUXDB_CONFIG_PAGE) + 64];
    dataCollector.get_config_page(influx_settings);

    sprintf_P(
        buffer,
        CONFIG_PAGE,
        network_settings,
        influx_settings);
    server->send(200, "text/html", buffer);
}

void WebServer::handle_pumpHeat() {
    heatPump.setMode(HP_HEATING);
    server->send(200);
}

void WebServer::handle_pumpCool() {
    heatPump.setMode(HP_COOLING);
    server->send(200);
}

void WebServer::handle_pumpDHWHeat() {
    heatPump.setMode(HP_DHW_HEATING);
    server->send(200);
}

void WebServer::handle_pumpOff() {
    heatPump.setMode(HP_OFF);
    server->send(200);
}

void WebServer::handle_ufhPumpOn() {
    ufhPump.setMode(CP_ON);
    server->send(200);
}

void WebServer::handle_ufhPumpOff() {
    ufhPump.setMode(CP_OFF);
    server->send(200);
}

void WebServer::handle_dhwPumpOn() {
    dhwPump.setMode(CP_ON);
    server->send(200);
}

void WebServer::handle_dhwPumpOff() {
    dhwPump.setMode(CP_OFF);
    server->send(200);
}

void WebServer::handle_dhwTankOff() {
    dhwTank.setMode(DHWT_OFF);
    server->send(200);
}

void WebServer::handle_dhwTankLow() {
    dhwTank.setMode(DHWT_LOW);
    server->send(200);
}

void WebServer::handle_dhwTankHigh() {
    dhwTank.setMode(DHWT_HIGH);
    server->send(200);
}

void WebServer::handle_get() {
    sprintf_P(buffer,
              GET_JSON,
              tempSensors.getDHWTankLowTemp(),
              tempSensors.getDHWTankHighTemp(),
              tempSensors.getBufferTemp(),
              tempSensors.getInflowTemp(),
              tempSensors.getOutflowTemp(),
              heatPump.getMode() == HP_HEATING,
              heatPump.getMode() == HP_COOLING,
              heatPump.getMode() == HP_DHW_HEATING,
              dhwTank.getMode(),
              dhwPump.getMode() == CP_ON,
              ufhPump.getMode() == CP_ON,
              WiFi.RSSI());
    server->send(200, "application/json", buffer);
}