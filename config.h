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

const IPAddress ip(10, 1, 1, 42);
const IPAddress gateway(10, 1, 1, 1);
const IPAddress subnet(255, 255, 255, 0);


// WEBSERVER
#define HTTP_PASSCODE  "mysecretkey"


// OTA UPDATE
#define OTA_PASSWORD "mysecretkey"
#define OTA_PORT 8266


// Fauxmo - Wemos switch simulation
// Define RF switches with names and their on and off codes - make sure the arrays have the correct number of elements
const char* RFNames[] = { "Badezimmerlicht", "Schlafzimmerlicht", "Arbeitszimmerlicht", "Küchenlicht" };
const int RFCodesOn[] = { 11144421, 11144431, 11144441, 1381719 };
const int RFCodesOff[] = { 11144422, 11144432, 11144442, 1381716 };

// Define HTTP devices with names and their on and off URL - make sure the arrays have the correct number of elements
const char* HttpNames[] = { "Stereo", "Satellite" };
const char* HttpOn[] = { "http://10.1.1.17/goform/formiPhoneAppPower.xml?1+PowerOn", "http://10.1.1.18/cgi-bin/admin?command=wakeup" };
const char* HttpOff[] = { "http://10.1.1.17/goform/formiPhoneAppPower.xml?1+PowerStandby", "http://10.1.1.18/cgi-bin/admin?command=standby" };

