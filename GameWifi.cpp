/**
 * GameWifi.h - This class take care of the Wifi connectivity
 * 
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#include "GameWifi.h"



GameWifi::GameWifi(){}

void GameWifi::setup(){

  Serial.printf("Connecting to %s\n", ssid);

  // For now we ill just load up the STATION, 
  // later we will make it configurable to use AP mode
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  delay(5000);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }


 if (WiFi.waitForConnectResult() == WL_CONNECTED) {

  
    wifiConnected = true;
    Serial.println("Connection Established...");
    
  }else{
    Serial.println("Could not find the AP to connect to, so running without OTA.");
  }

}

boolean GameWifi::isWifiConnected(){
  return wifiConnected;
}


