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
const char* HOSTNAME = "RF-BLASTER";

const IPAddress ip(10,1,1,42);
const IPAddress gateway(10,1,1,1);
const IPAddress subnet(255,255,255,0);


// WEBSERVER
#define HTTP_PASSCODE  "mysecretkey"


// OTA UPDATE
#define OTA_PASSWORD "mysecretkey"
#define OTA_PORT 8266


// Fauxmo - Wemos switch simulation
// set number of used switches and their on and off codes - make sure the array has the correct number of elements
#define SWITCH_COUNT 4
const char* RelayNames[] = { "Badezimmerlicht", "Schlafzimmerlicht", "Arbeitszimmerlicht", "Küchenlicht" };
const int RelayCodesOn[] = { 11144421, 11144431, 11144441, 1381719 };
const int RelayCodesOff[] = { 11144422, 11144432, 11144442, 1381716 };

