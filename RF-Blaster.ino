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
  Serial.println("starting ESP8266 RF-Blaster...");

  setupWifi();
  
  setupMDNS();
  
  setupWebServer();

  setupOTA();
  
  setupRF();
  
  setupFauxmo();
  
  Serial.println("Setup OK");
  delay(100);
}

void loop()
{
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
