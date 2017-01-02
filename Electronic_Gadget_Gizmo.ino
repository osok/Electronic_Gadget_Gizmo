
#include "Util.h"
#include "Game.h"
//#include <ESP8266WiFi.h>
//#include <ESP8266mDNS.h>
//#include <WiFiUdp.h>
//#include <ArduinoOTA.h>

/**
 * WiFI / OTA code found at
 * http://community.blynk.cc/t/updating-ota-is-amazing/7649/67
 * Aug 15 Dave1829
 */
const char* ssid = "Test-Net";
const char* password = "PleaseStayOffMyWiFi";

Game _game;
Util util;

boolean wifiConnected = false;

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("");
  Serial.print("Booting");
  
  util.wait(5);

  
//  WiFi.mode(WIFI_STA);
//  WiFi.begin(ssid, password);
//
//  util.wait(5);
//  
//  if (WiFi.waitForConnectResult() == WL_CONNECTED) {
//    wifiConnected = true;
//    Serial.println("Connection Established...");
//    ArduinoOTA.onStart([]() {
//      Serial.println("OTA Starting...");
//    });
//    ArduinoOTA.onEnd([]() {
//      Serial.println("\nOTA End.");
//    });
//    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
//      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
//    });
//    
//    ArduinoOTA.onError([](ota_error_t error) {
//      Serial.printf("Error[%u]: ", error);
//      if (error == OTA_AUTH_ERROR) Serial.println("OTA Auth Failed");
//      else if (error == OTA_BEGIN_ERROR) Serial.println("OTA Begin Failed");
//      else if (error == OTA_CONNECT_ERROR) Serial.println("OTA Connect Failed");
//      else if (error == OTA_RECEIVE_ERROR) Serial.println("OTA Receive Failed");
//      else if (error == OTA_END_ERROR) Serial.println("OTA End Failed");
//    });
//    ArduinoOTA.begin();
//    Serial.println("OTA Ready");
//    
//    Serial.print("IP address: ");
//    Serial.println(WiFi.localIP());
//  }else{
//    Serial.println("Could not find the AP to connect to, so running without OTA.");
//  }


  _game.setup();
  
}

void loop() {
//  if(wifiConnected){
//    ArduinoOTA.handle();
//    yield();
//  }
  _game.run();

}
