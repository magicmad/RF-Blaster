#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <RCSwitch.h>
#include "fauxmoESP.h"
#include "config.h"


// this library does all the wemo things
fauxmoESP fauxmo;

// use via browser
ESP8266WebServer server(80);

// network name
MDNSResponder mdns;

// rc stuff
RCSwitch mySwitch = RCSwitch();

// last received code
int lastcode;


void setup()
{
  // Initialize serial output
  Serial.begin(SERIAL_BAUDRATE);
  
  Serial.print("starting ");
  Serial.println(HOSTNAME);

  setupWifi();

  setupMDNS();

  setupWebServer();

  setupOTA();

  setupRF();

  setupFauxmo();

  Serial.println("--Setup OK");
  Serial.println("");
}

void loop()
{
  // perform Fauxmo actions
  fauxmo.handle();

  // perform MDNS actions
  mdns.update();

  // perform webserver actions
  server.handleClient();

  // perform OTA actions
  ArduinoOTA.handle();

  // RF Receive
  rf_receive();

  yield();
}
