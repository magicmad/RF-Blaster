// MDNS


void setupMDNS()
{
  Serial.println("-setup MDNS");

  if (mdns.begin(HOSTNAME, WiFi.localIP()))
  {
    MDNS.addService("http", "tcp", 80); // Anounce the ESP as an HTTP service
    Serial.println("-setup MDNS OK");
  }
}
