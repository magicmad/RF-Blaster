# RF-Blaster

Control your RF Switches with Amazons Alexa or any browser.

Code for a ESP8266 (NodeMCU) based 433MHz RF code sender and receiver.
I recommend to use a WL101-341 board, powered by 5V to avoid range issues.
NOTE: after 12 months the sender module died. I now use 3.3V for the second module :)

I use it to control RF power outlets and light switches with Amazons Alexa or simple wget scripting.

Make sure to change the config file.

NOTE: sending http requests does not work yet due to a incompatibility between HttpClient and fauxmoesp.