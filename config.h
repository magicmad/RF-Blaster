//
// your settings
//


#define SERIAL_BAUDRATE 74880


// D1 = GPIO 5
// D2 = GPIO 4
// D3 = GPIO 0 (flash)

// RF sender module pin
#define RC_SEND_PIN 4
// RF receiver module pin
#define RC_RECEIVE_PIN 5


// WIFI access
#define WIFI_SSID "xxx"
#define WIFI_PASS "yyy"


// NETWORK
#define HOSTNAME "RF-BLASTER"
const IPAddress ip(10,1,1,42);
const IPAddress gateway(10,1,1,1);
const IPAddress subnet(255,255,255,0);


// WEBSERVER
#define HTTP_PASSCODE  "mysecretkey"


// OTA UPDATE
#define OTA_PASSWORD "mysecretkey"
#define OTA_PORT 8266


// Fauxmo
// set number of used switches and their on and off codes - make sure the array has the correct number of elements
#define SWITCH_COUNT 2
const char* RelayNames[] = { "Schalter eins", "Schalter zwei" };
const int RelayCodesOn[] = { 1234, 56789 };
const int RelayCodesOff[] = { 4576, 4576 };

