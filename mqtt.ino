// MQTT



long lastMsg = 0;
char msg[50];
int value = 0;


// setup server connction and connect
void mqttSetup()
{
  Serial.println("-setup MQTT");

  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(callback);

  mqttReconnect();
}


// incoming messages
void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if (topic == topicStatusIn
      && length == 4)
  {
    if ((char)payload[0] == 't'
        && (char)payload[1] == 'e'
        && (char)payload[2] == 's'
        && (char)payload[3] == 't')
    {
      Serial.println("test request!");
      mqttPublish(topicStatusOut, "test requested! I´m alive!", true);
    }
    else if ((char)payload[0] == 's'
             && (char)payload[1] == 'c'
             && (char)payload[2] == 'a'
             && (char)payload[3] == 'n')
    {
      Serial.println("wifi scan request!");
      scan_wifi_to_mqtt();
    }
  }
  else if (topic == topicIn)
  {
    payload[length] = '\0';
    String s = String((char*)payload);
    int code = s.toInt();

    // codes to send
    rf_send(code);
  }
}


// connect to server and subscrive topics
void mqttReconnect()
{
  // Loop until we're reconnected
  while (!mqttClient.connected())
  {
    Serial.print("Attempting MQTT connection...");

    // Attempt to connect
    if (mqttClient.connect(HOSTNAME))
    {
      Serial.println("connected");

      // Once connected, publish an announcement...
      mqttPublish(topicStatusOut, "reconnect: I´m alive!", true);

      // ... and resubscribe
      mqttClient.subscribe(topicStatusIn);
      mqttClient.subscribe(topicIn);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());

      Serial.println(" try again in 5 seconds");

      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


// publish a message to the mqtt server
void mqttPublish(const char* chan, String text, bool addHostname)
{
  String msg = "";
  if (addHostname)
  {
    msg += String(HOSTNAME);
    msg += " ";
  }
  msg += text;
  msg += " ";

  // make a char array
  char b[msg.length() + 2];
  // copy string to array
  msg.toCharArray(b, msg.length());

  // publish
  mqttClient.publish(chan, b);
}
