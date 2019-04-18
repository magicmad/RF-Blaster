// RF


void setupRF()
{
  Serial.println("-setup RF");

  //setup Receiver
  rfLib.enableReceive(RF_RECEIVE_PIN);

  // setup Transmitter
  rfLib.enableTransmit(RF_TRANSMIT_PIN);

  // Optional set pulse length.
  rfLib.setPulseLength(360);

  // Optional set protocol (default is 1, will work for most outlets)
  // rfLib.setProtocol(2);

  // Optional set number of transmission repetitions.
  // rfLib.setRepeatTransmit(15);

  Serial.println("-setup RF - OK");
}


void rf_receive()
{
  // RF Receive
  if (rfLib.available())
  {
    //output(rfLib.getReceivedValue(), rfLib.getReceivedBitlength(), rfLib.getReceivedDelay(), rfLib.getReceivedRawdata(),rfLib.getReceivedProtocol());
    lastcode = rfLib.getReceivedValue();
    rfLib.resetAvailable();

    Serial.println("RF received: ");
    Serial.println(lastcode);

    String msg = String(lastcode);

    // send to mqtt
    mqttPublish(topicOutRec, msg, false);
  }
}


void rf_send(int code)
{
  rfLib.send(code, 24);
  Serial.print("RF send: ");
  Serial.println(code);

  // send to mqtt
  mqttPublish(topicOutSend, String(code), false);


  //TODO: check if code is from RF on or off code list - set fauxmo switchstate variable

  /* See Example: TypeA_WithDIPSwitches */
  //  rfLib.switchOn("11111", "00010");
  //  delay(1000);
  //  rfLib.switchOff("11111", "00010");
  //  delay(1000);

  /* Same switch as above, but using decimal code */
  //  rfLib.send(1394004, 24);
  //  delay(1000);
  //  rfLib.send(5396, 24);
  //  delay(1000);
  //
  //  /* Same switch as above, but using binary code */
  //  rfLib.send("000000000001010100010001");
  //  delay(1000);
  //  rfLib.send("000000000001010100010100");
  //  delay(1000);
  //
  //  /* Same switch as above, but tri-state code */
  //  rfLib.sendTriState("00000FFF0F0F");
  //  delay(1000);
  //  rfLib.sendTriState("00000FFF0FF0");
  //  delay(1000);

  //delay(20000);
}


