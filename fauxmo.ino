// FAUXMO


// store the relays state
bool SwitchState[SWITCH_COUNT];


void setupFauxmo()
{
  // not in use
  if(SWITCH_COUNT == 0)
    return;
  
  
  // start fauxmo library
  fauxmo.enable(true);
  
  // Add virtual devices
  for (int i = 0; i < SWITCH_COUNT; i = i + 1)
  {
    fauxmo.addDevice(RelayNames[i]);
  }
  
  
  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state)
  {
    Serial.printf("[MAIN] Device #%d (%s) state: %s\n", device_id, device_name, state ? "ON" : "OFF");
    
    int code = 0;
    
    if(state)
    {
      code = RelayCodesOn[device_id];
    }
    else
    {
      code = RelayCodesOff[device_id];
    }
    
    if(code != 0)
    {
      // send code - toggle switch
      rf_send(code);
      
      //store state for query
      SwitchState[device_id] = state;
    }
  });
  
  
  fauxmo.onGetState([](unsigned char device_id, const char * device_name)
  {
    return SwitchState[device_id];
  });
}
