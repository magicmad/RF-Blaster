//
// your settings
//


#define SERIAL_BAUDRATE 74880


// D1 = GPIO 5
// D2 = GPIO 4
// D3 = GPIO 0 (flash)

// RF sender module pin
#define RF_SEND_PIN 4
// RF receiver module pin
#define RF_RECEIVE_PIN 5


// WIFI access
#define WIFI_SSID "xxx"
#define WIFI_PASS "xxx"


// NETWORK
const char* HOSTNAME = "RF-BLASTER";

const IPAddress ip(10, 1, 1, 42);
const IPAddress gateway(10, 1, 1, 1);
const IPAddress subnet(255, 255, 255, 0);


// WEBSERVER
#define HTTP_PASSCODE  "xxx"


// OTA UPDATE
#define OTA_PASSWORD "xxx"
#define OTA_PORT 8266


// Fauxmo - Wemos switch simulation (up to 16 devices should work)
// Define RF switches with names and their on and off codes. Make sure the arrays have the correct number of elements and order.
const char* RFNames[] = { "Badezimmerlicht", "Schlafzimmerlicht", "Arbeitszimmerlicht", "WC Licht", "Küchenlicht", "TV LED"};
const int RFCodesOn[] = { 11144421, 11144431, 11144441, 11144451, 1381719, 1394007 };
const int RFCodesOff[] = { 11144422, 11144432, 11144442, 11144452, 1381716, 1394004 };

// Define HTTP devices with names and their on and off URLs. Make sure the arrays have the correct number of elements and order.
const char* HttpNames[] = { "Stereo", "Satellit" };
const char* HttpOn[] = { "http://10.1.1.17/goform/formiPhoneAppPower.xml?1+PowerOn", "http://10.1.1.18/cgi-bin/admin?command=wakeup" };
const char* HttpOff[] = { "http://10.1.1.17/goform/formiPhoneAppPower.xml?1+PowerStandby", "http://10.1.1.18/cgi-bin/admin?command=standby" };

