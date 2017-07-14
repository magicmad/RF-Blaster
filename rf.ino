
// D1 = GPIO 5
// D2 = GPIO 4
// D3 = GPIO 0 (flash)

const uint rc_receive_pin = 5;
const uint rc_send_pin = 4;


void setupRF()
{
  //setup Receiver
  mySwitch.enableReceive(rc_receive_pin);
  
  // setup Transmitter 
  mySwitch.enableTransmit(rc_send_pin);

  // Optional set pulse length.
  mySwitch.setPulseLength(360);
  
  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);
  
  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(15);

  Serial.println("RF setup OK");
}
  
void rf_receive()
{
  // RF Receive
  if (mySwitch.available())
  {
    //output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
    lastcode = mySwitch.getReceivedValue();
    mySwitch.resetAvailable();
    
    Serial.println("RF received: ");
    Serial.println(lastcode);
  }
}


void rf_send(int code)
{
  mySwitch.send(code, 24);
  Serial.print("RF send: ");
  Serial.println(code);

  

  /* See Example: TypeA_WithDIPSwitches */
//  mySwitch.switchOn("11111", "00010");
//  delay(1000);
//  mySwitch.switchOff("11111", "00010");
//  delay(1000);

  /* Same switch as above, but using decimal code */
//  mySwitch.send(1394004, 24);
//  delay(1000);  
//  mySwitch.send(5396, 24);
//  delay(1000);  
//
//  /* Same switch as above, but using binary code */
//  mySwitch.send("000000000001010100010001");
//  delay(1000);  
//  mySwitch.send("000000000001010100010100");
//  delay(1000);
//
//  /* Same switch as above, but tri-state code */ 
//  mySwitch.sendTriState("00000FFF0F0F");
//  delay(1000);  
//  mySwitch.sendTriState("00000FFF0FF0");
//  delay(1000);

  //delay(20000);
}


