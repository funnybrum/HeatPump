#include "HeatPump.h"

char buffer[4096];

WebServer::WebServer(Logger* logger, NetworkSettings* networkSettings)
    :WebServerBase(networkSettings, logger) {
}

void WebServer::registerHandlers() {
    server->on("/", std::bind(&WebServer::handle_root, this));
    server->on("/settings", std::bind(&WebServer::handle_settings, this));
    server->on("/get", std::bind(&WebServer::handle_get, this));
    server->on("/on", std::bind(&WebServer::handle_on, this));
    server->on("/off", std::bind(&WebServer::handle_off, this));
}

void WebServer::handle_root() {
    server->sendHeader("Location","/settings");
    server->send(303);
}

void WebServer::handle_settings() {
    wifi.parse_config_params(this);

    char network_settings[strlen_P(NETWORK_CONFIG_PAGE) + 32];
    wifi.get_config_page(network_settings);


    sprintf_P(
        buffer,
        CONFIG_PAGE,
        network_settings);
    server->send(200, "text/html", buffer);
}

void WebServer::handle_on() {
    digitalWrite(D1, HIGH);
    server->send(200);
}

void WebServer::handle_off() {
    digitalWrite(D1, LOW);
    server->send(200);
}

void WebServer::handle_get() {
    sprintf_P(buffer,
              GET_JSON,
              tempSensors.getDHWTankTemp(),
              tempSensors.getBufferTemp(),
              tempSensors.getInflowTemp(),
              tempSensors.getOutflowTemp(),
              0,
              0,
              0,
              0,
              WiFi.RSSI());
    server->send(200, "application/json", buffer);
}