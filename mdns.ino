// MDNS


void setupMDNS()
{
  if(mdns.begin(HOSTNAME, WiFi.localIP()))
  {
      MDNS.addService("http", "tcp", 80); // Anounce the ESP as an HTTP service
      Serial.println("MDNS responder started");
  }
}
