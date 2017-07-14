#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <RCSwitch.h>



ESP8266WebServer server(80);
MDNSResponder mdns;

RCSwitch mySwitch = RCSwitch();

int lastcode;


void setup()
{
  // Initialize serial
  Serial.begin(74880);
  Serial.println("starting ESP8266 RF-Blaster...");

  setupWifi();
  
  setupMDNS();
  
  setupWebServer();

  setupOTA();
  
  setupRF();
  
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
