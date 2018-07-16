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

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print (".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP address: ");
  Serial.println( WiFi.localIP() );

  Serial.println("-setup WIFI - OK");
}
