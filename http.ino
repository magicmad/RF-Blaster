// HTTP SERVER

char http_passcode[40] = "xxx";






void setupWebServer()
{
  // Configure the server
  server.on("/send", []() {handleSend(); });

  server.on("/", []() { handleRoot(); });
  
  server.onNotFound ( handleNotFound );
  
  server.begin();
  Serial.println("HTTP Server started");
}

void handleRoot()
{
    String out = "<html><head><title>RC-BLASTER</title></head>";
    out += "<body>";
    out += "Ready to serve, master!";
    out += "<br>Last code was: ";
    out += lastcode;
    out += "</body>";
    out += "</html>";
    server.send(200, "text/html", out);
}

void handleSend()
{
  Serial.println("Connection received - Send");

  // check authorization
  if (server.arg("pass") != http_passcode)
  {
    Serial.println("Unauthorized access");
    server.send(401, "text/html", "Unauthorized");
  }
  else
  {
    if (server.hasArg("code")) {
      int code = server.arg("code").toInt();
      rf_send(code);
      server.send(200, "text/html", "code sent");
      Serial.print("code send:");
      Serial.println(code);
    }
    else
    {
      server.send(200, "text/html", "code error");
      Serial.println("code error");
    }
  }
}

void handleNotFound()
{
    Serial.println("connection - not found");
      
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for ( uint8_t i = 0; i < server.args(); i++ )
    {
        message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
    }
    server.send ( 404, "text/plain", message );
}
