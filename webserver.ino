// HTTP SERVER


void setupWebServer()
{
  Serial.println("-setup WebServer");

  // setup the webpages
  server.on("/send", []() {
    handleSend();
  });

  server.on("/", []() {
    handleRoot();
  });

  server.onNotFound ( handleNotFound );

  server.begin();

  Serial.println("-setup WebServer - OK");
}

void handleRoot()
{
  String out = "<html><head><title>";
  out += HOSTNAME;
  out += "</title></head>";
  out += "<body>";
  out += "Ready to serve, master!";
  out += "<br><br>Last received code was: ";
  out += lastcode;
  out += "<br><br>Send a code:<br>";
  out += "<form action='/send'>Password:<input type='text' name='pass'> Code:<input type='text' name='code'><input type='submit' value='send'></input></form>";
  out += "</body>";
  out += "</html>";
  server.send(200, "text/html", out);
}

void handleSend()
{
  Serial.println("Connection received");

  // check authorization
  if (!server.hasArg("pass") || server.arg("pass") != HTTP_PASSCODE)
  {
    Serial.println("Wrong Passcode! ACCESS DENIED");
    server.send(401, "text/html", "Unauthorized");
    return;
  }
  else
  {
    if (server.hasArg("code"))
    {
      int code = server.arg("code").toInt();

      rf_send(code);

      server.send(200, "text/html", "code sent");
      Serial.print("code send:");
      Serial.println(code);
    }
    else
    {
      server.send(200, "text/html", "code error");
      Serial.println("no code supplied error");
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
