// WIFI


void setupWifi()
{
  Serial.println("-setup WIFI");

  // set mode
  WiFi.mode(WIFI_STA);

  // set hostname
  WiFi.hostname(HOSTNAME);

  // set ip
  WiFi.config(ip, gateway, subnet);

  if (WiFi.status() != WL_CONNECTED) { // FIX FOR USING 2.3.0 CORE (only .begin if not connected)
    WiFi.begin(WIFI_SSID, WIFI_PASS); // connect to the network
  }

  boolean state = true;
  int i = 0;

  // Wait for connection
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    // try for 10 seconds max
    if (i > 20) {
      state = false;
      break;
    }
    i++;
  }

  if (state)
  {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(WIFI_SSID);
    Serial.print("IP address: ");
    Serial.println( WiFi.localIP() );

    Serial.println("-setup WIFI - OK");
  }
  else
  {
    Serial.println("connection failed. retry in 60 seconds.");

    blinkled(10);

    // sleep 60 seconds
    delay(60000);
    // reboot
    ESP.restart();
  }
}

void scan_wifi_to_mqtt()
{
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
  {
    Serial.println("no networks found");
    mqttPublish(topicStatusOut, "test requested! I´m alive!", true);
  }
  else
  {
    String msg = String(n);
    msg += " networks found";
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      msg += String(i + 1);
      msg += ": ";
      msg += WiFi.SSID(i);
      msg += " (";
      msg += WiFi.RSSI(i);
      msg += ")";
      msg += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
    }
    mqttPublish(topicStatusOut, msg, true);
  }
  Serial.println("");
}
