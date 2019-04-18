#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <RCSwitch.h>
#include "fauxmoESP.h"
#include <PubSubClient.h>
#include "config.h"


// this library does all the wemo things
fauxmoESP fauxmo;

// use via browser
ESP8266WebServer server(80);

// network name
MDNSResponder mdns;

// MQTT
WiFiClient espWifiClient;
PubSubClient mqttClient(espWifiClient);


// rc stuff
RCSwitch rfLib = RCSwitch();

// last received code
int lastcode = 0;


void setup()
{
  // Initialize serial output
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println();

  Serial.print("starting ");
  Serial.println(HOSTNAME);


  setupWifi();

  mqttSetup();

  setupMDNS();

  setupWebServer();

  setupOTA();

  setupRF();

  setupFauxmo();

  Serial.println("--Setup OK");
  Serial.println("");

  blinkled(3);
}


void loop()
{
  // re connect wifi if down
  if (WiFi.status() != WL_CONNECTED) {
    setupWifi();
  }

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


void blinkled(int count)
{
  // clear serial data
  Serial.flush();
  delay(100);

  pinMode(LED_BUILTIN, OUTPUT);         // Initialize the LED_BUILTIN pin as an output

  for (int i = 0; i < count; i++)
  {
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
    if (i + 1 < count)
      delay(500);
  }

  // Initialize serial output
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println();
}
