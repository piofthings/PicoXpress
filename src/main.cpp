#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include "secrets.h"

ESP8266WiFiMulti WiFiMulti;

HTTPClient http;
WiFiClient client;

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println("Connecting to WiFi...");
  
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  // wait for WiFi connection
  while ((WiFiMulti.run() != WL_CONNECTED)) {
    Serial.write('.');
    delay(1500);
  }
  Serial.println(" connected to WiFi");

  // allow reuse (if server supports it)
  http.setReuse(true);


  http.begin(client, "http://192.168.50.15:8123");
}

int pass = 0;

void loop() 
{
  if ((WiFiMulti.run() == WL_CONNECTED)) 
  {

    WiFiClient client;

    HTTPClient http;

    //Serial.print("[HTTP] begin...\n");
    
    if (http.begin(client, "http://192.168.50.15:8123/api/states/sensor.0x00124b00226b5c15_temperature")) 
    {  // HTTP
      
      http.addHeader("Authorization", hassio_auth_header);
      http.addHeader("Content-Type","application/json");

      //Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) 
      {
        // HTTP header has been send and Server response header has been handled
        //Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
        {
          String payload = http.getString();
          //Serial.println("We got things back:");
          StaticJsonDocument<500> doc;
          char json[500];
          payload.toCharArray(json, payload.length() + 1);
          DeserializationError error = deserializeJson(doc, json);

          // // Test if parsing succeeds.
          if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
          }
          else {
            const char* state = doc["state"];
            //Serial.println(payload);
            //Serial.print("[[Temperature]]=");
            Serial.println(state);           
          }
        } 
        else 
        {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
      } 
      http.end();
    }
    else 
    {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }
  delay(60000);
}