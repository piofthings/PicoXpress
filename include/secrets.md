Add a file called `secrets.h` in this folder with the following code

```cpp
//enter your SSID here
const char *ssid = "";
//enter your network password here
const char *password = ""           ;
// IP address of mqtt server e.g. 192.168.10.20
const char *mqtt_server = "";
const int mqtt_port = 1883;
// Mqtt broker's username
const char *mqtt_user = "";
// Mqtt broker's password
const char *mqtt_password = "";
// Topic that the ESP is subscribing to e.g. "zigbee2mqtt/0x00124b00226b5c99"
const char *in_topic = "";
// OR
// Bearer token from HomeAssistant. The word `Bearer ` must be present before the actual token. 
// The entire string is added as "Authorization" header
const char *hassio_auth_header = "Bearer <token from Home Assistant>";

```