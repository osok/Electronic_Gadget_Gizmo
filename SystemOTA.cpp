/**
 * SystemOTA.cpp - This Class manages the OTA "Over The Air" option
 *              which enables the card to be programmed without UART 
 *              connectivity.
 * 
 * 
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#include "SystemOTA.h"
#include "Global.h"

SystemOTA::SystemOTA(){}

void SystemOTA::setup(){
     ArduinoOTA.onStart([]() {
      Serial.println("OTA Starting...");
    });
    ArduinoOTA.onEnd([]() {
      Serial.println("\nOTA End.");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    
    ArduinoOTA.onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("OTA Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("OTA Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("OTA Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("OTA Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("OTA End Failed");
    });
    ArduinoOTA.begin();
    Serial.println("OTA Ready");
    Serial.print("IP address: ");
    Serial.println( WiFi.localIP());
 
}

void SystemOTA::run(){
  if(getBox()->isWifiConnected()){
    ArduinoOTA.handle();
    yield();
  }
}



