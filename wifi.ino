
const char* WIFI_SSID = "xxx";
const char* WIFI_PWD = "xxx";
const char* HOSTNAME = "RF-BLASTER";


// static IP
IPAddress ip(10,1,1,42);
IPAddress gateway(10,1,1,1);
IPAddress subnet(255,255,255,0);



void setupWifi()
{
  Serial.println("starting wifi setup.");
  
  // set mode
  WiFi.mode(WIFI_STA);
  
  // set hostname
  WiFi.hostname(HOSTNAME);
  
  // set ip
  WiFi.config(ip, gateway, subnet);
  
  WiFi.begin(WIFI_SSID, WIFI_PWD);
  
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
}

void setupMDNS()
{
  if(mdns.begin(HOSTNAME, WiFi.localIP()))
  {
      MDNS.addService("http", "tcp", 80); // Anounce the ESP as an HTTP service
      Serial.println("MDNS responder started");
  }
}
