// FAUXMO


// client to perform http requests
HTTPClient http;

// store the relays state (this estimation is only correct if usage is only via alexa)
bool SwitchState[sizeof(RFNames)];


void setupFauxmo()
{
  Serial.println("-setup FAUXMO");

  // not in use?
  if (sizeof(RFNames) == 0 && sizeof(HttpNames) == 0)
  {
    Serial.println("Fauxmo is disabled");
    return;
  }


  // start fauxmo library
  fauxmo.enable(true);

  int rfcount = sizeof(RFNames)/sizeof(char*);
  Serial.print("RF device count: ");
  Serial.println(rfcount);
  
  // Add virtual devices for RF
  for (int i = 0; i < rfcount; i = i + 1)
  {
    Serial.print("adding RF device: ");
    Serial.print(i);
    Serial.print(" name: ");
    Serial.println(RFNames[i]);

    fauxmo.addDevice(RFNames[i]);
  }
  
  
  int httpcount = sizeof(HttpNames)/sizeof(char*);
  Serial.print("HTTP device count: ");
  Serial.println(httpcount );
  
  // Add virtual devices for HTTP requests
  for (int i = 0; i < httpcount; i = i + 1)
  {
    Serial.print("adding HTTP device: ");
    Serial.print(i);
    Serial.print(" name: ");
    Serial.println(HttpNames[i]);

    fauxmo.addDevice(HttpNames[i]);
  }

  // add fauxmo callbacks
  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state)
  {
    Serial.printf("[MAIN] Device #%d (%s) state: %s\n", device_id, device_name, state ? "ON" : "OFF");

    // RF or HTTP ?
    if (device_id < sizeof(RFNames))
    {
      // RF
      sendRF(device_id, state);
    }
    else
    {
      // HTTP
      sendHTTP(device_id, state);
    }
  });

  fauxmo.onGetState([](unsigned char device_id, const char * device_name)
  {
    // state not supported yet for http devices
    if(device_id > sizeof(RFNames))
    {
      return false;
    }

    // send state of RF device
    return SwitchState[device_id];
  });

  Serial.println("-setup FAUXMO OK");
}


void sendRF(int device_id, bool state)
{
  int code = 0;

  if (state)
  {
    code = RFCodesOn[device_id];
  }
  else
  {
    code = RFCodesOff[device_id];
  }

  if (code != 0)
  {
    // send code - toggle switch
    rf_send(code);

    //store state for query
    SwitchState[device_id] = state;
  }
}

void sendHTTP(int device_id, bool state)
{
  Serial.println("sending http request");

  const char* url = HttpOn[device_id];
  if (!state)
  {
    url = HttpOff[device_id];
  }

  HTTPClient http;    //Declare object of class HTTPClient

  http.begin(url);      //Specify request destination
  //http.addHeader("Content-Type", "text/plain");  //Specify content-type header
  //int httpCode = http.POST("Message from ESP8266");   //Send the POST request
  int httpCode = http.GET();  // Send GET request
  Serial.print("httpCode: ");
  Serial.println(httpCode);   //Print HTTP return code
  if (httpCode > 0)
  { //Check the returning code
    String payload = http.getString();   //Get the request response payload
    Serial.println(payload);             //Print the response payload
  }

  http.end();  //Close connection
}

